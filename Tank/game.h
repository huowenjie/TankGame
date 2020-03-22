#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "game-obj.h"

namespace hwj 
{
	class GameMap;
	class ShaderProgram;

	// ��Ϸ������
	class Game 
	{
	public:
		Game();
		~Game();

	public:
		// ����/�Ƴ���Ϸ��ͼ
		static void SetGameMap(GameMap *gameMap);

		// ���������
		void SetCamera(glm::mat4 &camera);

		// ��ʼ��Ϸ
		void StartGame();

		// ������Ϸ
		void StopGame();

		// �Ƿ�������
		const bool & IsRunning() const;

	public:
		static void RollMap(GAMEEVNET gameEvent);
		static void DrawMap(ShaderProgram &shader, float interpAlpha);

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

		static void AddObj(ObjectCode code, GameObject *obj);
		static GameObject * RemoveObj(ObjectCode code);
		static std::map<ObjectCode, GameObject *> & GetObjMap();

	protected:
		static std::map<ObjectCode, GameObject *> mObjTree;
		static GameMap *mMap;

		bool mIsRunning;
	};
}

#endif // __GAME_H__
