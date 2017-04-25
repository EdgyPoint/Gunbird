#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_Vase.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"




Enemy_Vase::Enemy_Vase(int x, int y, int option) : Enemy(x, y, option)
{
	//normal vase animation
	not_animation.PushBack({ 381, 3, 33, 49 });

	//animation when hit
	not_animation2.PushBack({ 418, 3, 33, 49 });

	//animation when damaged
	not_animation3.PushBack({ 381, 3, 33, 49 });
	not_animation3.PushBack({ 456, 3, 33, 49 });
	not_animation3.loop = true;
	not_animation3.speed = 0.2f;
	
	collider = App->collision->AddCollider({ 0, 0, 33, 49 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &not_animation;



	path.PushBack({ 0.0f, 0.55f }, 10000);
	original_pos.x = x;
	original_pos.y = y;

	hp = 12.0f;
	damaged_hp = 4.0f;
	death_type = SMALL_ENEMY;
	drops_coin = true;
	flying = false;
	killscore = 0;
}

void Enemy_Vase::Move()
{
	position = original_pos + path.GetCurrentPosition();
	if (status == NORMAL) { animation = &not_animation; }
	if (status == HIT) { animation = &not_animation2; }
	if (status == DAMAGED) { animation = &not_animation3; }
}

