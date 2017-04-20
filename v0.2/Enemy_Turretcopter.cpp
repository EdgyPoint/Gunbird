#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Turretcopter.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_Turretcopter::Enemy_Turretcopter(int x, int y, int option) : Enemy(x, y, option)
{
	fly.PushBack({ 0, 58, 32, 35 });
	fly.PushBack({ 32, 58, 32, 35 });
	fly.PushBack({ 66, 58, 32 ,35 });
	fly.PushBack({ 0, 93, 32, 35 });
	fly.PushBack({ 32, 93, 32, 35 });
	fly.PushBack({ 66, 93, 32, 35 });
	fly.speed = 0.2f;

	animation = &fly;

	path.PushBack({-0.1f, -0.7f }, 100);
	path.PushBack({-0.1f, 0.7f }, 200);
	path.PushBack({-0.1f, 1.2f }, 200);

	collider = App->collision->AddCollider({ 0, 0, 32, 35 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	hp = 1.0f;
}

void Enemy_Turretcopter::Move()
{
	if (pathoption == 2)
	{
		if (going_right)
		{
			if (wave > 1000.0f)
				going_right = false;
			else
				wave += 0.01f;
		}
		else
		{
			if (wave < -1000.0f)
				going_right = true;
			else
				wave -= 0.01f;
		}

		position.x = original_x + (200.0f * sinf(wave));
		position.y += 2;
	}
	else
	{
		position = original_pos + path.GetCurrentPosition();
	}
}

/*void Enemy_Turretcopter::Shoot()
{
	distance.x = App->player->position.x - position.x;
	distance.y = App->player->position.y - position.y;

	aux_float = distance.y / App->particles->balloonshoot.speed.y;
	speeds.x = distance.x / aux_float;
	speeds.y = distance.y / aux_float;

	initcounter += 1;
	if (initcounter > 210 && initcounter < 500)
	{
		if (SDL_GetTicks() >= reload)
		{
			if (distance.y < 0)
			{
				speeds.y *= -1;
				speeds.x *= -1;
			}
			App->particles->AddParticle(App->particles->balloonshoot, position.x + 18, position.y + 53, COLLIDER_ENEMY_SHOT, speeds.x, speeds.y);
			reload = SDL_GetTicks() + 500;
		}
	}
}*/
