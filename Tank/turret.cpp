#include <cmath>
#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "game.h"
#include "shell.h"

#include "app-debug.h"
#include "texture.h"

namespace hwj 
{
	Turret::Turret(Tank *chassic) : 
		GameObject("res/turret.png", 0, 0, 30.0f, 70.0f),
		mShootInterval(500U),
		isReadyFire(true),
		mShootIntervalTimer(0U),
		mRotateSpeed(1.0f),
		mRotateAngle(0.0f),
		mChassic(chassic)
	{
		mTurModel = mModel;
		mPrevTur = mModel;
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
		GameObject::Draw(shader, interpAlgha);

		shader.SetFloat("interpAlpha",	interpAlgha);
		shader.SetMat4f("prevModel",	&mPrevModel[0][0]);
		shader.SetMat4f("model",		&mModel[0][0]);

		glBindTexture(GL_TEXTURE_2D, mVertObj.mTex);
		glBindVertexArray(mVertObj.mVao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	// 更新当前位置
	void Turret::Update(GAMEEVNET handle, RoleType role)
	{
		SDL_Event *gameEvent = reinterpret_cast<SDL_Event *>(handle);

		if (!handle) {
			return;
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		mPrevModel = mModel;

		// ------------- 基本操作逻辑 ---------------

		if (role == PRIMARY_ROLE) {
			if (state[SDL_SCANCODE_Q])		{ Run(LEFTROTATE);	}
			if (state[SDL_SCANCODE_E])		{ Run(RIGHTROTATE); }
			if (state[SDL_SCANCODE_SPACE])	{ Fire();			}
		} else {
			// 通过 AI 命令操作
		}

		UpdateModel();
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

	void Turret::Fire()
	{
		Uint32 curTime = SDL_GetTicks();

		if (isReadyFire) {
			isReadyFire = false;
			LOG_INFO("Fire!\n");

			Shell *shell = new Shell(mStartPos.x, mStartPos.y);

			shell->SetTag(AllocObjTag(SHELL_TYPE));
			shell->mRun = mRun;
			shell->mShellModel = mTurModel;

			shell->mCurStatus = Shell::FLYING;
			shell->Initialize();

			Game::AddObj(shell->GetTag().mCode, shell);
			mShootIntervalTimer = SDL_GetTicks() + mShootInterval;
		} else {
			LOG_INFO("Filling!\n");
		}

		if (!SDL_TICKS_PASSED(mShootIntervalTimer, curTime)) {
			isReadyFire = true;
		}
	}

	// 初始化终止
	void Turret::Initialize() 
	{
		float vertex[24] = {
			-0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,

			 0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		GameObject::LoadVertex(vertex, sizeof(vertex) / sizeof(float));
		GameObject::Initialize();

		// 初始化物体位置
		mTranslate = glm::translate(mTranslate, glm::vec3(0, mSize.mY / 6, 0.0f));
		mModel = mTranslate * mRotate * mScale;
		mPrevModel = mModel;

		if (!GameObject::IsVertexObjExist(TURRET_TYPE)) {
			GameObject::AddVertexObj(TURRET_TYPE, mVertObj);
		}
	}

	void Turret::Terminate()
	{
		GameObject::Terminate();
	}

	void Turret::UpdateModel()
	{
		mModel = mRun * mTurModel * mTranslate * mRotate * mScale;
	}
}
