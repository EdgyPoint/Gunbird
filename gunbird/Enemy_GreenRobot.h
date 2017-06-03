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
	Path path;
	int counter = 0;
public:
	Enemy_GreenRobot(int x, int y, int option);
	void Move();
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif