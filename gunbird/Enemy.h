#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

#define BULLET_SPEED 4

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
	Animation* extra_animation = nullptr;
	Collider* collider = nullptr;


public:
	iPoint position;
	fPoint bullet_speed;
	int reload = 0;
	float angle;
	int pathoption = 0;
	float hp = 1.0f;
	int killscore = 0;
	int status = NORMAL;
	int death_type = DEFAULT_ENEMY;
	bool flying;
	bool drops_powerup = false;
	bool drops_bomb = false;
	bool drops_coin = false;
	int damaged_hp = 0;
	bool aditionalanimation = false;
	bool following = false;
	bool dead_anim = false;


public:
	Enemy(int x, int y, int option);
	virtual ~Enemy();

	const Collider* GetCollider() const;
	fPoint ShootCalculator(iPoint position, iPoint player);
	float AngleCalc(iPoint position, iPoint player);

	virtual void Move() {};
	virtual void Shoot() {};
	virtual void Draw(SDL_Texture* sprites, Enemy* enemy);
	virtual void Extra_animation() {};
	virtual void OnCollision(Collider* collider, Enemy* enemy);
	virtual void ToDie(Enemy* enemy, Collider* col);
};

#endif // __ENEMY_H__
