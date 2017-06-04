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

	if (option == 0)
	{
		path.PushBack({ 0.0f, 0.4f }, 4000);
		path.PushBack({ 0.0f, 10.0f }, 200);
		path.PushBack({ 0.0f, -5.0f }, 350);
		path.PushBack({ -3.0f, -5.0f }, 2);
		path.PushBack({ -3.2f, -5.0f }, 2);
		path.PushBack({ -3.4f, -5.0f }, 2);
		path.PushBack({ -3.6f, -5.0f }, 2);
		path.PushBack({ -3.8f, -5.0f }, 2);
		path.PushBack({ -4.0f, -5.0f }, 20000);
	}
	
	collider = App->collision->AddCollider({ 0, 0, 32, 35 }, COLLIDER_TYPE::COLLIDER_ENEMY_F, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	hp = 1.0f;

	death_type = SMALL_ENEMY;
	flying = true;
	killscore = 200;
}

void Enemy_Turretcopter::Move()
{
	
	position = original_pos + path.GetCurrentPosition();
	/*if (pathoption == 2)
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
	}*/
}


