#ifndef __ENEMY_GREENROBOT_H__
#define __ENEMY_GREENROBOT_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenRobot : public Enemy
{
private:
	enum Anim_Type
	{
		STAND,
		BACKWARD,
		FORWARD, 
		DEAD
	};

	Anim_Type anim_type = STAND;
	iPoint original_pos;
	fPoint distance;
	Animation dead;
	Animation stand, stand_hit, stand_damaged;
	Animation walk_backward, walk_backward_hit, walk_backward_damaged;
	Animation walk_forward, walk_forward_hit, walk_forward_damaged;
	Animation down, down_hit, down_damaged;
	Animation downr1, downr1_hit, downr1_damaged;
	Animation downr2, downr2_hit, downr2_damaged;
	Animation downr3, downr3_hit, downr3_damaged;
	Animation right, right_hit, right_damaged;
	Animation rightu1, rightu1_hit, rightu1_damaged;
	Animation rightu2, rightu2_hit, rightu2_damaged;
	Animation rightu3, rightu3_hit, rightu3_damaged;
	Animation up, up_hit, up_damaged;
	Animation upl1, upl1_hit, upl1_damaged;
	Animation upl2, upl2_hit, upl2_damaged;
	Animation upl3, upl3_hit, upl3_damaged;
	Animation left, left_hit, left_damaged;
	Animation leftd1, leftd1_hit, leftd1_damaged;
	Animation leftd2, leftd2_hit, leftd2_damaged;
	Animation leftd3, leftd3_hit, leftd3_damaged;

	Path path;
	int counter = 0;
public:
	Enemy_GreenRobot(int x, int y, int option);
	void Move();
	void Shoot();
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif