#ifndef __GAME_OBJ_H__
#define __GAME_OBJ_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "global.h"
#include "shader.h"
#include "game-math.h"

namespace hwj
{
	// 游戏对象
	class GameObject 
	{
	public:
		GameObject(
			const std::string &resPath, float startX, float startY,
			float width,  float height);

		virtual ~GameObject();

	public:
		// 设置对象标识
		void SetTag(ObjectTag tag);

		// 获取对象标识
		ObjectTag GetTag() const;

		// 绘制对象
		virtual void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		virtual void Update(GAMEEVNET handle);

	public:
		// 初始化
		virtual void Initialize(float *vertex, int num);
		virtual void Terminate();

		// 获取当前对象坐标
		Vector2D<float> GetPosition() const;

		// 获取包围盒数据
		const Vector4D<float> & GetAABB() const;

		// 获取包围求数据
		const Vector3D<float> & GetBoundingSphere() const;

	protected:

		// 销毁自身
		void DestroySelf();

	protected:
		ObjectTag mTag;

		float mWidth;			// 宽
		float mHeight;			// 高

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		glm::mat4 mModel;		// 模型矩阵
		glm::mat4 mPrevModel;	// 上一帧矩阵数据
		glm::vec4 mPosition;	// 位置
		glm::vec4 mStartPos;	// 初始位置

		Vector4D<float> mAABB;	// 包围盒
		Vector3D<float> mSphere;// 包围球

		std::string mResPath;	// 资源路径
	};
}

#endif // __GAME_OBJ_H__
