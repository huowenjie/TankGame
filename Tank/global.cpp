#include "global.h"

namespace hwj
{
	// ½ÇÉ«ÀàĞÍ
	const RoleType PRIMARY_ROLE = 1;
	const RoleType ENEMY_ROLE = 2;
	const RoleType NPC_ROLE = 3;

	const ObjectType TANK_TYPE = 1;
	const ObjectType SHELL_TYPE = 2;
	const ObjectType TURRET_TYPE = 3;
	const ObjectType ANIM_TYPE = 4;

	static int gCurMapTag = 0;
	static int gCurPriTag = 100;
	static int gCurCosTag = 300;
	static int gCurNpcTag = 400;
	static int gCurAnmTag = 500;

	ObjectTag AllocObjTag(ObjectType type) 
	{
		ObjectTag tag;

		tag.mType = type;

		switch (type) {
		case TANK_TYPE:
			tag.mCode = (gCurPriTag >= 299) ? 100 : gCurPriTag++;
			break;

		case SHELL_TYPE:
			tag.mCode = (gCurCosTag >= 399) ? 300 : gCurCosTag++;
			break;

		case TURRET_TYPE:
			tag.mCode = (gCurPriTag >= 299) ? 100 : gCurPriTag++;
			break;

		case ANIM_TYPE:
			tag.mCode = (gCurAnmTag >= 599) ? 500 : gCurAnmTag++;
			break;

		default:
			break;
		}

		return tag;
	}
}
