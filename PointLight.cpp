#include<cstdio>
#include"PointLight.h"
#include"Materials.h"

namespace Light {
	void PointLights::Init()
	{
		InitPosition();
		InitAmbient();
		InitDiffuse();
		InitSpecular();
		InitPointSize();
		InitPointOn();
		InitPointColor();
		InitPointSelected();
	}
	void PointLights::InitPointOn()
	{
		if (mOn)
		{
			delete[] mOn;
		}
		mOn = new GLuint[mMax_Light];

		for (GLint i = 0; i < mMax_Light; i++)
		{
			mOn[i] = 0u;
		}
		mOn[0] = 1u;
}

	void PointLights::InitPointSelected()
	{
		if (mSelected)
			delete[] mSelected;

		mSelected = new GLuint[mMax_Light];

		for (int i = 0; i < mMax_Light; i++)
		{
			mSelected[i] = 0u;
		}

	}
	void PointLights::InitPointColor()
	{
		if (mPointColor)
		{
			delete[] mPointColor;
		}
		mPointColor = new GLfloat[3 * mMax_Light];

		for (GLint i = 0; i < mMax_Light; i++)
		{
			if (mOn[i] == 1u)
			{
				mPointColor[3 * i + 0] = 1.0f;
				mPointColor[3 * i + 1] = (GLfloat)i / 255.0f; 
				mPointColor[3 * i + 2] = 1.0f;
			}
			else
			{
				mPointColor[3 * i + 0] = 0.0f;
				mPointColor[3 * i + 1] = 0.0f;
				mPointColor[3 * i + 2] = 0.0f;
			}
		}
	}
	void PointLights::InitPosition()
	{
		if (mPosition)
		{
			delete[] mPosition;
		}
		mPosition = new GLfloat[mMax_Light*3];


		for (GLint i = 0; i < mMax_Light; i++)
		{
			mPosition[3 * i + 0] = 0.0f;
			mPosition[3 * i + 1] = 0.0f;
			mPosition[3 * i + 2] = 0.0f;
		}
	}
	void PointLights::InitAmbient()
	{
		if (mAmbient)
		{
			delete[] mAmbient;
		}
		mAmbient = new GLfloat[mMax_Light*3];

		for (GLint i = 0u; i < mMax_Light; i++)
		{
			mAmbient[3*i+0] = 0.5f;
			mAmbient[3*i+1] = 0.5f;
			mAmbient[3*i+2] = 0.5f;
		}
	}
	void PointLights::InitDiffuse()
	{
		if (mDiffuse)
		{
			delete[] mDiffuse;
		}
		mDiffuse = new GLfloat[3*mMax_Light];

		for (GLint i = 0; i < mMax_Light; i++)
		{
			mDiffuse[3*i+0] = 1.0f;
			mDiffuse[3*i+1] = 1.0f;
			mDiffuse[3*i+2] = 1.0f;
		}
	}
	void PointLights::InitSpecular()
	{
		if (mSpecular)
		{
			delete[] mSpecular;
		}
		mSpecular = new GLfloat[3*mMax_Light];
		for (GLint i = 0; i < mMax_Light; i++)
		{
			mSpecular[3*i+0] = 1.0f;
			mSpecular[3*i+1] = 1.0f;
			mSpecular[3*i+2] = 1.0f;
		}
	}
	void PointLights::InitPointSize()
	{
		if (mPointSize)
		{
			delete[] mPointSize;
		}
		mPointSize = new GLfloat[mMax_Light];

		for (GLint i = 0; i < mMax_Light; i++)
		{
			mPointSize[i] = 5.0f;
		}
	}
	void PointLights::Turn_On()
	{
		if (mCursor == 0)
			return;

		if (mOn[mCursor - 1] == 0u)
		{
			mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
			mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor-1)/ 255.0f;
			mPointColor[3 * (mCursor - 1) + 2] = 0.0f;

			glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
			glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPointColor, GL_STATIC_DRAW);
		}
		mOn[mCursor-1] = 1u;


		glBindBuffer(GL_ARRAY_BUFFER, mVbo[3]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mOn, GL_STATIC_DRAW);
	}
	void PointLights::Turn_Off()
	{
		if (mCursor == 0)
			return;

		if (mOn[mCursor - 1] == 1u)
		{
			mPointColor[3 * (mCursor - 1) + 0] = 0.5f;
			mPointColor[3 * (mCursor - 1) + 1] = 0.5f;
			mPointColor[3 * (mCursor - 1) + 2] = 0.5f;

			glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
			glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPointColor, GL_STATIC_DRAW);
		}

		mOn[mCursor - 1] = 0u;

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[3]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mOn, GL_STATIC_DRAW);

	

	}
	void PointLights::Render()
	{
		glBindVertexArray(mVao);
		glDrawArrays(GL_POINTS, 0, mMax_Light);
	}
	void PointLights::Load_Lights()
	{
		glBindVertexArray(mVao);
		
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat)*3, mPosition, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPointColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[2]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat), mPointSize, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (char*)NULL);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[3]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mOn, GL_STATIC_DRAW);
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, 0, (char*)NULL);
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[4]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mSelected, GL_STATIC_DRAW);
		glVertexAttribIPointer(4, 1, GL_UNSIGNED_INT, 0, (char*)NULL);
		glEnableVertexAttribArray(4);
	}
	void PointLights::Move_Forward_Cursor()
	{
		if (mCursor != 0)
		{
			mSelected[mCursor - 1] = 0u;
			if (mOn[mCursor - 1] == 1u)
			{
				mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
				mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor-1) / 255.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 1.0f;
			}
			else
			{
				mPointColor[3 * (mCursor - 1) + 0] = 0.0f;
				mPointColor[3 * (mCursor - 1) + 1] = 0.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.0f;
			}
		}
		mCursor += 1;
		if (mCursor > mMax_Light)
			mCursor = 0;
		if (mCursor != 0)
		{
			mSelected[mCursor - 1] = 1u;
			if (mOn[mCursor - 1] == 1u)
			{
				mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
				mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor - 1) / 255.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.0f;
			}
			else
			{
				mPointColor[3 * (mCursor - 1) + 0] = 0.5f;
				mPointColor[3 * (mCursor - 1) + 1] = 0.5f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.5f;
			}
		}


		glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPointColor, GL_STATIC_DRAW);
		printf("%d\n", mCursor);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[4]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mSelected, GL_STATIC_DRAW);
	}
	void PointLights::Move_Backward_Cursor()
	{
		if (mCursor != 0)
		{
			mSelected[mCursor - 1] = 0u;
			if (mOn[mCursor - 1] == 1u)
			{
				mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
				mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor - 1) / 255.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 1.0f;
			}
			else
			{
				mPointColor[3 * (mCursor - 1) + 0] = 0.0f;
				mPointColor[3 * (mCursor - 1) + 1] = 0.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.0f;
			}
		}
		mCursor -= 1;
		if (mCursor < 0)
			mCursor = mMax_Light;
		if (mCursor != 0)
		{
			mSelected[mCursor - 1] = 1u;
			if (mOn[mCursor - 1] == 1u)
			{
				mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
				mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor - 1) / 255.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.0f;
			}
			else
			{
				mPointColor[3 * (mCursor - 1) + 0] = 0.5f;
				mPointColor[3 * (mCursor - 1) + 1] = 0.5f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.5f;
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPointColor, GL_STATIC_DRAW);
		printf("%d\n", mCursor);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[4]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mSelected, GL_STATIC_DRAW);
	}
	void PointLights::Move_Forward_PositionX(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mPosition[3* (mCursor - 1) +0]+=val;

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::Move_Backward_PositionX(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mPosition[3 * (mCursor - 1) + 0] -= val;

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::Move_Forward_PositionY(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mPosition[3 * (mCursor - 1) + 1] += val;

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::Move_Backward_PositionY(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mPosition[3 * (mCursor - 1) + 1] -= val;
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::Move_Forward_PositionZ(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mPosition[3 * (mCursor - 1) + 2] += val;
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::Move_Backward_PositionZ(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mPosition[3 * (mCursor - 1) + 2] -= val;
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::Move_Forward_AmbientR(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;

		mAmbient[3 * (mCursor - 1) + 0] += val;
		if (mAmbient[3 * (mCursor - 1) + 0] > 1.0f)
			mAmbient[3 * (mCursor - 1) + 0] = 1.0f;
		else if (mAmbient[3 * (mCursor - 1) + 0] < 0.0f)
			mAmbient[3 * (mCursor - 1) + 0] = 0.0f;
	}
	void PointLights::Move_Backward_AmbientR(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mAmbient[3 * (mCursor - 1) + 0] -= val;
		if (mAmbient[3 * (mCursor - 1) + 0] > 1.0f)
			mAmbient[3 * (mCursor - 1) + 0] = 1.0f;
		else if (mAmbient[3 * (mCursor - 1) + 0] < 0.0f)
			mAmbient[3 * (mCursor - 1) + 0] = 0.0f;
	}
	void PointLights::Move_Forward_AmbientG(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mAmbient[3* (mCursor - 1) +1] += val;
		if (mAmbient[3*(mCursor-1)+1] > 1.0f)
			mAmbient[3*(mCursor-1)+1] = 1.0f;
		else if (mAmbient[3*(mCursor-1)+1] < 0.0f)
			mAmbient[3*(mCursor-1)+1] = 0.0f;

	}
	void PointLights::Move_Backward_AmbientG(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mAmbient[3* (mCursor - 1) +1] -= val;
		if (mAmbient[3* (mCursor - 1) +1] > 1.0f)
			mAmbient[3* (mCursor - 1) +1] = 1.0f;
		else if (mAmbient[3* (mCursor - 1) +1] < 0.0f)
			mAmbient[3* (mCursor - 1) +1] = 0.0f;

	}
	void PointLights::Move_Forward_AmbientB(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mAmbient[3* (mCursor - 1) +2] += val;
		if (mAmbient[3* (mCursor - 1) +2] > 1.0f)
			mAmbient[3* (mCursor - 1) +2] = 1.0f;
		else if (mAmbient[3* (mCursor - 1) +2] < 0.0f)
			mAmbient[3* (mCursor - 1) +2] = 0.0f;
	}
	void PointLights::Move_Backward_AmbientB(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mAmbient[3*(mCursor - 1) +2] -= val;
		if (mAmbient[3* (mCursor - 1) +2] > 1.0f)
			mAmbient[3* (mCursor - 1) +2] = 1.0f;
		else if (mAmbient[3* (mCursor - 1) +2] < 0.0f)
			mAmbient[3* (mCursor - 1) +2] = 0.0f;
	}
	void PointLights::Move_Forward_DiffuseR(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mDiffuse[3* (mCursor - 1) +0] += val;
		if (mDiffuse[3* (mCursor - 1) +0] > 1.0f)
			mDiffuse[3* (mCursor - 1) +0] = 1.0f;
		else if (mDiffuse[3* (mCursor - 1) +0] < 0.0f)
			mDiffuse[3*(mCursor-1)+0] = 0.0f;
	}
	void PointLights::Move_Backward_DiffuseR(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mDiffuse[3* (mCursor - 1) +0] -= val;
		if (mDiffuse[3* (mCursor - 1) +0] > 1.0f)
			mDiffuse[3*(mCursor-1)+0] = 1.0f;
		else if (mDiffuse[3* (mCursor - 1) +0] < 0.0f)
			mDiffuse[3*(mCursor-1)+0] = 0.0f;
	}
	void PointLights::Move_Forward_DiffuseG(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mDiffuse[3* (mCursor - 1) +1] += val;
		if (mDiffuse[3* (mCursor - 1) +1] > 1.0f)
			mDiffuse[3*(mCursor-1)+1] = 1.0f;
		else if (mDiffuse[3*(mCursor-1)+1] < 0.0f)
			mDiffuse[3*(mCursor-1)+1] = 0.0f;

	}
	void PointLights::Move_Backward_DiffuseG(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mDiffuse[3*(mCursor-1)+1] -= val;
		if (mDiffuse[3*(mCursor-1)+1] > 1.0f)
			mDiffuse[3*(mCursor-1)+1] = 1.0f;
		else if (mDiffuse[3*(mCursor-1)+1] < 0.0f)
			mDiffuse[3*(mCursor-1)+1] = 0.0f;
	}
	void PointLights::Move_Forward_DiffuseB(GLfloat val)
	{
		if (mCursor == 0)
			return;
		mDiffuse[3*(mCursor-1)+2] += val;
		if (mDiffuse[3*(mCursor-1)+2] > 1.0f)
			mDiffuse[3*(mCursor-1)+2] = 1.0f;
		else if (mDiffuse[3*(mCursor-1)+2] < 0.0f)
			mDiffuse[3*(mCursor-1)+2] = 0.0f;

	}
	void PointLights::Move_Backward_DiffuseB(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mDiffuse[3*(mCursor-1)+2] -= val;
		if (mDiffuse[3*(mCursor-1)+2] > 1.0f)
			mDiffuse[3*(mCursor-1)+2] = 1.0f;
		else if (mDiffuse[3*(mCursor-1)+2] < 0.0f)
			mDiffuse[3*(mCursor-1)+2] = 0.0f;

	}
	void PointLights::Move_Forward_SpecularR(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mSpecular[3*(mCursor-1)+0] += val;
		if (mSpecular[3*(mCursor-1)+0] > 1.0f)
			mSpecular[3*(mCursor-1)+0] = 1.0f;
		else if (mSpecular[3*(mCursor-1)+0] < 0.0f)
			mSpecular[3*(mCursor-1)+0] = 0.0f;
	}
	void PointLights::Move_Backward_SpecularR(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mSpecular[3*(mCursor-1)+0] -= val;
		if (mSpecular[3*(mCursor-1)+0] > 1.0f)
			mSpecular[3*(mCursor-1)+0] = 1.0f;
		else if (mSpecular[3*(mCursor-1)+0] < 0.0f)
			mSpecular[3*(mCursor-1)+0] = 0.0f;

	}
	void PointLights::Move_Forward_SpecularG(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mSpecular[3*(mCursor-1)+1] += val;
		if (mSpecular[3*(mCursor-1)+1] > 1.0f)
			mSpecular[3*(mCursor-1)+1] = 1.0f;
		else if (mSpecular[3*(mCursor-1)+1] < 0.0f)
			mSpecular[3*(mCursor-1)+1] = 0.0f;

	}
	void PointLights::Move_Backward_SpecularG(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mSpecular[3*(mCursor-1)+1] -= val;
		if (mSpecular[3*(mCursor-1)+1] > 1.0f)
			mSpecular[3*(mCursor-1)+1] = 1.0f;
		else if (mSpecular[3*(mCursor-1)+1] < 0.0f)
			mSpecular[3*(mCursor-1)+1] = 0.0f;
	}
	void PointLights::Move_Forward_SpecularB(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mSpecular[3*(mCursor-1)+2] += val;
		if (mSpecular[3*(mCursor-1)+2] > 1.0f)
			mSpecular[3*(mCursor-1)+2] = 1.0f;
		else if (mSpecular[3*(mCursor-1)+2] < 0.0f)
			mSpecular[3*(mCursor-1)+2] = 0.0f;
	}
	void PointLights::Move_Backward_SpecularB(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mSpecular[3*(mCursor-1)+2] -= val;
		if (mSpecular[3*(mCursor-1)+2] > 1.0f)
			mSpecular[3*(mCursor-1)+2] = 1.0f;
		else if (mSpecular[3*(mCursor-1)+2] < 0.0f)
			mSpecular[3*(mCursor-1)+2] = 0.0f;
	}
	void PointLights::Move_Forward_PointSize(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mPointSize[mCursor-1] += val;
		if (mPointSize[mCursor-1] < 0)
			mPointSize[mCursor-1] = 0;

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[2]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat), mPointSize, GL_STATIC_DRAW);
	}
	void PointLights::Move_Backward_PointSize(GLfloat val)
	{
		if (mCursor == 0)
			return;
		if (mOn[mCursor - 1] == 0)
			return;
		mPointSize[mCursor-1] -= val;
		if (mPointSize[mCursor-1] < 0)
			mPointSize[mCursor-1] = 0;

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[2]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat), mPointSize, GL_STATIC_DRAW);
	}
	void PointLights::ImplementLightsAtTerrain(GLuint TerrainProgram,GLuint MaterialType)
	{
		glUseProgram(TerrainProgram);
		glUniform1i(glGetUniformLocation(TerrainProgram, "Max_Light"), mMax_Light);
		glUniform3fv(glGetUniformLocation(TerrainProgram, "light.position"),mMax_Light,mPosition);
		glUniform3fv(glGetUniformLocation(TerrainProgram, "light.ambient"), mMax_Light, mAmbient);
		glUniform3fv(glGetUniformLocation(TerrainProgram, "light.diffuse"), mMax_Light,mDiffuse);
		glUniform3fv(glGetUniformLocation(TerrainProgram, "light.specular"), mMax_Light,mSpecular);
		glUniform1uiv(glGetUniformLocation(TerrainProgram, "light.On"), mMax_Light, mOn);

		// GOLD	http://devernay.free.fr/cours/opengl/materials.html
		glUniform3f(glGetUniformLocation(TerrainProgram, "material.ambient"), Material::AmbientR[MaterialType], Material::AmbientG[MaterialType], Material::AmbientB[MaterialType]);
		glUniform3f(glGetUniformLocation(TerrainProgram, "material.diffuse"), Material::DiffuseR[MaterialType], Material::DiffuseG[MaterialType], Material::DiffuseG[MaterialType]);
		glUniform3f(glGetUniformLocation(TerrainProgram, "material.specular"), Material::SpecularR[MaterialType], Material::SpecularG[MaterialType], Material::SpecularB[MaterialType]);
		glUniform1f(glGetUniformLocation(TerrainProgram, "material.shininess"), Material::Shininess[MaterialType] * 128.0f);
	}

	void PointLights::AnimateFallingLight(GLfloat minHeight, GLfloat maxHeight,GLfloat val)
	{
		for (int i = 0; i < mMax_Light; i++)
		{
			if (mOn[i] == 0u)
			{
				continue;
			}
			else
			{
				if (mState[i] == FALLING)
				{
					mPosition[3 * i + 1] -= val;
					if (mPosition[3 * i + 1] < minHeight)
					{
						mState[i] = RISING;
						mPosition[3 * i + 1] = minHeight;
					}
				}
				else if (mState[i] == RISING)
				{
					mPosition[3 * i + 1] += val;
					if (mPosition[3 * i + 1] > maxHeight)
					{
						mState[i] = FALLING;
						mPosition[3 * i + 1] = maxHeight;
					}
				}
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPosition, GL_STATIC_DRAW);
	}
	void PointLights::SetCursor(GLuint val)
	{
		if (mCursor != 0)
		{
			mSelected[mCursor - 1] = 0u;
			if (mOn[mCursor - 1] == 1u)
			{
				mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
				mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor - 1) / 255.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 1.0f;
			}
			else
			{
				mPointColor[3 * (mCursor - 1) + 0] = 0.0f;
				mPointColor[3 * (mCursor - 1) + 1] = 0.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.0f;
			}
		}
		mCursor = val;
		if (mCursor > mMax_Light)
			mCursor = 0;
		if (mCursor < 0)
			mCursor = mMax_Light;
		if (mCursor != 0)
		{
			mSelected[mCursor - 1] = 1u;
			if (mOn[mCursor - 1] == 1u)
			{
				mPointColor[3 * (mCursor - 1) + 0] = 1.0f;
				mPointColor[3 * (mCursor - 1) + 1] = (GLfloat)(mCursor - 1) / 255.0f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.0f;
			}
			else
			{
				mPointColor[3 * (mCursor - 1) + 0] = 0.5f;
				mPointColor[3 * (mCursor - 1) + 1] = 0.5f;
				mPointColor[3 * (mCursor - 1) + 2] = 0.5f;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLfloat) * 3, mPointColor, GL_STATIC_DRAW);
		printf("%d\n", mCursor);

		glBindBuffer(GL_ARRAY_BUFFER, mVbo[4]);
		glBufferData(GL_ARRAY_BUFFER, mMax_Light * sizeof(GLuint), mSelected, GL_STATIC_DRAW);
	}
	GLint PointLights::GetCursor()
	{
		return mCursor;
	}
	GLboolean PointLights::isOn(int Cursor)
	{
		if (mOn[Cursor] == 1)
			return GL_FALSE;
		else
			return GL_TRUE;
	}
}