#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Balloon.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"

Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0, 0, 53, 53 });
	fly.PushBack({ 53, 0, 53, 53 });
	fly.PushBack({ 106, 0, 53 ,53 });
	fly.PushBack({ 159, 0, 53, 53 });
	fly.PushBack({ 212, 0, 53, 53 });
	fly.speed = 0.65f;

	animation = &fly;

	path.PushBack({ 0.0f, 0.75f }, 200);
	path.PushBack({ 0.0f,0.0f }, 300);
	path.PushBack({ 0.0f, 0.75f }, 300);

	collider = App->collision->AddCollider({ 0, 0, 42, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Balloon::Move()
{
	position = original_pos + path.GetCurrentPosition();
}

void Enemy_Balloon::Shoot()
{
	initcounter += 1;
	if (initcounter > 210 && initcounter < 500)
	{
		if (SDL_GetTicks() >= reload)
		{
			App->particles->AddParticle(App->particles->balloonshoot, position.x + 18, position.y + 53, COLLIDER_ENEMY_SHOT);
			reload = SDL_GetTicks() + 500;
		}
	}
}
