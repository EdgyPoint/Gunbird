#ifndef __ENEMY_TRAINTURRET_H__
#define __ENEMY_TRAINTURRET_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_TrainTurret : public Enemy
{

private:

	iPoint original_pos;
	Animation closed;
	Animation closed_hit;
	Animation closed_damaged;
	Path path;
	int counter = 0;
	int reloadd;

public:
	Enemy_TrainTurret(int x, int y, int option);
	void Move();
	void Shoot();
};
#endif

