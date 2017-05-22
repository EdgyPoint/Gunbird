#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_2CannonTurret.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_2CannonTurret::Enemy_2CannonTurret(int x, int y, int option) : Enemy(x, y, option)
{

	status = NORMAL;

	closed.PushBack({ 239, 429, 30, 42 });
	closed.loop = false;

	closed_hit.PushBack({ 239, 597, 30, 42 });
	closed.loop = false;

	closed_damaged.PushBack({ 239, 513, 30, 42 });
	closed.loop = false;

	attacking.PushBack({ 269, 429, 30, 42 });
	attacking.PushBack({ 299, 429, 30, 42 });
	attacking.PushBack({ 329, 429, 30, 42 });
	attacking.PushBack({ 359, 429, 30, 42 });
	attacking.PushBack({ 239, 471, 30, 42 });
	attacking.PushBack({ 269, 471, 30, 42 });
	attacking.PushBack({ 299, 471, 30, 42 });
	attacking.PushBack({ 329, 471, 30, 42 });
	attacking.PushBack({ 299, 471, 30, 42 });
	attacking.PushBack({ 269, 471, 30, 42 });
	attacking.PushBack({ 269, 471, 30, 42 });
	attacking.PushBack({ 299, 471, 30, 42 });
	attacking.PushBack({ 329, 471, 30, 42 });
	attacking.PushBack({ 299, 471, 30, 42 });
	attacking.PushBack({ 269, 471, 30, 42 });
	attacking.PushBack({ 269, 471, 30, 42 });
	attacking.PushBack({ 299, 471, 30, 42 });
	attacking.PushBack({ 329, 471, 30, 42 });
	attacking.PushBack({ 299, 471, 30, 42 });
	attacking.PushBack({ 269, 471, 30, 42 });
	attacking.PushBack({ 239, 471, 30, 42 });
	attacking.PushBack({ 359, 429, 30, 42 });
	attacking.PushBack({ 329, 429, 30, 42 });
	attacking.PushBack({ 299, 429, 30, 42 });
	attacking.PushBack({ 269, 429, 30, 42 });
	attacking.speed = 0.1f;

	attacking_hit.PushBack({ 269, 597, 30, 42 });
	attacking_hit.PushBack({ 299, 597, 30, 42 });
	attacking_hit.PushBack({ 329, 597, 30, 42 });
	attacking_hit.PushBack({ 359, 597, 30, 42 });
	attacking_hit.PushBack({ 239, 639, 30, 42 });
	attacking_hit.PushBack({ 269, 639, 30, 42 });
	attacking_hit.PushBack({ 299, 639, 30, 42 });
	attacking_hit.PushBack({ 329, 639, 30, 42 });
	attacking_hit.PushBack({ 299, 639, 30, 42 });
	attacking_hit.PushBack({ 269, 639, 30, 42 });
	attacking_hit.PushBack({ 269, 639, 30, 42 });
	attacking_hit.PushBack({ 299, 639, 30, 42 });
	attacking_hit.PushBack({ 329, 639, 30, 42 });
	attacking_hit.PushBack({ 299, 639, 30, 42 });
	attacking_hit.PushBack({ 269, 639, 30, 42 });
	attacking_hit.PushBack({ 269, 639, 30, 42 });
	attacking_hit.PushBack({ 299, 639, 30, 42 });
	attacking_hit.PushBack({ 329, 639, 30, 42 });
	attacking_hit.PushBack({ 299, 639, 30, 42 });
	attacking_hit.PushBack({ 269, 639, 30, 42 });
	attacking_hit.PushBack({ 239, 639, 30, 42 });
	attacking_hit.PushBack({ 359, 597, 30, 42 });
	attacking_hit.PushBack({ 329, 597, 30, 42 });
	attacking_hit.PushBack({ 299, 597, 30, 42 });
	attacking_hit.PushBack({ 269, 597, 30, 42 });
	attacking_hit.speed = 0.1f;

	attacking_damaged.PushBack({ 269, 513, 30, 42 });
	attacking_damaged.PushBack({ 299, 513, 30, 42 });
	attacking_damaged.PushBack({ 329, 513, 30, 42 });
	attacking_damaged.PushBack({ 359, 513, 30, 42 });
	attacking_damaged.PushBack({ 239, 555, 30, 42 });
	attacking_damaged.PushBack({ 269, 555, 30, 42 });
	attacking_damaged.PushBack({ 299, 555, 30, 42 });
	attacking_damaged.PushBack({ 329, 555, 30, 42 });
	attacking_damaged.PushBack({ 299, 555, 30, 42 });
	attacking_damaged.PushBack({ 269, 555, 30, 42 });
	attacking_damaged.PushBack({ 269, 555, 30, 42 });
	attacking_damaged.PushBack({ 299, 555, 30, 42 });
	attacking_damaged.PushBack({ 329, 555, 30, 42 });
	attacking_damaged.PushBack({ 299, 555, 30, 42 });
	attacking_damaged.PushBack({ 269, 555, 30, 42 });
	attacking_damaged.PushBack({ 269, 555, 30, 42 });
	attacking_damaged.PushBack({ 299, 555, 30, 42 });
	attacking_damaged.PushBack({ 329, 555, 30, 42 });
	attacking_damaged.PushBack({ 299, 555, 30, 42 });
	attacking_damaged.PushBack({ 269, 555, 30, 42 });
	attacking_damaged.PushBack({ 239, 555, 30, 42 });
	attacking_damaged.PushBack({ 359, 513, 30, 42 });
	attacking_damaged.PushBack({ 329, 513, 30, 42 });
	attacking_damaged.PushBack({ 299, 513, 30, 42 });
	attacking_damaged.PushBack({ 269, 513, 30, 42 });
	attacking_damaged.speed = 0.1f;

	animation = &attacking;

	collider = App->collision->AddCollider({ 0, 0, 30, 43 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.4f }, 10000);

	original_pos.x = x;
	original_pos.y = y;

	hp = 10.0f;
	damaged_hp = 7;
	death_type = SMALL_ENEMY;
	flying = false;
	killscore = 200;
}

void Enemy_2CannonTurret::Move()
{
	position = original_pos + path.GetCurrentPosition();

	/*if (status == NORMAL)
		aditional_animation = &closed;

	if (status == HIT)
		aditional_animation = &closed_hit;

	if (status == DAMAGED)
		aditional_animation = &closed_damaged;*/

	if (status == NORMAL)
		animation = &attacking;

	if (status == HIT)
		animation = &attacking_hit;

	if (status == DAMAGED)
	{
		if (counter == 0)
			animation = &attacking_damaged;
		else
			animation = &attacking;
		counter++;
		if (counter == 20)counter = 0;
	}
}

void Enemy_2CannonTurret::Shoot()
{

}
