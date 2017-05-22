#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_WindowGun.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"




Enemy_WindowGun::Enemy_WindowGun(int x, int y, int option) : Enemy(x, y, option)
{
	//closed animation
	closed.PushBack({ 0, 291, 22, 23 });

	//opening animation
	opening.PushBack({26, 291, 22, 23});
	opening.PushBack({54, 291, 22, 23});
	shooting.loop = false;

	//opening hit animation

	//normal opened animation
	stand1.PushBack({82, 291, 22, 23});

	//shooting animation
	shooting.PushBack({108, 291, 22, 23});
	shooting.PushBack({136, 291, 22, 23});
	shooting.PushBack({164, 291, 22, 23});
	shooting.loop = true;
	shooting.speed = 1.0f;

	//hit opened animation

	//damaged opened animation

	collider = App->collision->AddCollider({ 0, 0, 33, 49 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &closed;

	
	path.PushBack({ 0.0f, 0.4f }, 10000);
	original_pos.x = x;
	original_pos.y = y;

	hp = 5.0f;
	damaged_hp = 4.0f;
	death_type = SMALL_ENEMY;
	drops_coin = false;
	flying = false;
	killscore = 200;
}

void Enemy_WindowGun::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (status == OPENING || status == NONE)
		collider->type = COLLIDER_NONE;
	if (status == NORMAL)
		collider->type = COLLIDER_ENEMY;

	/*if (status == OPENING && animation->Finished() == true) { status = NORMAL; }
	if (status == NORMAL) { animation = &stand1; }
	if (status == HIT && animation == &opening) { animation = &opening2; }
	if (status == HIT) { animation = &stand2; }
	if (status == DAMAGED) { animation = &stand3; }*/
}

