#ifndef __GLOBAL_H__
#define __GLOBAL_H__

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

	// �����ʶ
	typedef int ObjectTag;

	// ������Ⱦ�����ʶ
	ObjectTag AllocMap();				// ��ͼ�Լ�����
	ObjectTag AllocPrimaryTag();		// ����
	ObjectTag AllocConsumable();		// ������Ʒ�����ڵ�
	ObjectTag AllocEnemy();				// ����
	ObjectTag AllocNpc();				// NPC
}

#endif // __GLOBAL_H__
