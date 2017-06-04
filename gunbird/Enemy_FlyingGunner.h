#ifndef __ENEMY_FLYINGGUNNER_H__
#define __ENEMY_FLYINGGUNNER_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_FlyingGunner : public Enemy
{

private:
	iPoint original_pos;
	Animation nothing;
	Animation arriving_left1;
	Animation arriving_left2;
	Animation arriving_left3;
	Animation arriving_right1;
	Animation arriving_right2;
	Animation arriving_right3;
	Animation staying;
	Path path;
	int original_x = 0;
	bool hasfinishedleft = false;
	bool hasfinishedright = false;

public:
	Enemy_FlyingGunner(int x, int y, int option);
	void Move();
};
#endif
