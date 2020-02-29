#ifndef __GLOBAL_H__
#define __GLOBAL_H__

namespace hwj 
{
	// ---------------------------------------------------------------------------
	
	// 窗口句柄
	typedef void * WINDOWHANDLE;

	// Opengl 上下文
	typedef void * OPENGLCONTEXT;

	// 事件句柄
	typedef void * GAMEEVNET;

	// ---------------------------------------------------------------------------
	
	// 角色类型
	typedef int RoleType;

	// 具体角色
	extern const RoleType PRIMARY_ROLE;
	extern const RoleType ENEMY_ROLE;
	extern const RoleType NPC_ROLE;

	// ---------------------------------------------------------------------------

	// 对象标识
	typedef int ObjectTag;

	// 分配渲染对象标识
	ObjectTag AllocMap();				// 地图以及场景
	ObjectTag AllocPrimaryTag();		// 主角
	ObjectTag AllocConsumable();		// 消耗物品，如炮弹
	ObjectTag AllocEnemy();				// 敌人
	ObjectTag AllocNpc();				// NPC
}

#endif // __GLOBAL_H__
