#ifndef __ENEMY_CASTLEMORTAR_H__
#define __ENEMY_CASTLEMORTAR_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_CastleMortar : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation closed;
	Animation opening;
	Animation opening2;
	Animation stand;
	Animation stand2;
	Animation stand3;
	Path path;
public:
	Enemy_CastleMortar(int x, int y, int option);
	void Shoot();
	void Move();
	int reload[3];
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif