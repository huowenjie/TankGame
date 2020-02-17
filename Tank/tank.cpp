#include "tank.h"
#include "app-debug.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hwj 
{
	Tank::Tank(float x, float y) : 
		mWidth(60.0f), 
		mHeight(60.0f),
		mSpeed(2.0f)
	{
		mModel = glm::mat4(1.0f);
		mPrevModel = glm::mat4(1.0f);

		mStartPos.x = x;
		mStartPos.y = y;
		mStartPos.z = 0.0f;
		mStartPos.w = 1.0f;
		mPosition = mStartPos;
	}

	Tank::~Tank() 
	{
	}

	void Tank::Draw(ShaderProgram &shader, float interpAlgha)
	{
		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &mPrevModel[0][0]);
		shader.SetMat4f("model", &mModel[0][0]);

		glBindVertexArray(mVao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Tank::Update(WINDOWHANDLE handle)
	{
		if (!handle) {
			return;
		}
		GLFWwindow *win = (GLFWwindow *)handle;

		// 缓存上一帧的模型矩阵
		mPrevModel = mModel;

		// ------------- 基本操作逻辑 ---------------

		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) { Move(Tank::UP);   }
		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) { Move(Tank::DOWN); }
		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) { Move(Tank::LEFT); }
		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) { Move(Tank::RIGHT);}

		mPosition = mModel * mStartPos;
	}

	void Tank::Move(Action action)
	{
		switch (action) {
		case UP:
			mModel = glm::translate(mModel, glm::vec3(0, mSpeed, 0.0f));
			break;
		case DOWN:
			mModel = glm::translate(mModel, glm::vec3(0, -mSpeed, 0.0f));
			break;
		case LEFT:
			mModel = glm::translate(mModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mModel = glm::rotate(mModel, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			mModel = glm::translate(mModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case RIGHT:
			mModel = glm::translate(mModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mModel = glm::rotate(mModel, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			mModel = glm::translate(mModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		default:
			break;
		}
	}

	void Tank::SetSpeed(int speed)
	{
		mSpeed = (float)speed;
	}

	void Tank::Initialize()
	{
		float vertex[24] = {
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 0.0f,
			mStartPos.x + mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 0.0f,
			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 0.0f, 0.0f,

			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y - mHeight / 2, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 0.0f
		};

		// 创建顶点缓冲对象
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Tank::Terminate()
	{
		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);
	}
}
