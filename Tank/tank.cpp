#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "tank.h"
#include "app-debug.h"
#include "texture.h"
#include "game.h"
#include "game-map.h"

namespace hwj
{
	Tank::Tank(RoleType type, float x, float y) :
		GameObject("res/chassis.png", x, y, 60.0f, 60.0f),
		mType(type),
		mSpeed(5.0f),
		mRSpeed(1.0f),
		mMap(nullptr)
	{
	}

	Tank::~Tank() 
	{
	}

	void Tank::Draw(ShaderProgram &shader, float interpAlgha)
	{
		GameObject::Draw(shader, interpAlgha);

		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &mPrevModel[0][0]);
		shader.SetMat4f("model", &mModel[0][0]);

		glBindVertexArray(mVertObj.mVao);
		glBindTexture(GL_TEXTURE_2D, mVertObj.mTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// ���þ���
		mTurret.Draw(shader, interpAlgha);
	}

	void Tank::Update(GAMEEVNET handle)
	{
		// ������һ֡������
		mPrevModel = mModel;
		mPrevRun = mRun;
		mPrevPos = mPosition;

		mTurret.mPrevRun = mRun;

		// ------------- ���������߼� ---------------

		if (mType == PRIMARY_ROLE) {

			// ֻ�вٿ��߽�ɫ���Կ��Ƶ�ͼ���ƶ�
			if (mMap) {
				// �����ͼ����һ֡
				mMap->CachPrev();
			}

			UpdatePrimary(handle);
		} else if (mType == ENEMY_ROLE) {
			// ����̹�ˣ��Զ�����
			UpdateEnemy(handle);
		} else if (mType == NPC_ROLE) {
			// NPC
		} else {
			// ����
		}

		// ����������ģ�;���
		mTurret.mRun = mRun;
		mTurret.Update(handle, mType);

		// ----------����̹�˵�ǰλ��---------------

		GameObject::Update(handle);

		// -------------- ��ײ�߼� ----------------

		// ��ײ���

		std::map<ObjectCode, GameObject *> objs = Game::GetObjMap();
		std::map<ObjectCode, GameObject *>::const_iterator it =
			objs.begin();

		// ��ʱ���ô˷������Ժ����Ż�
		for (; it != objs.end(); ++it) {
			if (it->first == mTag.mCode) {
				continue;
			}

			GameObject *elem = it->second;

			if (Game::SphereCollision(*this, *elem)) {
				mModel = mPrevModel;
				mTurret.mModel = mTurret.mPrevModel;
				mRun = mPrevRun;
				mTurret.mRun = mPrevRun;
				LOG_INFO("Tank Collision!\n");
			}
		}
	}

	void Tank::UpdatePrimary(GAMEEVNET handle)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_W]) { Run(Tank::UP,		true); }
		if (state[SDL_SCANCODE_S]) { Run(Tank::DOWN,	true); }
		if (state[SDL_SCANCODE_A]) { Run(Tank::LEFT,	true); }
		if (state[SDL_SCANCODE_D]) { Run(Tank::RIGHT,	true); }
	}

	void Tank::UpdateEnemy(GAMEEVNET handle) 
	{
		// ��ȡ��������˶�
		Run(UP, false);
		Run(LEFT, false);
	}

	void Tank::UpdateNpc(GAMEEVNET handle) 
	{
	
	}

	void Tank::Run(Action action, bool isUpdateMap)
	{
		switch (action) {
		case UP:
			mRun = glm::translate(mRun, glm::vec3(0, mSpeed, 0.0f));
			break;
		case DOWN:
			mRun = glm::translate(mRun, glm::vec3(0, -mSpeed, 0.0f));
			break;
		case LEFT:
			mRun = glm::translate(mRun, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mRun = glm::rotate(mRun, glm::radians(mRSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mRun = glm::translate(mRun, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case RIGHT:
			mRun = glm::translate(mRun, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mRun = glm::rotate(mRun, glm::radians(-mRSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mRun = glm::translate(mRun, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case STOP:
		default:
			break;
		}

		// ����ģ�;���
		mModel = mRun * mTranslate * mRotate * mScale;
		mPosition = mRun * mStartPos;

		if (isUpdateMap && mMap) {
			// ��֤ delt Ϊ��
			float deltX = mPosition.x > mPrevPos.x ?
				(mPosition.x - mPrevPos.x) : (mPrevPos.x - mPosition.x);
			float deltY = mPosition.y > mPrevPos.y ?
				(mPosition.y - mPrevPos.y) : (mPrevPos.y - mPosition.y);

			// �����߽��ƶ���ͼ
			mMap->MarginMove(mPosition, deltX, deltY, 100.0f, 100.0f);
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

	void Tank::SetMap(GameMap *gameMap)
	{
		mMap = gameMap;
	}

	void Tank::Initialize()
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

		if (!GameObject::IsVertexObjExist(TANK_TYPE)) {
			GameObject::AddVertexObj(TANK_TYPE, mVertObj);
		}

		// ��ʼ������
		mTurret.mStartPos = mPosition;
		mTurret.SetTag(AllocObjTag(TURRET_TYPE));
		mTurret.Initialize();
	}

	void Tank::Terminate()
	{
		// �ͷ�����
		mTurret.Terminate();
		GameObject::Terminate();
	}
}
