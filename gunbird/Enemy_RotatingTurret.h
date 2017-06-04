#ifndef __ENEMY_ROTATINGTURRET_H__
#define __ENEMY_ROTATINGTURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RotatingTurret : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation* aux;
	Animation aditional_animation;
	Animation normal_base_anim;
	Animation hit_base_anim;
	Animation damaged_base_anim;
	Animation down, down_hit, down_damaged;
	Animation downr1, downr1_hit, downr1_damaged;
	Animation downr2, downr2_hit, downr2_damaged;
	Animation downr3, downr3_hit, downr3_damaged;
	Animation downr4, downr4_hit, downr4_damaged;
	Animation downr5, downr5_hit, downr5_damaged;
	Animation downr6, downr6_hit, downr6_damaged;
	Animation downr7, downr7_hit, downr7_damaged;
	Animation right, right_hit, right_damaged;
	Animation rightu1, rightu1_hit, rightu1_damaged;
	Animation rightu2, rightu2_hit, rightu2_damaged;
	Animation rightu3, rightu3_hit, rightu3_damaged;
	Animation rightu4, rightu4_hit, rightu4_damaged;
	Animation rightu5, rightu5_hit, rightu5_damaged;
	Animation up, up_hit, up_damaged;
	Animation upl1, upl1_hit, upl1_damaged;
	Animation upl2, upl2_hit, upl2_damaged;
	Animation upl3, upl3_hit, upl3_damaged;
	Animation upl4, upl4_hit, upl4_damaged;
	Animation upl5, upl5_hit, upl5_damaged;
	Animation upl6, upl6_hit, upl6_damaged;
	Animation left, left_hit, left_damaged;
	Animation leftd1, leftd1_hit, leftd1_damaged;
	Animation leftd2, leftd2_hit, leftd2_damaged;
	Animation leftd3, leftd3_hit, leftd3_damaged;
	Animation leftd4, leftd4_hit, leftd4_damaged;
	Animation leftd5, leftd5_hit, leftd5_damaged;
	Animation leftd6, leftd6_hit, leftd6_damaged;
	Animation dead;
	Path path;

public:
	Enemy_RotatingTurret(int x, int y, int option);
	void Shoot();
	void Move();
	void Special_animation();
	int reload[3];
	int initcounter = 0;
	float aux_float;
	int counter = 0;
	int reloadd = 0;
	fPoint speeds;
};
#endif