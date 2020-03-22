#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "game-obj.h"

namespace hwj
{
	// 游戏地图
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

		// 绘制对象
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 逻辑帧更新
		void Update(GAMEEVNET handle);

		// 缓存上一帧
		void CachPrev();

		// 设置相机矩阵
		void SetCamera(const glm::mat4 &camera);

		// 设置地图移动速度
		void SetCameraSpeed(float deltX, float deltY);

		// 移动摄像机
		void MoveCamera(RollDirection direction);

		// 抵达边缘后移动
		void MarginMove(
			const glm::vec4 &position, float deltX, float deltY,
			float disX = 100.0f, float disY = 100.0f);

	public:

		void Initialize();
		void Terminate();

	protected:
		// 当前地图滚动距离
		float mDeltX;
		float mDeltY;

		// 当前地图摄像机矩阵
		glm::mat4 mCamera;
		glm::mat4 mProjection;
		glm::mat4 mPrevProj;
	};
}

#endif // __GAME_MAP_H__
