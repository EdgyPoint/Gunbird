#ifndef __ENEMY_VASE_H__
#define __ENEMY_VASE_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_Vase : public Enemy
{

private:
	iPoint original_pos;
	Animation not_animation;
	Animation not_animation2;
	Animation not_animation3;
	Path path;


public:
	Enemy_Vase(int x, int y, int option);
	void Move();
	};
#endif

