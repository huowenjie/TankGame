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

		// 设置矩阵
		mTurret.Draw(shader, interpAlgha);
	}

	void Tank::Update(GAMEEVNET handle)
	{
		// 缓存上一帧的数据
		mPrevModel = mModel;
		mPrevRun = mRun;
		mPrevPos = mPosition;

		mTurret.mPrevRun = mRun;

		// ------------- 基本操作逻辑 ---------------

		if (mType == PRIMARY_ROLE) {

			// 只有操控者角色可以控制地图的移动
			if (mMap) {
				// 缓存地图的上一帧
				mMap->CachPrev();
			}

			UpdatePrimary(handle);
		} else if (mType == ENEMY_ROLE) {
			// 敌人坦克，自动运行
			UpdateEnemy(handle);
		} else if (mType == NPC_ROLE) {
			// NPC
		} else {
			// 其他
		}

		// 设置炮塔的模型矩阵
		mTurret.mRun = mRun;
		mTurret.Update(handle, mType);

		// ----------计算坦克当前位置---------------

		GameObject::Update(handle);

		// -------------- 碰撞逻辑 ----------------

		// 碰撞检测

		std::map<ObjectCode, GameObject *> objs = Game::GetObjMap();
		std::map<ObjectCode, GameObject *>::const_iterator it =
			objs.begin();

		// 暂时先用此方法，以后再优化
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
		// 获取命令后在运动
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

		// 更新模型矩阵
		mModel = mRun * mTranslate * mRotate * mScale;
		mPosition = mRun * mStartPos;

		if (isUpdateMap && mMap) {
			// 保证 delt 为正
			float deltX = mPosition.x > mPrevPos.x ?
				(mPosition.x - mPrevPos.x) : (mPrevPos.x - mPosition.x);
			float deltY = mPosition.y > mPrevPos.y ?
				(mPosition.y - mPrevPos.y) : (mPrevPos.y - mPosition.y);

			// 超过边界移动地图
			mMap->MarginMove(mPosition, deltX, deltY, 100.0f, 100.0f);
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

		// 初始化炮塔
		mTurret.mStartPos = mPosition;
		mTurret.SetTag(AllocObjTag(TURRET_TYPE));
		mTurret.Initialize();
	}

	void Tank::Terminate()
	{
		// 释放炮塔
		mTurret.Terminate();
		GameObject::Terminate();
	}
}
