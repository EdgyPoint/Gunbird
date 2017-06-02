#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_WindowGun.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"




Enemy_WindowGun::Enemy_WindowGun(int x, int y, int option) : Enemy(x, y, option)
{
	//closed animation
	closed.PushBack({0, 291, 22, 23});

	closed_hit.PushBack({ 0, 314, 22, 23 });

	closed_damaged.PushBack({ 0, 337, 22, 23 });

	//opening and closing animations
	opening.PushBack({22, 291, 22, 23});
	opening.PushBack({44, 291, 22, 23});
	opening.PushBack({66, 291, 22, 23});
	opening.loop = false;
	opening.speed = 2.0f;

	opening_hit.PushBack({ 22, 314, 22, 23 });
	opening_hit.PushBack({ 44, 314, 22, 23 });
	opening_hit.PushBack({ 66, 314, 22, 23 });
	opening_hit.loop = false;
	opening_hit.speed = 2.0f;

	opening_damaged.PushBack({ 22, 337, 22, 23 });
	opening_damaged.PushBack({ 44, 337, 22, 23 });
	opening_damaged.PushBack({ 66, 337, 22, 23 });
	opening_damaged.loop = false;
	opening_damaged.speed = 2.0f;


	closing.PushBack({ 66, 291, 22, 23 });
	closing.PushBack({ 44, 291, 22, 23 });
	closing.PushBack({ 22, 291, 22, 23 });
	closing.loop = false;
	closing.speed = 2.0f;

	closing_hit.PushBack({ 66, 314, 22, 23 });
	closing_hit.PushBack({ 44, 314, 22, 23 });
	closing_hit.PushBack({ 22, 314, 22, 23 });
	closing_hit.loop = false;
	closing_hit.speed = 2.0f;

	closing_damaged.PushBack({ 66, 337, 22, 23 });
	closing_damaged.PushBack({ 44, 337, 22, 23 });
	closing_damaged.PushBack({ 22, 337, 22, 23 });
	closing_damaged.loop = false;
	closing_hit.speed = 2.0f;


	//shooting animation
	shooting.PushBack({88, 291, 22, 23});
	shooting.PushBack({110, 291, 22, 23});
	shooting.PushBack({132, 291, 22, 23});
	shooting.loop = true;
	shooting.speed = 0.1f;

	shooting_hit.PushBack({ 88, 314, 22, 23 });
	shooting_hit.PushBack({ 110, 314, 22, 23 });
	shooting_hit.PushBack({ 132, 314, 22, 23 });
	shooting_hit.loop = true;
	shooting_hit.speed = 0.1f;

	shooting_damaged.PushBack({ 88, 337, 22, 23 });
	shooting_damaged.PushBack({ 110, 337, 22, 23 });
	shooting_damaged.PushBack({ 132, 337, 22, 23 });
	shooting_damaged.loop = true;
	shooting_damaged.speed = 0.1f;

	left_dead.PushBack({ 0, 370, 51, 66 });

	right_dead.PushBack({ 55, 370, 43, 61 });

	collider = App->collision->AddCollider({0, 0, 22, 23}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &closed;

	
	path.PushBack({ 0.0f, 0.4f }, 10000);
	original_pos.x = x;
	original_pos.y = y;

	hp = 7.0f;
	damaged_hp = 4.0f;
	death_type = SMALL_ENEMY;
	anim_type = CLOSED;
	drops_coin = false;
	flying = false;
	dead_anim = true;
	killscore = 200;
}

void Enemy_WindowGun::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (hp > 0)
	{
		if (counter < 370 || counter >= 560)anim_type = CLOSED;
		if (counter >= 370 && counter < 380)anim_type = OPENING;
		if (counter >= 380 && counter < 550)anim_type = SHOOTING;
		if (counter >= 550 && counter < 560)anim_type = CLOSING;
		counter++;
	}
	else
		anim_type = DEAD;

	if (anim_type == DEAD && position.x < 100)
	{
		animation = &left_dead;
		position.x -= 25;
		position.y -= 6;
		collider->rect.h = 0;
		collider->rect.w = 0;
	}
	if (anim_type == DEAD && position.x > 100)
	{
		animation = &right_dead;
		position.x -= 17;
		position.y -= 3;
		collider->rect.h = 0;
		collider->rect.w = 0;
	}

	if (anim_type == CLOSED)
	{
		if (status == NORMAL)
			animation = &closed;

		if (status == HIT)
			animation = &closed_hit;
		if (status == DAMAGED)
		{
			if (counter2 == 0)
				animation = &closed_damaged;
			else
				animation = &closed;
		}
	}
	if (anim_type == OPENING)
	{
		if (status == NORMAL)
			animation = &opening;

		if (status == HIT)
			animation = &opening_hit;
		if (status == DAMAGED)
		{
			if (counter2 == 0)
				animation = &opening_damaged;
			else
				animation = &opening;
		}
	}
	if (anim_type == SHOOTING)
	{
		if (status == NORMAL)
			animation = &shooting;

		if (status == HIT)
			animation = &shooting_hit;
		if (status == DAMAGED)
		{
			if (counter2 == 0)
				animation = &shooting_damaged;
			else
				animation = &shooting;
		}
	}
	if (anim_type == CLOSING)
	{
		if (status == NORMAL)
			animation = &closing;

		if (status == HIT)
			animation = &closing_hit;
		if (status == DAMAGED)
		{
			if (counter2 == 0)
				animation = &closing_damaged;
			else
				animation = &closing;
		}
	}
	counter2++;
	if (counter2 == 20)counter2 = 0;
}

void Enemy_WindowGun::Shoot()
{
	if (anim_type == SHOOTING)
	{
		if (SDL_GetTicks() >= reload[0])//first wave
		{
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 1.5f, 2);

			reload[0] = SDL_GetTicks() + 1000;
			reload[1] = SDL_GetTicks() + 500;
		}

		if (SDL_GetTicks() >= reload[1])
		{
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -1.5f, 2);
			
			reload[1] = SDL_GetTicks() + 500;
		}
	}
}

