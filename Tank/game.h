#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include "game-obj.h"

namespace hwj 
{
	// 游戏控制器
	class ShaderProgram;
	class Game 
	{
	public:
		Game();
		~Game();

	public:
		// 开始游戏
		void StartGame();

		// 结束游戏
		void StopGame();

		const bool & IsRunning() const;

	public:
		// 依次执行对象逻辑
		static void UpdateAll(GAMEEVNET gameEvent);

		// 依次渲染对象
		static void DrawAll(ShaderProgram &shader, float interpAlpha);

		// AABB 碰撞
		static bool AABBCollision(
			const GameObject &objA, const GameObject &objB);

		// 球体碰撞
		static bool SphereCollision(
			const GameObject &objA, const GameObject &objB);

		static void AddObj(ObjectTag tag, GameObject *obj);
		static GameObject * RemoveObj(ObjectTag tag);
		static std::map<ObjectTag, GameObject *> & GetObjMap();

	protected:
		static std::map<ObjectTag, GameObject *> mObjTree;
		bool mIsRunning;
	};

}

#endif // __GAME_H__
