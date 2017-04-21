#ifndef __ENEMY_CASTLEMORTAR_H__
#define __ENEMY_CASTLEMORTAR_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_CastleMortar : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation stand;
	Path path;
public:
	Enemy_CastleMortar(int x, int y, int option);
	void Shoot();
	void Move();
	int reload = 0;
	int initcounter = 0;
	float aux_float;
	fPoint speeds;
};
#endif