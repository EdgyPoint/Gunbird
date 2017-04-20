#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

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
	bool aditionalanimation = false;
	


public:
	Enemy(int x, int y, int option);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	const int GetOption();

	virtual void Move() {};
	virtual void Shoot() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void Extra_animation() {};
	virtual void OnCollision(Collider* collider, Enemy* enemy);
};

#endif // __ENEMY_H__
