#ifndef __TURRET_H__
#define __TURRET_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"
#include "shader.h"

namespace hwj 
{
	class Tank;
	// 炮塔
	class Turret 
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
		void Update(WINDOWHANDLE handle);

		// 运行
		void Run(Action action);

	public:
		// 初始化终止
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// 宽
		float mHeight;			// 高

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		float mRotateSpeed;		// 当前炮塔转速
		float mRotateAngle;		// 炮塔旋转角度

		glm::mat4 mModel;		// 底盘模型矩阵
		glm::mat4 mPrevModel;	// 上一帧矩阵数据
		glm::mat4 mTurModel;	// 炮塔模型矩阵
		glm::mat4 mPrevTur;		// 上一帧炮塔模型矩阵
		glm::vec4 mStartPos;	// 初始位置

		Tank *mChassic;			// 所属坦克底盘
	};
}

#endif // __TURRET_H__
