#ifndef __ENEMY_TRUMPSECOND__
#define __ENEMY_TRUMPSECOND__

#include "Enemy.h"
#include "Path.h"

class Enemy_TrumpSecond : public Enemy
{
private:

	Anim_Type anim_type = STAND;
	iPoint original_pos;
	fPoint distance;
	Animation stand, stand_hit, stand_damaged;
	Animation attacking, attacking_hit, attacking_damaged;


	Path path;
	int counter = 0;
public:
	Enemy_TrumpSecond(int x, int y, int option);
	void Move();
	void Shoot();
	int straight_shot[3];
	float aux_float;
	bool discount;
	fPoint speed;
};
#endif