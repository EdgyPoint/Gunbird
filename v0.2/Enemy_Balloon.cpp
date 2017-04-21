#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Balloon.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_Balloon::Enemy_Balloon(int x, int y, int option) : Enemy(x, y, option)
{
	fly.PushBack({ 0, 0, 53, 53 });
	fly.PushBack({ 53, 0, 53, 53 });
	fly.PushBack({ 106, 0, 53 ,53 });
	fly.PushBack({ 159, 0, 53, 53 });
	fly.PushBack({ 212, 0, 53, 53 });
	fly.speed = 0.65f;

	fly2.PushBack({ 265, 0, 53, 53 });
	fly2.speed = 0.65f;

	fly3.PushBack({ 0, 0, 53, 53 });
	fly3.PushBack({ 53, 0, 53, 53 });
	fly3.PushBack({ 106, 0, 53, 53 });
	fly3.PushBack({ 159, 0, 53, 53 });
	fly3.PushBack({ 212, 0, 53, 53 });
	fly3.PushBack({ 318, 0, 53, 53 });
	fly3.speed = 0.65f;

	animation = &fly;

	path.PushBack({ 0.0f, 0.75f }, 200);
	path.PushBack({ 0.0f,0.0f }, 50);
	path.PushBack({ 0.0f, 0.75f }, 200);
	path.PushBack({ 0.0f, 0.0f }, 50); 
	path.PushBack({ 0.0f, 0.75f }, 200);
	path.PushBack({ 0.0f, 0.0f }, 50);

	collider = App->collision->AddCollider({ 0, 0, 42, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	hp = 19.0f;
	damaged_hp = 7;
	death_type = MEDIUM_ENEMY;
}

void Enemy_Balloon::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (status == NORMAL)
		animation = &fly;

	if (status == HIT)
		animation = &fly2;

	if (status == DAMAGED)
		animation = &fly3;
}

void Enemy_Balloon::Shoot()
{
	distance.x = (App->player->position.x) - (position.x + 18);
	distance.y = App->player->position.y - (position.y + 53);

	speeds.x = distance.x / 30;
	speeds.y = distance.y / 30;

	initcounter += 1;
	if (initcounter > 210 && initcounter < 500)
	{
		if (SDL_GetTicks() >= reload)
		{
			if (distance.y < 0)
			{
				speeds.y *= -1;
				speeds.x *= 1;
			}
			App->particles->AddParticle(App->particles->balloonshoot, position.x + 18, position.y + 53, COLLIDER_ENEMY_SHOT, speeds.x, speeds.y);
			reload = SDL_GetTicks() + 1000;
		}
	}
}
