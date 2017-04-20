#ifndef __ENEMY_HOUSE2_H__
#define __ENEMY_HOUSE2_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_House2 : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Animation flag;
	Path path;


public:
	Enemy_House2(int x, int y, int option);
	void Move();
	void Extra_animation();
};
#endif

