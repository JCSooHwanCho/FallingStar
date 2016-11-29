#pragma comment(lib, "../lib/x64/DevIL.lib")
#pragma comment(lib, "../lib/x64/ILU.lib")
#pragma comment(lib, "../lib/x64/ILUT.lib")
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <cstdlib>
#include<cmath>
#include<cstdlib>
#include<ctime>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <GLUT/GLUT.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <IL/il.h>

#define	DEG2RAD(x)	GLfloat(M_PI*(x)/180.0)
#define	MIN(x,y)	((x)<(y)?(x):(y))
#define	MAX(x,y)	((x)>(y)?(x):(y))
#define	FOVY_MIN	5.0f
#define	FOVY_MAX	179.0f

#ifndef BUFFER_OFFSET	
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif

struct
{
	bool	perspective;
	GLfloat	fovy;
} camera =
{
	true,
	45.0f,
};
enum GUIstate { STATE_NONE = 0, STATE_ROTATING, STATE_MOVING, STATE_NUM };
enum MOUSE_MODE { MODE_TERRAIN = 0,MODE_LIGHT,MODE_NUM };
struct
{
	glm::ivec2	offset, position_mouse;
	GLuint		state,mode;
} gui =
{
	glm::ivec2(0,0),
	glm::ivec2(0,0),
	STATE_NONE,
	MODE_TERRAIN,
};

#include "shaders.cpp"
#include "Grid.h"
#include "PointLight.h"
#include "Materials.h"

struct ImageData {
	GLint Row;
	GLint Col;
	GLint Format;
	GLint Type;
	GLfloat Length;
	ILubyte* Heights;
} data;



//User Changable Area
const GLfloat Length = 4.0;
const GLfloat Max_Height = 2.0;
const GLfloat Min_Height = 0.0;
const char* Filename = "data/images/HeightMap1.jpg";
const int Max_Light = 100;//최대 광원 개수
//User Changable Area End



GLuint MaterialType = 0;
GLboolean AnimateOn = GL_FALSE;
glm::mat4	P, V, M,M_Light;
GLuint terrain_Prog,Light_Prog;
GLint Cnt = 0;
GLint CntMax = 10;

GRID::Grid* grid;
Light::PointLights* light;

void Load_Height(const char * Filename, ImageData& data)
{
	ilInit();
	ILuint	img;
	ilGenImages(1, &img);
	ilBindImage(img);
	ilLoadImage(Filename);
	printf("image loaded. (width=%d, height=%d, format=%d(0x%x), type=%d(0x%x))\n",
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_TYPE),
		ilGetInteger(IL_IMAGE_TYPE));
	data.Row = ilGetInteger(IL_IMAGE_WIDTH);
	data.Col = ilGetInteger(IL_IMAGE_HEIGHT);
	data.Format = ilGetInteger(IL_IMAGE_FORMAT);
	data.Type = ilGetInteger(IL_IMAGE_TYPE);
	data.Heights = ilGetData();
}

void init()
{

	Load_Height(Filename,data);
	terrain_Prog = build_program_from_files("terrain.vert", "terrain.frag");
	Light_Prog = build_program_from_files("light.vert", "light.frag");

	grid = new GRID::Grid(data.Row, data.Col, Length, Max_Height, Min_Height);
	light = new Light::PointLights(Max_Light);

	//grid->Produce_Height();
	grid->Load_Height_From_Map(data.Heights,data.Format);
	grid->Load_Grid();
	light->Load_Lights();

	V = glm::lookAt(glm::vec3(1.0f, 1.0f, 1.0f)*Length, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void display()
{
	P = glm::perspective(camera.fovy, 1.0f, 0.1f / (GLfloat)Length, 10.0f*(GLfloat)Length);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(terrain_Prog);

	light->ImplementLightsAtTerrain(terrain_Prog, MaterialType);

	M = grid->T*grid->R;
	M_Light = light->T*light->R;
	glUniformMatrix4fv(glGetUniformLocation(terrain_Prog, "MVP"), 1, GL_FALSE, glm::value_ptr(P*V*M));

	glUniformMatrix4fv(glGetUniformLocation(terrain_Prog, "MV"), 1, GL_FALSE, glm::value_ptr(V*M));
	glUniformMatrix4fv(glGetUniformLocation(terrain_Prog, "MV_L"), 1, GL_FALSE, glm::value_ptr(V*M_Light));
	glUniformMatrix4fv(glGetUniformLocation(terrain_Prog, "V"), 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix3fv(glGetUniformLocation(terrain_Prog, "matNormal"), 1, GL_FALSE, glm::value_ptr(glm::mat3(V*M)));

	grid->Render();
	
	glUseProgram(Light_Prog);
	glUniformMatrix4fv(glGetUniformLocation(Light_Prog, "MVP"), 1, GL_FALSE, glm::value_ptr(P*V*M_Light));
	light->Render();

	glutSwapBuffers();

}

void mouse_wheel(int wheel, int dir, int x, int y)
{
	camera.fovy = MIN(MAX(camera.fovy + (GLfloat)dir*0.1f, FOVY_MIN), FOVY_MAX);//fovy를 0.1단위로 조정한다. dir은 정수이지만 미세 조정을 위해 float로 캐스팅 후 0.1을 곱해준다.
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			gui.state = STATE_MOVING; 
			gui.position_mouse = glm::ivec2(x, y);

			if (gui.mode == MODE_LIGHT)
			{
				GLubyte	pixel[4] = { 0,0,0,0 };
				glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
				if(pixel[0]==255&&pixel[2]==255)//light여야 하고 현재 커서가 가리키지 않는 빛이여야 할 것!
				light->SetCursor(pixel[1]+1);
			}
		}
		else	gui.state = STATE_NONE;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			gui.state = STATE_ROTATING;
			gui.position_mouse = glm::ivec2(x, y);
		}
		else	gui.state = STATE_NONE;
		break;
	}
}

