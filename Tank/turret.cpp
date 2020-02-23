#include "turret.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "app-debug.h"
#include "texture.h"

namespace hwj 
{
	Turret::Turret(Tank *chassic) :
		mWidth(30.0f),
		mHeight(70.0f),
		mVao(0),
		mVbo(0),
		mTex(0),
		mRotateSpeed(1.0f),
		mChassic(chassic)
	{
		mModel = glm::mat4(1.0f);
		mPrevModel = mModel;
		mTurModel = mModel;
		mPrevTur = mModel;

		mStartPos.x = 0.0f;
		mStartPos.y = 0.0f;
		mStartPos.z = 0.0f;
		mStartPos.w = 0.0f;
	}

	Turret::~Turret()
	{
	}

	void Turret::SetController(Tank *chassic)
	{
		mChassic = chassic;
	}

	// 绘制对象
	void Turret::Draw(ShaderProgram &shader, float interpAlgha)
	{
		shader.SetInt("turret", 1);
		shader.SetFloat("interpAlpha",	interpAlgha);
		shader.SetMat4f("prevModel",	&mPrevModel[0][0]);
		shader.SetMat4f("model",		&mModel[0][0]);
		shader.SetMat4f("turModel",		&mTurModel[0][0]);
		shader.SetMat4f("prevTur",		&mPrevTur[0][0]);

		glBindTexture(GL_TEXTURE_2D, mTex);
		glBindVertexArray(mVao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	// 更新当前位置
	void Turret::Update(WINDOWHANDLE handle)
	{
		if (!handle) {
			return;
		}
		GLFWwindow *win = (GLFWwindow *)handle;

		mPrevTur = mTurModel;

		if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) { Run(LEFTROTATE);  }
		if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS) { Run(RIGHTROTATE); }
	}

	// 旋转
	void Turret::Run(Action action) 
	{
		switch (action)
		{
		case LEFTROTATE:
			mTurModel = glm::translate(mTurModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mTurModel = glm::rotate(mTurModel, glm::radians(mRotateSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mTurModel = glm::translate(mTurModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;

		case RIGHTROTATE:
			mTurModel = glm::translate(mTurModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mTurModel = glm::rotate(mTurModel, glm::radians(-mRotateSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mTurModel = glm::translate(mTurModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;

		default:
			break;
		}
	}

	// 初始化终止
	void Turret::Initialize() 
	{
		float vertex[24] = {
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2 + 12.0f, 0.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y + mHeight / 2 + 12.0f, 1.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2 + 12.0f, 1.0f, 0.0f,

			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2 + 12.0f, 1.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y - mHeight / 2 + 12.0f, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2 + 12.0f, 0.0f, 1.0f
		};

		// 创建顶点缓冲对象
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 加载纹理文件
		mTex = TexLoader::GenDefTextures("res/turret.png");

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Turret::Terminate() 
	{
		TexLoader::DelTextures(mTex);

		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);
	}
}
