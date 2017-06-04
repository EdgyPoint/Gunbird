#ifndef __ENEMY_TRUMPFIRST__
#define __ENEMY_TRUMPFIRST__

#include "Enemy.h"
#include "Path.h"

class Enemy_TrumpFirst : public Enemy
{
private:
	enum Anim_Type
	{
		STAND,
		ATTACKING,
	};

	Anim_Type anim_type = STAND;
	iPoint original_pos;
	fPoint distance;
	Animation stand, stand_hit, stand_damaged;
	Animation attacking, attacking_hit, attacking_damaged;


	Path path;
	int counter = 0;
public:
	Enemy_TrumpFirst(int x, int y, int option);
	void Move();
	void Shoot();
	int straight_shot[3];
	float aux_float;
	fPoint speed;
};
#endif