void motion(int x, int y)
{
	switch (gui.state)
	{
	case STATE_ROTATING:
	{
		if (gui.mode == MODE_TERRAIN)
		{
			gui.offset = glm::ivec2(x, y) - gui.position_mouse;//클릭한 위치와 현재 위치와의 거리
			gui.position_mouse = glm::ivec2(x, y);//현재 마우스 위치
			glm::vec4	viewport;
			glGetFloatv(GL_VIEWPORT, glm::value_ptr(viewport));
			glm::vec3	org_win = glm::project(glm::vec3(0.0f, 0.0f, 0.0f), V*grid->T, P, viewport);
			glm::vec3	dir_win = glm::vec3(gui.offset.y, gui.offset.x, 0.0f);
			glm::vec3	dir_model = glm::unProject(dir_win + org_win, V*grid->T, P, viewport);


			if (dir_model.x*dir_model.x + dir_model.y*dir_model.y + dir_model.z*dir_model.z == 0)
				break;

			grid->R = glm::rotate(glm::mat4(1.0f), DEG2RAD(GLfloat(dir_win.length() / 2)), dir_model)*grid->R;
			glutPostRedisplay();
		}
		break;
	}
	case STATE_MOVING:
	{
		if (gui.mode == MODE_TERRAIN)
		{
			gui.offset = glm::ivec2(x, y) - gui.position_mouse;
			gui.position_mouse = glm::ivec2(x, y);
			glm::vec4	viewport;
			glGetFloatv(GL_VIEWPORT, glm::value_ptr(viewport));
			glm::vec3	org_win = glm::project(glm::vec3(0.0f, 0.0f, 0.0f), V*grid->T, P, viewport);
			glm::vec3	dir_win = glm::vec3(gui.offset.x, -gui.offset.y, 0.0f);
			glm::vec3	dir_model = glm::unProject(dir_win + org_win, V*grid->T, P, viewport);

			grid->T = glm::translate(glm::mat4(1.0f), dir_model)*grid->T;
			glutPostRedisplay();
		}
		else if (gui.mode == MODE_LIGHT)
		{
			gui.offset = glm::ivec2(x, y) - gui.position_mouse;
			gui.position_mouse = glm::ivec2(x, y);
			glm::vec4	viewport;
			glGetFloatv(GL_VIEWPORT, glm::value_ptr(viewport));
			glm::vec3	org_win = glm::project(glm::vec3(0.0f, 0.0f, 0.0f), V*light->T, P, viewport);
			glm::vec3	dir_win = glm::vec3(gui.offset.x, -gui.offset.y, 0.0f);
			glm::vec3	dir_model = glm::unProject(dir_win + org_win, V*light->T, P, viewport);

			light->Move_Forward_PositionX(dir_model.x);
			light->Move_Forward_PositionY(dir_model.y);
			light->Move_Forward_PositionZ(dir_model.z);
			glutPostRedisplay();
		}
		break;
	}
	}
}

