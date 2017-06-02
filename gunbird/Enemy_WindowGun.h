#ifndef __ENEMY_WINDOWGUN_H__
#define __ENEMY_WINDOWGUN_H__

#include "Enemy.h"
#include "Path.h"


class Enemy_WindowGun : public Enemy
{
	enum anim_type
	{
		CLOSED,
		OPENING,
		SHOOTING,
		CLOSING,
		DEAD
	};
private:
	iPoint original_pos;
	Animation closed, opening, shooting, closing;
	Animation closed_hit, opening_hit, shooting_hit, closing_hit;
	Animation closed_damaged, opening_damaged, shooting_damaged, closing_damaged;
	Animation left_dead, right_dead;
	Path path;
	int counter = 0;
	int counter2 = 0;
	int reload[2];
	anim_type anim_type;

public:
	Enemy_WindowGun(int x, int y, int option);
	void Move();
	void Shoot();
};
#endif

