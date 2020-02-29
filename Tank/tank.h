#ifndef __TANK_H__
#define __TANK_H__

#include "turret.h"

namespace hwj 
{
	class Tank : public GameObject
	{
	public:
		Tank(RoleType type, float x = 400.0f, float y = 300.0f);
		~Tank();

		enum Action {
			UP,
			DOWN,
			LEFT,
			RIGHT,
			STOP
		};

	public:

		// 绘制对象
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		void Update(GAMEEVNET handle);

		// 移动
		void Run(Action action);

		// 设置移速
		void SetSpeed(float speed);

		// 设置转速
		void SetRotateSpeed(float rSpeed);

	public:
		// 初始化
		void Initialize();
		void Terminate();

	protected:
		RoleType mType;			// 角色类型

		float mSpeed;			// 当前移动速度
		float mRSpeed;			// 底盘旋转速度

		Turret mTurret;			// 所属炮塔
	};
}

#endif // __TANK_H__
