#ifndef __GAME_OBJ_H__
#define __GAME_OBJ_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <map>

#include "global.h"
#include "shader.h"
#include "game-math.h"

namespace hwj
{
	// 顶点缓存对象
	class VertexObj
	{
	public:
		VertexObj() : mVao(0), mVbo(0), mTex(0) {}
		~VertexObj() {}

		void LoadDefVertex(float *vertex, uint32_t num);
		void UnLoadDefVertex();

		uint32_t mVao;
		uint32_t mVbo;
		uint32_t mTex;
	};

	// 游戏对象
	class GameObject 
	{
	public:
		GameObject(
			float startX, float startY, float width, float height);
		GameObject(
			const std::string &resPath, float startX, float startY,
			float width,  float height);

		virtual ~GameObject();

	public:
		// 设置对象标识
		void SetTag(const ObjectTag &tag);

		// 获取对象标识
		ObjectTag GetTag() const;

		// 绘制对象
		virtual void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		virtual void Update(GAMEEVNET handle);

	public:
		// 初始化
		virtual void LoadVertex(float *vertex, uint32_t num);
		virtual void Initialize();
		virtual void Terminate();

		// 获取当前对象坐标
		Vector2D<float> GetPosition() const;

		// 获取包围盒数据
		const Vector4D<float> & GetAABB() const;

		// 获取包围求数据
		const Vector3D<float> & GetBoundingSphere() const;

		// 顶点列表操作
		static void AddVertexObj(ObjectType type, const VertexObj &obj);
		static void RemoveVertexObj(ObjectType type);
		static bool IsVertexObjExist(ObjectType type);
		static void RemoveAllVertexObj();

	protected:

		// 销毁自身
		void DestroySelf();

	protected:
		ObjectTag mTag;

		VertexObj mVertObj;		// 顶点对象

		glm::mat4 mModel;		// 模型矩阵
		glm::mat4 mPrevModel;	// 上一帧矩阵数据

		glm::mat4 mTranslate;	// 平移矩阵
		glm::mat4 mRotate;		// 旋转矩阵
		glm::mat4 mScale;		// 缩放矩阵

		glm::mat4 mRun;			// 运动矩阵
		glm::mat4 mPrevRun;		// 上一帧矩阵，用于碰撞还原

		glm::vec4 mPosition;	// 位置
		glm::vec4 mPrevPos;		// 上一帧位置，用于地图滚动
		glm::vec4 mStartPos;	// 初始位置

		Vector4D<float> mAABB;	// 包围盒
		Vector3D<float> mSphere;// 包围球
		Vector2D<float> mSize;	// 对象尺寸

		std::string mResPath;	// 资源路径

		// 顶点缓冲区
		static std::map<ObjectType, VertexObj> mBufferes;
	};
}

#endif // __GAME_OBJ_H__
