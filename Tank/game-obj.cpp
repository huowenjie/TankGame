#include <glad/glad.h>
#include <cmath>

#include "game-obj.h"
#include "texture.h"
#include "game.h"

namespace hwj 
{
	std::map<ObjectType, VertexObj> GameObject::mBufferes;

	void VertexObj::LoadDefVertex(float *vertex, uint32_t num)
	{
		if (!vertex || num <= 0) {
			return;
		}

		// 创建顶点缓冲对象
		glCreateVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glCreateBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glNamedBufferStorage(mVbo, num * sizeof(float), vertex, GL_DYNAMIC_STORAGE_BIT);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexObj::UnLoadDefVertex()
	{
		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);
	}

	GameObject::GameObject(
		float startX, float startY, float width, float height)
	{
		mModel = glm::mat4(1.0f);
		mPrevModel = mModel;

		mTranslate = mModel;
		mRotate = mModel;
		mScale = mModel;
		mRun = mModel;
		mPrevRun = mModel;

		mStartPos.x = startX;
		mStartPos.y = startY;
		mStartPos.z = 0.0f;
		mStartPos.w = 1.0f;
		mPosition = mStartPos;
		mPrevPos = mStartPos;

		// 设置外接圆半径
		mSphere.mZ =
			((width > height) ? height : width) / 2.0f;

		mSize.mX = width;
		mSize.mY = height;
	}

	GameObject::GameObject(
		const std::string &resPath, float startX, float startY,
		float width, float height) :
		mResPath(resPath)
	{
		mModel = glm::mat4(1.0f);
		mPrevModel = mModel;

		mTranslate = mModel;
		mRotate = mModel;
		mScale = mModel;
		mRun = mModel;
		mPrevRun = mModel;

		mStartPos.x = startX;
		mStartPos.y = startY;
		mStartPos.z = 0.0f;
		mStartPos.w = 1.0f;
		mPosition = mStartPos;
		mPrevPos = mStartPos;
		
		// 设置外接圆半径
		mSphere.mZ = 
			((width > height) ? height : width) / 2.0f;

		mSize.mX = width;
		mSize.mY = height;
	}

	GameObject::~GameObject() 
	{
	}

	void GameObject::SetTag(const ObjectTag &tag)
	{
		mTag = tag;
	}

	ObjectTag GameObject::GetTag() const
	{
		return mTag;
	}

	void GameObject::Draw(ShaderProgram &shader, float interpAlgha)
	{
	}

	// 更新当前位置
	void GameObject::Update(GAMEEVNET handle)
	{
		// 更新包围盒子
		mAABB.mA = mPosition.x - mSize.mX / 2;
		mAABB.mB = mPosition.x + mSize.mX / 2;
		mAABB.mC = mPosition.y - mSize.mY / 2;
		mAABB.mD = mPosition.y + mSize.mY / 2;

		// 更新包围球
		mSphere.mX = mPosition.x;
		mSphere.mY = mPosition.y;
	}

	void GameObject::LoadVertex(float *vertex, uint32_t num)
	{
		std::map<ObjectType, VertexObj>::iterator it =
			mBufferes.find(mTag.mType);

		if (it != mBufferes.end()) {
			mVertObj.mVao = it->second.mVao;
			mVertObj.mVbo = it->second.mVbo;
			mVertObj.mTex = it->second.mTex;
		}
		else {
			// 加载默认顶点
			mVertObj.LoadDefVertex(vertex, num);

			// 加载纹理文件
			if (!glIsTexture(mVertObj.mTex) && !mResPath.empty()) {
				mVertObj.mTex = GenDefTextures(mResPath.c_str());
			}
		}
	}

	void GameObject::Initialize()
	{
		// 初始化物体位置
		mTranslate = glm::translate(mTranslate, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
		mScale = glm::scale(mScale, glm::vec3(mSize.mX, mSize.mY, 0.0f));
		mModel = mTranslate * mRotate * mScale;
		mPrevModel = mModel;
	}

	void GameObject::Terminate()
	{
		if (!GameObject::IsVertexObjExist(mTag.mType)) {
			DelTextures(mVertObj.mTex);
			mVertObj.UnLoadDefVertex();
		}
	}

	Vector2D<float> GameObject::GetPosition() const
	{
		return Vector2D<float>(mPosition.x, mPosition.y);
	}

	const Vector4D<float> & GameObject::GetAABB() const
	{
		return mAABB;
	}

	const Vector3D<float> & GameObject::GetBoundingSphere() const
	{
		return mSphere;
	}

	void GameObject::AddVertexObj(ObjectType type, const VertexObj &obj)
	{
		if (!IsVertexObjExist(type)) {
			mBufferes.insert(std::map<ObjectType, VertexObj>::value_type(type, obj));
		}
	}

	void GameObject::RemoveVertexObj(ObjectType type)
	{
		std::map<ObjectType, VertexObj>::iterator it =
			mBufferes.find(type);

		if (it != mBufferes.end()) {
			DelTextures(it->second.mTex);
			it->second.UnLoadDefVertex();
			mBufferes.erase(type);
		}
	}

	bool GameObject::IsVertexObjExist(ObjectType type)
	{
		std::map<ObjectType, VertexObj>::iterator it =
			mBufferes.find(type);

		return it != mBufferes.end();
	}

	void GameObject::RemoveAllVertexObj()
	{
		mBufferes.clear();
	}

	void GameObject::DestroySelf()
	{
		GameObject *obj = Game::RemoveObj(mTag.mCode);

		if (obj) {
			obj->Terminate();
			delete obj;
		}
	}
}
