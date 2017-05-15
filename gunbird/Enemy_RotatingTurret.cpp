#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_RotatingTurret.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_RotatingTurret::Enemy_RotatingTurret(int x, int y, int option) : Enemy(x, y, option)
{

	//normal animation
	normal_anim.PushBack({ 594, 397, 28, 41 });

	//hit animation
	hit_anim.PushBack({ 631, 397, 28, 41 });

	
	collider = App->collision->AddCollider({ 0, 0, 28, 41 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &normal_anim;


	path.PushBack({ 0.0f, 0.4f }, 1000);

	original_pos.x = x;
	original_pos.y = y;

	hp = 2.0f;

	death_type = SMALL_ENEMY;
	flying = false;
	killscore = 500;
}

void Enemy_RotatingTurret::Move()
{
	position = original_pos + path.GetCurrentPosition();
	
	if (status == NORMAL) { animation = &normal_anim; }
	if (status == HIT) { animation = &hit_anim; }
	
}

void Enemy_RotatingTurret::Shoot()
{}