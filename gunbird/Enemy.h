#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

#define BULLET_SPEED 4

struct SDL_Texture;
struct Collider;

enum Anim_Type
{
	STAND,
	BACKWARD,
	FORWARD,
	ATTACKING,
	CLOSED,
	OPENIN,
	SHOOTING,
	CLOSING,
	DEAD,
};

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
	Animation* extra_animation2 = nullptr;
	Collider* collider = nullptr;


public:
	iPoint position;
	fPoint bullet_speed;
	fPoint bullet_speed2;
	fPoint bullet_speed3;
	fPoint bullet_speed4;
	fPoint bullet_speed5;
	fPoint bullet_speed6;
	int hitCD = 0;
	bool already_hit = false;
	int reload = 0;
	float angle, angle2;
	int pathoption = 0;
	float hp = 1.0f;
	int killscore = 0;
	int status = NORMAL;
	int death_type = DEFAULT_ENEMY;
	bool flying;
	bool firstdead = false;
	bool secondead = false;
	bool drops_powerup = false;
	bool drops_bomb = false;
	bool drops_coin = false;
	int damaged_hp = 0;
	bool aditionalanimation = false;
	bool specialanimation = false;
	bool following = false;
	bool dead_anim = false;
	bool to_draw = true;
	Anim_Type anim_type = STAND;


public:
	Enemy(int x, int y, int option);
	virtual ~Enemy();

	const Collider* GetCollider() const;
	fPoint ShootCalculator(iPoint position, iPoint player);
	float AngleCalc(iPoint position, iPoint player);

	virtual void Move() {};
	virtual void Shoot() {};
	virtual void Draw(SDL_Texture* sprites, Enemy* enemy);
	virtual void Special_animation() {};
	virtual void Extra_animation() {};
	virtual void OnCollision(Collider* collider, Enemy* enemy);
	virtual void ToDie(Enemy* enemy, Collider* col);
};

#endif // __ENEMY_H__
