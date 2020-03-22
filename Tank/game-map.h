#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "game-obj.h"

namespace hwj
{
	// ��Ϸ��ͼ
	class GameMap : public GameObject
	{
	public:
		GameMap(float x, float y, float width, float height);
		~GameMap();

		enum RollDirection {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

	public:

		// ���ƶ���
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// �߼�֡����
		void Update(GAMEEVNET handle);

		// ������һ֡
		void CachPrev();

		// �����������
		void SetCamera(const glm::mat4 &camera);

		// ���õ�ͼ�ƶ��ٶ�
		void SetCameraSpeed(float deltX, float deltY);

		// �ƶ������
		void MoveCamera(RollDirection direction);

		// �ִ��Ե���ƶ�
		void MarginMove(
			const glm::vec4 &position, float deltX, float deltY,
			float disX = 100.0f, float disY = 100.0f);

	public:

		void Initialize();
		void Terminate();

	protected:
		// ��ǰ��ͼ��������
		float mDeltX;
		float mDeltY;

		// ��ǰ��ͼ���������
		glm::mat4 mCamera;
		glm::mat4 mProjection;
		glm::mat4 mPrevProj;
	};
}

#endif // __GAME_MAP_H__
