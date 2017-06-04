#ifndef __ENEMY_TURRETCOPTER_H__
#define __ENEMY_TURRETCOPTER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Turretcopter : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation fly;
	Path path;
	float wave = -1.0f;
	bool going_right = true;
	int original_x = 0;

public:
	Enemy_Turretcopter(int x, int y, int option);
	void Move();
	int killscore = 200;
	int reload = 0;
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif

