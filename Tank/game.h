#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include "game-obj.h"

namespace hwj 
{
	// ��Ϸ������
	class ShaderProgram;
	class Game 
	{
	public:
		Game();
		~Game();

	public:
		// ��ʼ��Ϸ
		void StartGame();

		// ������Ϸ
		void StopGame();

		const bool & IsRunning() const;

	public:
		// ����ִ�ж����߼�
		static void UpdateAll(GAMEEVNET gameEvent);

		// ������Ⱦ����
		static void DrawAll(ShaderProgram &shader, float interpAlpha);

		// AABB ��ײ
		static bool AABBCollision(
			const GameObject &objA, const GameObject &objB);

		// ������ײ
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
