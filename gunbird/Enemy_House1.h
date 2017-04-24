#ifndef __ENEMY_HOUSE1_H__
#define __ENEMY_HOUSE1_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_House1 : public Enemy
{

private:
	iPoint original_pos;
	Animation fly, fly2, fly3;
	Animation flag, flag2, flag3;
	Path path;


public:
	Enemy_House1(int x, int y, int option);
	void Move();
	void Extra_animation();
};
#endif

