#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef __POINTLIGHT__
#define __POINTLIGHT_



namespace Light {
	const int MAX_LIGHT = 203;


	class PointLights {
	public:

		glm::mat4 R, T;

		PointLights(GLuint max_light) : mMax_Light(max_light),mCursor(0)
		{
			if (mMax_Light > MAX_LIGHT)
				mMax_Light = MAX_LIGHT;
			else if (mMax_Light < 0)
				mMax_Light = 1;

			mState = new GLuint[mMax_Light];

			for (int i = 0; i < mMax_Light; i++)
				mState[i] = FALLING;
			glGenVertexArrays(1,&mVao);
			mVbo = new GLuint[5];
			glGenBuffers(5, mVbo);

			Init();
		}
		~PointLights()
		{
			if (mPosition)
			{
				delete[] mPosition;
			}
			if (mAmbient)
			{
				delete[] mAmbient;
			}
			if (mDiffuse)
			{
				delete[] mDiffuse;
			}
			if (mSpecular)
			{
				delete[] mSpecular;
			}
			if (mPointSize)
			{
				delete[] mPointSize;
			}
			if (mPointColor)
			{
				delete[] mPointColor;
			}
			if (mSelected)
			{
				delete[] mSelected;
			}
			if (mOn)
			{
				delete[] mOn;
			}
			if (mState)
			{
				delete[] mState;
			}
			glDeleteBuffers(5, mVbo);
			delete[] mVbo;
			glDeleteVertexArrays(1, &mVao);
		}

		GLboolean isOn(int Cursor);
		void Turn_On();
		void Turn_Off();
		void Render();
		void Load_Lights();
		void Move_Forward_Cursor();
		void Move_Backward_Cursor();
		void Move_Forward_PositionX(GLfloat val);
		void Move_Backward_PositionX(GLfloat val);
		void Move_Forward_PositionY(GLfloat val);
		void Move_Backward_PositionY(GLfloat val);
		void Move_Forward_PositionZ(GLfloat val);
		void Move_Backward_PositionZ(GLfloat val);
		void Move_Forward_AmbientR(GLfloat val);
		void Move_Backward_AmbientR(GLfloat val);
		void Move_Forward_AmbientG(GLfloat val);
		void Move_Backward_AmbientG(GLfloat val);
		void Move_Forward_AmbientB(GLfloat val);
		void Move_Backward_AmbientB(GLfloat val);
		void Move_Forward_DiffuseR(GLfloat val);
		void Move_Backward_DiffuseR(GLfloat val);
		void Move_Forward_DiffuseG(GLfloat val);
		void Move_Backward_DiffuseG(GLfloat val);
		void Move_Forward_DiffuseB(GLfloat val);
		void Move_Backward_DiffuseB(GLfloat val);
		void Move_Forward_SpecularR(GLfloat val);
		void Move_Backward_SpecularR(GLfloat val);
		void Move_Forward_SpecularG(GLfloat val);
		void Move_Backward_SpecularG(GLfloat val);
		void Move_Forward_SpecularB(GLfloat val);
		void Move_Backward_SpecularB(GLfloat val);
		void Move_Forward_PointSize(GLfloat val);
		void Move_Backward_PointSize(GLfloat val);
		void ImplementLightsAtTerrain(GLuint TerrainProgram,GLuint MaterialType);
		void AnimateFallingLight(GLfloat minHeight,GLfloat maxHeight,GLfloat val);
		void SetCursor(GLuint val);
		GLint GetCursor();
	private:
		GLfloat* mPosition;
		GLfloat* mAmbient;
		GLfloat* mDiffuse;
		GLfloat* mSpecular;
		GLfloat* mPointSize;
		GLfloat* mPointColor;
		GLuint mVao;
		GLuint* mVbo;
		GLint mMax_Light;
		GLint mCursor;
		GLuint* mOn;
		GLuint* mSelected;
		GLuint* mState;

		void Init();
		void InitPosition();
		void InitAmbient();
		void InitDiffuse();
		void InitSpecular();
		void InitPointSize();
		void InitPointColor();
		void InitPointOn();
		void InitPointSelected();

		enum ANIMATION_STATE { FALLING = 0, RISING, STATE_NUM };

	};
}
#endif