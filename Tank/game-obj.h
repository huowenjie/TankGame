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
	// ���㻺�����
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

	// ��Ϸ����
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
		// ���ö����ʶ
		void SetTag(const ObjectTag &tag);

		// ��ȡ�����ʶ
		ObjectTag GetTag() const;

		// ���ƶ���
		virtual void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// ���µ�ǰλ��
		virtual void Update(GAMEEVNET handle);

	public:
		// ��ʼ��
		virtual void LoadVertex(float *vertex, uint32_t num);
		virtual void Initialize();
		virtual void Terminate();

		// ��ȡ��ǰ��������
		Vector2D<float> GetPosition() const;

		// ��ȡ��Χ������
		const Vector4D<float> & GetAABB() const;

		// ��ȡ��Χ������
		const Vector3D<float> & GetBoundingSphere() const;

		// �����б����
		static void AddVertexObj(ObjectType type, const VertexObj &obj);
		static void RemoveVertexObj(ObjectType type);
		static bool IsVertexObjExist(ObjectType type);
		static void RemoveAllVertexObj();

	protected:

		// ��������
		void DestroySelf();

	protected:
		ObjectTag mTag;

		VertexObj mVertObj;		// �������

		glm::mat4 mModel;		// ģ�;���
		glm::mat4 mPrevModel;	// ��һ֡��������

		glm::mat4 mTranslate;	// ƽ�ƾ���
		glm::mat4 mRotate;		// ��ת����
		glm::mat4 mScale;		// ���ž���

		glm::mat4 mRun;			// �˶�����
		glm::mat4 mPrevRun;		// ��һ֡����������ײ��ԭ

		glm::vec4 mPosition;	// λ��
		glm::vec4 mPrevPos;		// ��һ֡λ�ã����ڵ�ͼ����
		glm::vec4 mStartPos;	// ��ʼλ��

		Vector4D<float> mAABB;	// ��Χ��
		Vector3D<float> mSphere;// ��Χ��
		Vector2D<float> mSize;	// ����ߴ�

		std::string mResPath;	// ��Դ·��

		// ���㻺����
		static std::map<ObjectType, VertexObj> mBufferes;
	};
}

#endif // __GAME_OBJ_H__
