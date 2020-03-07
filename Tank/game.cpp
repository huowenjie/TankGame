#include <cmath>

#include "game.h"
#include "shader.h"
#include "tank.h"
#include "shell.h"

namespace hwj 
{
	std::map<ObjectTag, GameObject *> Game::mObjTree;

	Game::Game() : mIsRunning(false)
	{
	}
	
	Game::~Game() 
	{
	}

	void Game::StartGame()
	{
		Tank *tank = new Tank(PRIMARY_ROLE);
		tank->SetTag(AllocPrimaryTag());
		tank->Initialize();

		Tank *enemy = new Tank(ENEMY_ROLE, 200.0f, 400.0f);
		enemy->SetTag(AllocPrimaryTag());
		enemy->Initialize();

		AddObj(tank->GetTag(), tank);
		AddObj(enemy->GetTag(), enemy);

		mIsRunning = true;
	}

	void Game::StopGame()
	{
		mIsRunning = false;

		std::map<ObjectTag, GameObject *> &objTree = GetObjMap();
		std::map<ObjectTag, GameObject *>::iterator it =
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

		std::map<ObjectTag, GameObject *>::iterator it = mObjTree.begin();
		std::map<ObjectTag, GameObject *>::iterator tmp;

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
		for (std::map<ObjectTag, GameObject *>::iterator it = mObjTree.begin();
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

	void Game::AddObj(ObjectTag tag, GameObject *obj)
	{
		if (obj) {
			mObjTree.insert(
				std::map<ObjectTag, GameObject *>::value_type(tag, obj));
		}
	}

	GameObject * Game::RemoveObj(ObjectTag tag)
	{
		if (mObjTree.empty()) {
			return nullptr;
		}

		std::map<ObjectTag, GameObject *>::iterator it = mObjTree.find(tag);
		GameObject *ret = it->second;

		mObjTree.erase(it);
		return ret;
	}

	std::map<ObjectTag, GameObject *> & Game::GetObjMap()
	{
		return mObjTree;
	}
}
