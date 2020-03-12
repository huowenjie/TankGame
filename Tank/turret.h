#ifndef __TURRET_H__
#define __TURRET_H__

#include "game-obj.h"

namespace hwj 
{
	class Tank;

	// 炮塔
	class Turret : public GameObject
	{
	public:
		friend class Tank;

		explicit Turret(Tank *chassic = nullptr);
		~Turret();

		enum Action {
			FILLING,		// 装填中
			STOP,			// 停止旋转
			LEFTROTATE,		// 左旋转
			RIGHTROTATE		// 右旋转
		};

	public:

		void SetController(Tank *chassic);

		// 绘制对象
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		void Update(GAMEEVNET handle);

		// 运行
		void Run(Action action);

		// 开火
		void Fire();

	public:

		// 初始化
		void Initialize();

		// 终止
		void Terminate();

	protected:
		unsigned int mShootInterval;	// 射击间隔 ms

		float mRotateSpeed;				// 当前炮塔转速
		float mRotateAngle;				// 炮塔旋转角度

		glm::mat4 mTurModel;			// 炮塔模型矩阵
		glm::mat4 mPrevTur;				// 上一帧炮塔模型矩阵

		Tank *mChassic;					// 所属坦克底盘
	};
}

#endif // __TURRET_H__
