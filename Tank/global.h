#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <cstdint>

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

	// 对象类型, 对于 GameObject 定义
	typedef int ObjectType;

	extern const ObjectType MAP_TYPE;		// 地图
	extern const ObjectType TANK_TYPE;		// 坦克
	extern const ObjectType SHELL_TYPE;		// 炮弹
	extern const ObjectType TURRET_TYPE;	// 炮塔
	extern const ObjectType ANIM_TYPE;		// 帧动画

	// ---------------------------------------------------------------------------

	// 对象编号
	typedef int ObjectCode;

	// 对象标识
	class ObjectTag
	{
	public:
		ObjectTag() : mType(0), mCode(0) {}

		ObjectType mType;	// 对象标识
		ObjectCode mCode;	// 对象编码
	};

	ObjectTag AllocObjTag(ObjectType type);
}

#endif // __GLOBAL_H__
