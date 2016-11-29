#include"Grid.h"
namespace GRID {
	void Grid::InitGridCoordinate()
	{
		if (mPositionX)
			delete[] mPositionX;
		if (mPositionY)
			delete[] mPositionY;
		if (mPositionZ)
			delete[] mPositionZ;

		mPositionX = new GLfloat[(mRow + 1)*(mCol + 1)];
		mPositionY = new GLfloat[(mRow + 1)*(mCol + 1)];
		mPositionZ = new GLfloat[(mRow + 1)*(mCol + 1)];

		for (GLint i = 0; i < (mRow + 1)*(mCol + 1); i++)
		{
			mPositionX[i] = ((GLfloat)(-mRow) / 2.0f + (GLfloat)(i % (mRow + 1)))*mLength / mRow;
			mPositionY[i] = 0;
			mPositionZ[i] = ((GLfloat)(-mCol) / 2.0f + (GLfloat)(i / (mCol + 1)))*mLength / mCol;

			if (mPositionY[i] > mMax_Height)
				mPositionY[i] = mMax_Height;
		}

	}
	void Grid::InitGridIndices()
	{
		if (mIndices)
			delete[] mIndices;
		mIndices = new GLuint[mRow * mCol * 6];
		for (GLint i = 0; i < mRow*mCol; i++)
		{
			mIndices[(6 * i)] = i + (i / mRow);
			mIndices[(6 * i) + 1] = mIndices[6 * i] + (mRow + 1);
			mIndices[(6 * i) + 2] = mIndices[6 * i] + 1;
			mIndices[(6 * i) + 3] = mIndices[(6 * i) + 2];
			mIndices[(6 * i) + 4] = mIndices[(6 * i) + 1];
			mIndices[(6 * i) + 5] = mIndices[(6 * i) + 2] + (mRow + 1);
		}
	}

	void Grid::InitGridNormal()
	{
		GLint NofTriangle = 0;
		GLboolean hasLeftPoint;
		GLboolean hasRightPoint;
		GLboolean hasUpperPoint;
		GLboolean hasDownerPoint;
		GLfloat x1, x2, Nx = 0;
		GLfloat y1, y2, Ny = 0;
		GLfloat z1, z2, Nz = 0;
		
		if (mNormX)
			delete[] mNormX;
		if (mNormY)
			delete[] mNormY;
		if (mNormZ)
			delete[] mNormZ;

		mNormX = new GLfloat[(mRow + 1)*(mCol + 1)];
		mNormY = new GLfloat[(mRow + 1)*(mCol + 1)];
		mNormZ = new GLfloat[(mRow + 1)*(mCol + 1)];
		for (GLint i = 0; i < (mRow + 1)*(mCol + 1); i++)
		{
			hasLeftPoint = (i % (mRow + 1) == 0) ? GL_FALSE : GL_TRUE;
			hasRightPoint = ((i + 1) % (mRow + 1) == 0) ? GL_FALSE : GL_TRUE;
			hasUpperPoint = (i - (mRow + 1)) < 0 ? GL_FALSE : GL_TRUE;
			hasDownerPoint = (i + (mRow + 1)) >= (mRow + 1)*(mCol + 1) ? GL_FALSE : GL_TRUE;

			if (hasLeftPoint&&hasUpperPoint)
			{
				NofTriangle += 1;
				x1 = mPositionX[i - (mRow + 1)] - mPositionX[i];
				y1 = mPositionY[i - (mRow + 1)] - mPositionY[i];
				z1 = mPositionZ[i - (mRow + 1)] - mPositionZ[i];

				x2 = mPositionX[i - 1] - mPositionX[i];
				y2 = mPositionY[i - 1] - mPositionY[i];
				z2 = mPositionZ[i - 1] - mPositionZ[i];

				Nx += y1*z2 - y2*z1;
				Ny += z1*x2 - z2*x1;
				Nz += x1*y2 - x2*y1;
			}

			if (hasLeftPoint&&hasDownerPoint)
			{
				NofTriangle += 2;
				x1 = mPositionX[i - 1] - mPositionX[i];
				y1 = mPositionY[i - 1] - mPositionY[i];
				z1 = mPositionZ[i - 1] - mPositionZ[i];

				x2 = mPositionX[i + mRow] - mPositionX[i];
				y2 = mPositionY[i + mRow] - mPositionY[i];
				z2 = mPositionZ[i + mRow] - mPositionZ[i];

				Nx += y1*z2 - y2*z1;
				Ny += z1*x2 - z2*x1;
				Nz += x1*y2 - x2*y1;

				x1 = mPositionX[i + mRow] - mPositionX[i];
				y1 = mPositionY[i + mRow] - mPositionY[i];
				z1 = mPositionZ[i + mRow] - mPositionZ[i];

				x2 = mPositionX[i + mRow + 1] - mPositionX[i];
				y2 = mPositionY[i + mRow + 1] - mPositionY[i];
				z2 = mPositionZ[i + mRow + 1] - mPositionZ[i];

				Nx += y1*z2 - y2*z1;
				Ny += z1*x2 - z2*x1;
				Nz += x1*y2 - x2*y1;
			}

			if (hasRightPoint&&hasUpperPoint)
			{
				NofTriangle += 2;

				x1 = mPositionX[i - (mRow + 1)] - mPositionX[i];
				y1 = mPositionY[i - (mRow + 1)] - mPositionY[i];
				z1 = mPositionZ[i - (mRow + 1)] - mPositionZ[i];

				x2 = mPositionX[i - mRow] - mPositionX[i];
				y2 = mPositionY[i - mRow] - mPositionY[i];
				z2 = mPositionZ[i - mRow] - mPositionZ[i];

				Nx += y1*z2 - y2*z1;
				Ny += z1*x2 - z2*x1;
				Nz += x1*y2 - x2*y1;

				x1 = mPositionX[i - mRow] - mPositionX[i];
				y1 = mPositionY[i - mRow] - mPositionY[i];
				z1 = mPositionZ[i - mRow] - mPositionZ[i];

				x2 = mPositionX[i + 1] - mPositionX[i];
				y2 = mPositionY[i + 1] - mPositionY[i];
				z2 = mPositionZ[i + 1] - mPositionZ[i];

				Nx += y1*z2 - y2*z1;
				Ny += z1*x2 - z2*x1;
				Nz += x1*y2 - x2*y1;

			}

			if (hasRightPoint&&hasDownerPoint)
			{
				NofTriangle += 1;
				x1 = mPositionX[i + (mRow + 1)] - mPositionX[i];
				y1 = mPositionY[i + (mRow + 1)] - mPositionY[i];
				z1 = mPositionZ[i + (mRow + 1)] - mPositionZ[i];

				x2 = mPositionX[i + 1] - mPositionX[i];
				y2 = mPositionY[i + 1] - mPositionY[i];
				z2 = mPositionZ[i + 1] - mPositionZ[i];

				Nx += y1*z2 - y2*z1;
				Ny += z1*x2 - z2*x1;
				Nz += x1*y2 - x2*y1;
			}

			mNormX[i] = Nx / NofTriangle;
			mNormY[i] = Ny / NofTriangle;
			mNormZ[i] = Nz / NofTriangle;

			NofTriangle = 0;
		}

	}

