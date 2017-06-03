#ifndef __ENEMY_FLYINGGUNNER_H__
#define __ENEMY_FLYINGGUNNER_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_FlyingGunner : public Enemy
{

private:
	iPoint original_pos;
	Animation arriving_left1;
	Animation arriving_left2;
	Path path;
	int original_x = 0;


public:
	Enemy_FlyingGunner(int x, int y, int option);
	void Move();
};
#endif
