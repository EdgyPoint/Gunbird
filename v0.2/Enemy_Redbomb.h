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
public:
	Enemy_Redbomb(int x, int y);
	void Move();
	void Shoot();
};
#endif
