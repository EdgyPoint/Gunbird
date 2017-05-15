#ifndef __ENEMY_ROTATINGTURRET_H__
#define __ENEMY_ROTATINGTURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RotatingTurret : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation normal_anim;
	Animation hit_anim;
	Path path;
public:
	Enemy_RotatingTurret(int x, int y, int option);
	void Shoot();
	void Move();
	int reload[3];
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif