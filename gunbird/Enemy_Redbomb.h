#ifndef __ENEMY_REDBOMB_H__
#define __ENEMY_REDBOMB_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_Redbomb : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;
	int original_x = 0;

	
public:
	Enemy_Redbomb(int x, int y, int option);
	void Move();
	void Extra_animation();
};
#endif
