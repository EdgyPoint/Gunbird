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
		path.PushBack({ -0.8f, 0.4f }, 4000);
	}

	if (option == 1)
	{
		path.PushBack({ 0.0f, 0.4f }, 4000);
		path.PushBack({ 0.8f, 0.4f }, 4000);
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
	
}


