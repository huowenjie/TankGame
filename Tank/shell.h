#ifndef __SHELL_H__
#define __SHELL_H__

#include "turret.h"

namespace hwj 
{
	// 炮弹
	class Shell
	{
	public:
		Shell();
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
		void SetSpeed(int speed);

	public:
		// 初始化
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// 宽
		float mHeight;			// 高

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		float mSpeed;			// 当前移动速度

		glm::mat4 mModel;		// 模型矩阵
		glm::mat4 mPrevModel;	// 上一帧矩阵数据
		glm::vec4 mPosition;	// 位置
		glm::vec4 mStartPos;	// 初始位置
	};
}

#endif // __SHELL_H__
