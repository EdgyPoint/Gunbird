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
	fly.PushBack({ 106, 0, 53, 53 });
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

	path.PushBack({ 0.0f, 0.55f }, 220);
	path.PushBack({ 0.0f, 2.0f }, 55);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, 2.0f }, 55);
	path.PushBack({ 0.0f, 0.0f }, 1000);


	collider = App->collision->AddCollider({ 0, 0, 42, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY_F, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	killscore = 500;
	hp = 19.0f;
	damaged_hp = 7;
	death_type = MEDIUM_ENEMY;
	enemy_drops = true;
	flying = true;
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
	if (path.steps[2].active == true || path.steps[4].active == true)
	{
		if (reload == 0 || reload == 40)
		{

			App->particles->AddParticle(App->particles->smallshot, position.x + 25, position.y + 44, COLLIDER_ENEMY_SHOT, 2, 1, false);
			App->particles->AddParticle(App->particles->smallshot, position.x + 9, position.y + 44, COLLIDER_ENEMY_SHOT, -2, 1, false);
			App->particles->AddParticle(App->particles->presmallshot, position.x + 24, position.y + 43, COLLIDER_ENEMY_SHOT, 2, 1, false);
			App->particles->AddParticle(App->particles->presmallshot, position.x + 8, position.y + 43, COLLIDER_ENEMY_SHOT, -2, 1, false);
		}
		reload++;
}
	
	else if( reload != 0)
	{
		reload = 0;
	}
	
}