void timer(GLint value)
{
	if (AnimateOn==GL_TRUE)
	{
		Cnt++;
		if (Cnt == CntMax)
		{
			grid->ChangeHeights();
			Cnt = 0;
		}
		light->AnimateFallingLight(Min_Height-1.0f, Max_Height + 1.0f, 0.01f);
	}
	glutPostRedisplay();

	glutTimerFunc(10, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	int m = glutGetModifiers();
	switch (key)
	{
	case ' ':
		MaterialType += 1;
		if (MaterialType == Material::NofMaterials)
			MaterialType = 0;
		printf("Material = %s\n", Material::MaterialName[MaterialType]);
		break;
	case 'q':
	case 'Q':
		if (m == GLUT_ACTIVE_CTRL)
			light->Move_Forward_AmbientR(0.01f);
		if (m == GLUT_ACTIVE_ALT)
			light->Move_Forward_DiffuseR(0.01f);
		else if (m == GLUT_ACTIVE_SHIFT)
			light->Move_Forward_SpecularR(0.01f);
		else
			light->Move_Forward_PositionX(0.01f);
		break;
	case 'w':
	case 'W':
		if (m == GLUT_ACTIVE_CTRL)
			light->Move_Forward_AmbientR(0.01f);
		else if (m == GLUT_ACTIVE_ALT)
			light->Move_Forward_DiffuseG(0.01f);
		else if (m == GLUT_ACTIVE_SHIFT)
			light->Move_Forward_SpecularG(0.01f);
		else
			light->Move_Forward_PositionY(0.01f);
		break;
	case 'e':
	case 'E':
		if (m == GLUT_ACTIVE_CTRL)
			light->Move_Forward_AmbientB(0.01f);
		else if (m == GLUT_ACTIVE_ALT)
			light->Move_Forward_DiffuseB(0.01f);
		else if (m == GLUT_ACTIVE_SHIFT)
			light->Move_Forward_SpecularB(0.01f);
		else
			light->Move_Forward_PositionZ(0.01f);
		break;
	case 'a':
	case 'A':
		if (m == GLUT_ACTIVE_CTRL)
			light->Move_Backward_AmbientR(0.01f);
		else if (m == GLUT_ACTIVE_ALT)
			light->Move_Backward_DiffuseR(0.01f);
		else if (m == GLUT_ACTIVE_SHIFT)
			light->Move_Backward_SpecularR(0.01f);
		else
			light->Move_Backward_PositionX(0.01f);
		break;
	case 's':
	case 'S':
		if (m == GLUT_ACTIVE_CTRL)
			light->Move_Backward_AmbientG(0.01f);
		else if (m == GLUT_ACTIVE_ALT)
			light->Move_Backward_DiffuseG(0.01f);
		else if (m == GLUT_ACTIVE_SHIFT)
			light->Move_Backward_SpecularG(0.01f);
		else
			light->Move_Backward_PositionY(0.01f);
		break;
	case 'd':
	case 'D':
		if (m == GLUT_ACTIVE_CTRL)
			light->Move_Backward_AmbientB(0.01f);
		else if (m == GLUT_ACTIVE_ALT)
			light->Move_Backward_DiffuseB(0.01f);
		else if (m == GLUT_ACTIVE_SHIFT)
			light->Move_Backward_SpecularB(0.01f);
		else
			light->Move_Backward_PositionZ(0.01f);
		break;
	case'l':
	case'L':
		if (gui.mode == MODE_TERRAIN)
			gui.mode = MODE_LIGHT;
		else
			gui.mode = MODE_TERRAIN;
		break;
	case'z':
	case'Z':
		if (AnimateOn == GL_FALSE)
			AnimateOn = GL_TRUE;
		else
			AnimateOn = GL_FALSE;
		break;
	case 17 : //ctrl+q
		light->Move_Forward_AmbientR(0.01f);
		break;
	case 1 : //ctrl+a
		light->Move_Backward_AmbientR(0.01f);
		break;
	case 23 : //ctrl+w
		light->Move_Forward_AmbientG(0.01f);
		break;
	case 19 : //ctrl+s
		light->Move_Backward_AmbientG(0.01f);
		break;
	case 5 : ///ctrl+e
		light->Move_Forward_AmbientB(0.01f);
		break;
	case 4 : //ctrl+d
		light->Move_Backward_AmbientB(0.01f);
		break;
	}
	glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		light->Turn_On();
		break;
	case GLUT_KEY_DOWN:
		light->Turn_Off();
		break;
	case GLUT_KEY_LEFT:
		light->Move_Backward_Cursor();
		break;
	case GLUT_KEY_RIGHT :
		light->Move_Forward_Cursor();
		break;
	case GLUT_KEY_PAGE_UP:
		light->Move_Forward_PointSize(0.1f);
		break;
	case GLUT_KEY_PAGE_DOWN:
		light->Move_Backward_PointSize(0.1f);
		break;
	}
	glutPostRedisplay();
}
GLint main(GLint argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512);
#ifdef __APPLE__
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
	glutCreateWindow(argv[0]);
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(4, 3);
	glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
	glutCreateWindow(argv[0]);
	if (glewInit()) {
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
		exit(EXIT_FAILURE);
	}
#endif
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouse_wheel);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutTimerFunc(10, timer, 0);//1초후 자신을 다시 호출하도록 예약
	glutMainLoop();
}