#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "tank.h"
#include "app-debug.h"
#include "texture.h"

namespace hwj
{
	Tank::Tank(float x, float y) : 
		mWidth(60.0f), 
		mHeight(60.0f),
		mSpeed(2.0f),
		mRSpeed(1.0f),
		mVao(0),
		mVbo(0),
		mTex(0)
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
		shader.SetInt("turret", 0);
		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &mPrevModel[0][0]);
		shader.SetMat4f("model", &mModel[0][0]);

		glBindVertexArray(mVao);
		glBindTexture(GL_TEXTURE_2D, mTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// 设置矩阵
		mTurret.Draw(shader, interpAlgha);
	}

	void Tank::Update(GAMEEVNET handle)
	{
		SDL_Event *gameEvent = reinterpret_cast<SDL_Event *>(handle);

		if (!handle) {
			return;
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		// 缓存上一帧的模型矩阵
		mPrevModel = mModel;
		mTurret.mPrevModel = mPrevModel;

		// ------------- 基本操作逻辑 ---------------

		if (state[SDL_SCANCODE_W]) { Run(Tank::UP);		}
		if (state[SDL_SCANCODE_S]) { Run(Tank::DOWN);	}
		if (state[SDL_SCANCODE_A]) { Run(Tank::LEFT);	}
		if (state[SDL_SCANCODE_D]) { Run(Tank::RIGHT);	}

		// 计算坦克当前位置
		mPosition = mModel * mStartPos;

		// 设置炮塔的模型矩阵
		mTurret.Update(handle);
		mTurret.mModel = mModel;

		// -------------- 碰撞逻辑 ----------------
	}

	void Tank::Run(Action action)
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
			mModel = glm::rotate(mModel, glm::radians(mRSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mModel = glm::translate(mModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case RIGHT:
			mModel = glm::translate(mModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mModel = glm::rotate(mModel, glm::radians(-mRSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mModel = glm::translate(mModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case STOP:
		default:
			break;
		}
	}

	void Tank::SetSpeed(float speed)
	{
		mSpeed = speed;
	}

	// 设置转速
	void Tank::SetRotateSpeed(float rSpeed)
	{
		mRSpeed = rSpeed;
	}

	void Tank::Initialize()
	{
		float vertex[24] = {
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y + mHeight / 2, 1.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 1.0f, 0.0f,

			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 1.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y - mHeight / 2, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 1.0f
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
		mTex = TexLoader::GenDefTextures("res/chassis.png");

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// 初始化炮塔
		mTurret.mStartPos = mPosition;
		mTurret.Initialize();
	}

	void Tank::Terminate()
	{
		mTurret.Terminate();
		TexLoader::DelTextures(mTex);

		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);		
	}
}
