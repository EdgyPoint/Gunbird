#ifndef __ENEMY_BALLOON_H__
#define __ENEMY_BALLOON_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Balloon : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;
public:
	Enemy_Balloon(int x, int y);
	void Move();
	void Shoot();
};
#endif

