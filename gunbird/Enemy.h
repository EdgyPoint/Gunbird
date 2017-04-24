#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum ENEMY_STATUS
{
	NORMAL,
	HIT,
	DAMAGED,
	OPENING,
	NONE,
};

enum DEATH_TYPE
{
	MEDIUM_ENEMY,
	SMALL_ENEMY,
	DEFAULT_ENEMY
};

class Enemy
{
protected:
	Animation* animation = nullptr;
	Animation* aditional_animation = nullptr;
	Collider* collider = nullptr;


public:
	iPoint position;
	int pathoption = 0;
	float hp = 1.0f;
	int killscore = 0;
	int status = NORMAL;
	int death_type = DEFAULT_ENEMY;
	bool flying;
	bool enemy_drops = false;
	int damaged_hp = 0;
	bool aditionalanimation = false;
	bool following = false;


public:
	Enemy(int x, int y, int option);
	virtual ~Enemy();

	const Collider* GetCollider() const;


	virtual void Move() {};
	virtual void Shoot() {};
	virtual void Draw(SDL_Texture* sprites, Enemy* enemy);
	virtual void Extra_animation() {};
	virtual void OnCollision(Collider* collider, Enemy* enemy);
	virtual void ToDie(Enemy* enemy, Collider* col);
};

#endif // __ENEMY_H__
