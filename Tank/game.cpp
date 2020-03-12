#include <cmath>

#include "game.h"
#include "shader.h"
#include "tank.h"
#include "shell.h"
#include "texture.h"
#include "anim-frame.h"

namespace hwj 
{
	std::map<ObjectCode, GameObject *> Game::mObjTree;

	Game::Game() : mIsRunning(false)
	{
	}
	
	Game::~Game() 
	{
	}

	void Game::StartGame()
	{
		Tank *tank = new Tank(PRIMARY_ROLE);
		tank->SetTag(AllocObjTag(TANK_TYPE));
		tank->Initialize();

		Tank *enemy = new Tank(ENEMY_ROLE, 200.0f, 400.0f);
		enemy->SetTag(AllocObjTag(TANK_TYPE));
		enemy->Initialize();

		Animation *anim = new Animation(400.0f, 542.0f);
		anim->SetAnimTexInfo(GenAnimTextures("res/explode.png"));
		anim->SetTag(AllocObjTag(ANIM_TYPE));
		anim->Initialize();
		anim->SetLoopMode(true);
		anim->Play();

		AddObj(tank->GetTag().mCode,  tank);
		AddObj(enemy->GetTag().mCode, enemy);
		AddObj(anim->GetTag().mCode,  anim);

		mIsRunning = true;
	}

	void Game::StopGame()
	{
		mIsRunning = false;

		std::map<ObjectCode, GameObject *> &objTree = GetObjMap();
		std::map<ObjectCode, GameObject *>::iterator it =
			objTree.begin();

		while (!objTree.empty() && it != objTree.end()) {
			GameObject *obj = it->second;
			
			if (obj) {
				obj->Terminate();
				delete obj;
				objTree.erase(it);
			}

			it = objTree.begin();
		}
	}

	const bool & Game::IsRunning() const
	{
		return mIsRunning;
	}

	void Game::UpdateAll(GAMEEVNET gameEvent) 
	{
		size_t size = mObjTree.size();

		std::map<ObjectCode, GameObject *>::iterator it = mObjTree.begin();
		std::map<ObjectCode, GameObject *>::iterator tmp;

		// 游戏控制逻辑，比如操作对象移动
		while (it != mObjTree.end()) {
			tmp = it;
			++it;
			tmp->second->Update(gameEvent);
		}
	}

	void Game::DrawAll(ShaderProgram &shader, float interpAlpha)
	{
		// 游戏对象渲染
		for (std::map<ObjectCode, GameObject *>::iterator it = mObjTree.begin();
			it != mObjTree.end(); ++it) {
			it->second->Draw(shader, interpAlpha);
		}
	}

	bool Game::AABBCollision(
		const GameObject &objA, const GameObject &objB) 
	{
		const Vector4D<float> & aAABB = objA.GetAABB();
		const Vector4D<float> & bAABB = objB.GetAABB();

		bool test = 
			(aAABB.mB < bAABB.mA) || (bAABB.mB < aAABB.mA) ||
			(aAABB.mC > bAABB.mD) || (bAABB.mC > aAABB.mD);

		return !test;
	}

	bool Game::SphereCollision(
		const GameObject &objA, const GameObject &objB)
	{
		const Vector3D<float> & aSphere = objA.GetBoundingSphere();
		const Vector3D<float> & bSphere = objB.GetBoundingSphere();

		float distSquared = 
			std::powf(aSphere.mX - bSphere.mX, 2) +
			std::powf(aSphere.mY - bSphere.mY, 2);

		return distSquared <= std::powf(aSphere.mZ + bSphere.mZ, 2);
	}

	void Game::AddObj(ObjectCode code, GameObject *obj)
	{
		if (obj) {
			mObjTree.insert(
				std::map<ObjectCode, GameObject *>::value_type(code, obj));
		}
	}

	GameObject * Game::RemoveObj(ObjectCode code)
	{
		if (mObjTree.empty()) {
			return nullptr;
		}

		std::map<ObjectCode, GameObject *>::iterator it = mObjTree.find(code);
		GameObject *ret = it->second;

		mObjTree.erase(it);
		return ret;
	}

	std::map<ObjectCode, GameObject *> & Game::GetObjMap()
	{
		return mObjTree;
	}
}
