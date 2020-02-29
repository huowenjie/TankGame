#include "global.h"

namespace hwj
{
	// ½ÇÉ«ÀàÐÍ
	const RoleType PRIMARY_ROLE = 1;
	const RoleType ENEMY_ROLE = 2;
	const RoleType NPC_ROLE = 3;

	static int gCurMapTag = 0;
	static int gCurPriTag = 100;
	static int gCurCosTag = 200;
	static int gCurEnmTag = 300;
	static int gCurNpcTag = 400;

	ObjectTag AllocMap() 
	{
		return (gCurMapTag >= 99) ? -1 : gCurMapTag++;
	}

	ObjectTag AllocPrimaryTag() 
	{
		return (gCurPriTag >= 199) ? -1 : gCurPriTag++;
	}

	ObjectTag AllocConsumable()
	{
		if (gCurCosTag >= 299) {
			gCurCosTag = 0;
			return gCurCosTag;
		}

		return gCurCosTag++;
	}

	ObjectTag AllocEnemy()
	{
		return (gCurEnmTag >= 399) ? -1 : gCurEnmTag++;
	}

	ObjectTag AllocNpc()
	{
		return (gCurNpcTag >= 499) ? -1 : gCurNpcTag++;
	}
}
