#pragma once
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
#include <IL/il.h>

#ifndef BUFFER_OFFSET	
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif

#ifndef __GRID__
#define __GRID__

namespace GRID {
	class Grid {
	public:
		Grid(GLint row, GLint col, GLfloat length, GLfloat maxHeight = 1.0, GLfloat minHeight = -1.0) :mRow(row-1), mCol(col-1), mLength(length), mMax_Height(maxHeight), mMin_Height(minHeight), mNum_VBO(6),mMode(Grid::HEIGHT_MODE::MODE_MAP)
		{
			srand((unsigned int)time(NULL));
			if (mRow < 2)
				mRow = 2;
			if (mCol < 2)
				mCol = 2;
			if (length < 0)
				length = 0.1f;
			glGenVertexArrays(1, &mVao);

			mVbo = new GLuint[mNum_VBO];
			glGenBuffers(mNum_VBO, mVbo);
			glGenBuffers(1, &mEbo);
			
			if (mMax_Height < mMin_Height)
			{
				GLfloat temp;
				temp = mMax_Height;
				mMax_Height = mMin_Height;
				mMin_Height = mMax_Height;
			}

			Init_Grid();
		}
		~Grid()
		{
			glDeleteBuffers(mNum_VBO, mVbo);
			glDeleteVertexArrays(1, &mVao);
			if (mVbo)
				delete[] mVbo;
			if(mPositionX)
				delete[] mPositionX;
			if(mPositionY)
				delete[] mPositionY;
			if(mPositionZ)
				delete[] mPositionZ;
			if(mNormX)
				delete[] mNormX;
			if(mNormY)
				delete[] mNormY;
			if(mNormZ)
				delete[] mNormZ;
			if(mIndices)
				delete[] mIndices;
		}
		void Render();
		void ChangeHeights();
		void Init_Grid();
		void Load_Grid();
		void Load_Height_From_Map(GLubyte* Map,GLint Format);
		void Produce_Height();
		glm::mat4 T, R;

	private:
		GLint mRow;
		GLint mCol;
		GLfloat mLength;
		GLfloat mMax_Height;
		GLfloat mMin_Height;
		const GLuint mNum_VBO;
		GLuint mMode;

		GLfloat* mPositionX;
		GLfloat* mPositionY;
		GLfloat* mPositionZ;

		GLfloat* mNormX;
		GLfloat* mNormY;
		GLfloat* mNormZ;

		GLuint* mIndices;

		enum HEIGHT_MODE { MODE_MAP = 0, MODE_PRODUCE, MODE_NUM };

		GLuint mVao;
		GLuint* mVbo;
		GLuint mEbo;


		void InitGridCoordinate();
		void InitGridIndices();
		void InitGridNormal();
	};
};
#endif