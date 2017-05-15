#ifndef __ENEMY_WINDOWGUN_H__
#define __ENEMY_WINDOWGUN_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_WindowGun : public Enemy
{

private:
	iPoint original_pos;
	Animation closed;
	Animation opening;
	Animation opening2;
	Animation stand1;
	Animation stand2;
	Animation stand3;
	Animation shooting;
	Path path;


public:
	Enemy_WindowGun(int x, int y, int option);
	void Move();
};
#endif

