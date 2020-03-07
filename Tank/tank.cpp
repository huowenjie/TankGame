#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "tank.h"
#include "app-debug.h"
#include "texture.h"
#include "game.h"

namespace hwj
{
	Tank::Tank(RoleType type, float x, float y) :
		GameObject("res/chassis.png", x, y, 60.0f, 60.0f),
		mType(type),
		mSpeed(2.0f),
		mRSpeed(1.0f)
	{
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

		// ���þ���
		mTurret.Draw(shader, interpAlgha);
	}

	void Tank::Update(GAMEEVNET handle)
	{
		SDL_Event *gameEvent = reinterpret_cast<SDL_Event *>(handle);

		if (!handle) {
			return;
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		// ������һ֡��ģ�;���
		mPrevModel = mModel;
		mTurret.mPrevModel = mPrevModel;

		// ------------- ���������߼� ---------------

		if (mType == PRIMARY_ROLE) {
			if (state[SDL_SCANCODE_W]) { Run(Tank::UP); }
			if (state[SDL_SCANCODE_S]) { Run(Tank::DOWN); }
			if (state[SDL_SCANCODE_A]) { Run(Tank::LEFT); }
			if (state[SDL_SCANCODE_D]) { Run(Tank::RIGHT); }

			// ����������ģ�;���
			mTurret.Update(handle);
			mTurret.mModel = mModel;
		} else if (mType == ENEMY_ROLE) {
			// ����̹�ˣ��Զ�����
		} else if (mType == NPC_ROLE) {
			// NPC
		} else {
			// ����
		}

		// ----------����̹�˵�ǰλ��---------------

		mPosition = mModel * mStartPos;

		GameObject::Update(handle);

		// -------------- ��ײ�߼� ----------------

		// ��ײ���

		std::map<ObjectTag, GameObject *> objs = Game::GetObjMap();
		std::map<ObjectTag, GameObject *>::const_iterator it =
			objs.begin();

		// ��ʱ���ô˷������Ժ����Ż�
		for (; it != objs.end(); ++it) {
			if (it->first == mTag) {
				continue;
			}

			GameObject *elem = it->second;

			if (Game::SphereCollision(*this, *elem)) {
				mModel = mPrevModel;
				mTurret.mModel = mPrevModel;
				LOG_INFO("Collision!\n");
			}
		}
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

	// ����ת��
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

		GameObject::Initialize(vertex, sizeof(vertex) / sizeof(float));

		// ��ʼ������
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