	void Grid::Load_Grid()
	{
		glBindVertexArray(mVao);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mPositionX, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mPositionY, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, mVbo[2]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mPositionZ, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[3]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mNormX, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[4]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mNormY, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(4);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[5]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mNormZ, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(5);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mRow*mCol * 6 * sizeof(GLuint), mIndices, GL_STATIC_DRAW);
	}
	void Grid::Init_Grid()
	{
		InitGridCoordinate();
		InitGridIndices();
		InitGridNormal();
	}
	void Grid::Render()
	{
		glBindVertexArray(mVao);
		glDrawElements(GL_TRIANGLES, mRow*mCol * 6 * sizeof(GLuint), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
	void Grid::ChangeHeights()
	{
		for (GLint i = 0; i < (mRow + 1)*(mCol + 1); i++)
		{
			mPositionY[i] += (GLfloat)((rand() % 3) - 1)*(mMax_Height-mMin_Height)/255.0f;
			if (mPositionY[i] > mMax_Height)
			{
				mPositionY[i] = mMax_Height;
			}
			else if (mPositionY[i] < mMin_Height)
			{
				mPositionY[i] = mMin_Height;
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mPositionY, GL_DYNAMIC_DRAW);

		InitGridNormal();

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[3]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mNormX, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[4]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mNormY, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[5]);
		glBufferData(GL_ARRAY_BUFFER, (mRow + 1)*(mCol + 1) * sizeof(GLfloat), mNormZ, GL_DYNAMIC_DRAW);


	}
void Grid::Load_Height_From_Map(GLubyte* Map,GLint Format)
	{
		if (mPositionY)
			delete[] mPositionY;
		if (Format == IL_LUMINANCE)
		{
			mPositionY = new GLfloat[(mRow + 1)*(mCol + 1)];
			for (int i = 0; i < (mRow + 1)* (mCol + 1); i++)
			{
				mPositionY[i] = mMin_Height + (GLfloat)Map[i] * (mMax_Height - mMin_Height) / 255.0f;
			}
		}
		else if (Format == IL_RGBA)
		{
			for (int i = 0; i < (mRow + 1)* (mCol + 1); i++)
			{
				mPositionY[i] = mMin_Height + (GLfloat)Map[4*i] * (mMax_Height - mMin_Height) / 255.0f;
			}
		}
		else if (Format == IL_RGB)
		{
			for (int i = 0; i < (mRow + 1)* (mCol + 1); i++)
			{
				mPositionY[i] = mMin_Height + (GLfloat)Map[3 * i] * (mMax_Height - mMin_Height) / 255.0f;
			}
		}
	}
void Grid::Produce_Height()
	{
		if (mPositionY)
			delete[] mPositionY;

		mPositionY = new GLfloat[(mRow + 1)*(mCol + 1)];
		
		mPositionY[0] = 0.0f;
		for (int i = 0; i < (mRow + 1)* (mCol + 1)-1; i++)
		{
			mPositionY[i + 1] = mMin_Height+(rand() % 256)*(mMax_Height - mMin_Height) / 255.0f;
			
			if (mPositionY[i + 1] > mMax_Height)
				mPositionY[i + 1] = mMax_Height;
			else if (mPositionY[i + 1] < mMin_Height)
				mPositionY[i + 1] = mMin_Height;
		}
	}
}