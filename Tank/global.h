#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <cstdint>

namespace hwj 
{
	// ---------------------------------------------------------------------------
	
	// ���ھ��
	typedef void * WINDOWHANDLE;

	// Opengl ������
	typedef void * OPENGLCONTEXT;

	// �¼����
	typedef void * GAMEEVNET;

	// ---------------------------------------------------------------------------

	// ��ɫ����
	typedef int RoleType;

	// �����ɫ
	extern const RoleType PRIMARY_ROLE;
	extern const RoleType ENEMY_ROLE;
	extern const RoleType NPC_ROLE;

	// ---------------------------------------------------------------------------

	// ��������, ���� GameObject ����
	typedef int ObjectType;

	extern const ObjectType MAP_TYPE;		// ��ͼ
	extern const ObjectType TANK_TYPE;		// ̹��
	extern const ObjectType SHELL_TYPE;		// �ڵ�
	extern const ObjectType TURRET_TYPE;	// ����
	extern const ObjectType ANIM_TYPE;		// ֡����

	// ---------------------------------------------------------------------------

	// ������
	typedef int ObjectCode;

	// �����ʶ
	class ObjectTag
	{
	public:
		ObjectTag() : mType(0), mCode(0) {}

		ObjectType mType;	// �����ʶ
		ObjectCode mCode;	// �������
	};

	ObjectTag AllocObjTag(ObjectType type);
}

#endif // __GLOBAL_H__
