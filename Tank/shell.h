#ifndef __SHELL_H__
#define __SHELL_H__

#include <vector>
#include "turret.h"

namespace hwj 
{
	// 炮弹
	class Shell : public GameObject
	{
	public:
		friend class Turret;

		Shell(float x = 0.0f, float y = 0.0f);
		~Shell();

		enum Status {
			AWAIT,		// 待命
			FLYING,		// 射击飞行过程
			EXPLODE,	// 爆炸
			STRIKE,		// 撞击
			DESTROY		// 被系统回收
		};

	public:
		// 绘制对象
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		void Update(WINDOWHANDLE handle);

		// 设置移速
		void SetSpeed(float speed);

		// 炮弹是否超出范围
		bool IsOutOfRange() const;

	public:
		// 初始化
		void Initialize();
		void Terminate();

	protected:
		glm::mat4 mShellModel;	// 炮弹位置模型矩阵
		glm::mat4 mPrevShell;	// 上一帧炮弹模型矩阵
		glm::vec4 mShootPos;	// 发射位置

		float  mRange;			// 射程
		float  mSpeed;			// 当前移动速度
		Status mCurStatus;		// 当前状态
	};
}

#endif // __SHELL_H__
