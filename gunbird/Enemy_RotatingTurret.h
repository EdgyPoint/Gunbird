#ifndef __ENEMY_ROTATINGTURRET_H__
#define __ENEMY_ROTATINGTURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RotatingTurret : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation normal_base_anim;
	Animation hit_base_anim;
	Animation damaged_base_anim;
	Animation down;
	Animation downr1;
	Animation downr2;
	Animation downr3;
	Animation downr4;
	Animation downr5;
	Animation downr6;
	Animation downr7;
	Animation right;
	Animation rightu1;
	Animation rightu2;
	Animation rightu3;
	Animation rightu4;
	Animation rightu5;
	Animation up;
	Animation upl1;
	Animation upl2;
	Animation upl3;
	Animation upl4;
	Animation upl5;
	Animation upl6;
	Animation left;
	Animation leftd1;
	Animation leftd2;
	Animation leftd3;
	Animation leftd4;
	Animation leftd5;
	Animation leftd6;
	Path path;
public:
	Enemy_RotatingTurret(int x, int y, int option);
	void Shoot();
	void Move();
	void Extra_animation();
	int reload[3];
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif