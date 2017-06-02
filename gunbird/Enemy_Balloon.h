#ifndef __ENEMY_BALLOON_H__
#define __ENEMY_BALLOON_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Balloon : public Enemy
{

private:
	iPoint original_pos;
	Animation fly, fly2, fly3;
	Path path;

public:
	Enemy_Balloon(int x, int y, int option);
	void Move();
	void Shoot();
	int initcounter = 0;
	float aux_float;
	int counter = 0;
};
#endif

