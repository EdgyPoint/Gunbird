#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Redbomb.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"

Enemy_Redbomb :: Enemy_Redbomb(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 100, 58, 28, 32 });
	fly.PushBack({ 128, 58, 28, 32 });
	fly.PushBack({ 156, 58, 28, 32 });
	fly.PushBack({ 184, 58, 28, 32 });
	fly.PushBack({ 100, 90, 28, 32 });
	fly.PushBack({ 128, 90, 28, 32 });
	fly.PushBack({ 156, 90, 28, 32 });
	fly.PushBack({ 184, 90, 28, 32 });

	fly.speed = 0.3f;

	animation = &fly;

	path.PushBack({ 0.0f, 0.55f }, 600);
	path.PushBack({ 1.75f, 1.75f }, 2000);


	

	collider = App->collision->AddCollider({ 0, 0,  28, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Redbomb::Move()
{
	position = original_pos + path.GetCurrentPosition();
}

void Enemy_Redbomb::Shoot()
{
	
}
