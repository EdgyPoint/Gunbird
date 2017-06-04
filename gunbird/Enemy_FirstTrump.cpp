#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_FirstTrump.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_FirstTrump::Enemy_FirstTrump(int x, int y, int option) : Enemy(x, y, option)
{
	stand.PushBack({ 1392, 0, 60, 60 });

	stand_hit.PushBack({ 1572, 0, 60, 60 });

	stand_damaged.PushBack({ 1752, 0, 60, 60 });


	attacking.PushBack({ 1392, 0, 60, 60 });
	attacking.PushBack({ 1452, 0, 60, 60 });
	attacking.PushBack({ 1512, 0, 60, 60 });

	attacking_hit.PushBack({ 1572, 0, 60, 60 });
	attacking_hit.PushBack({ 1632, 0, 60, 60 });
	attacking_hit.PushBack({ 1692, 0, 60, 60 });

	attacking_damaged.PushBack({ 1752, 0, 60, 60 });
	attacking_damaged.PushBack({ 1812, 0, 60, 60 });
	attacking_damaged.PushBack({ 1872, 0, 60, 60 });


	animation = &stand;

	collider = App->collision->AddCollider({ 0, 0, 60, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.4f }, 10000);




	original_pos.x = x;
	original_pos.y = y;

	hp = 10.0f;
	damaged_hp = 7;
	death_type = SMALL_ENEMY;
	anim_type = STAND;
	flying = false;
	killscore = 200;
}

void Enemy_FirstTrump::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (position.y > 0 && position.y < 100) anim_type = ATTACKING;
	else anim_type = STAND;


	if (anim_type == STAND)
	{
		if (status == NORMAL)
			animation = &stand;

		if (status == HIT)
			animation = &stand_hit;

		if (status == DAMAGED)
		{
			if (counter == 0)
				animation = &stand_damaged;
			else
				animation = &stand;
		}
	}
	if (anim_type == ATTACKING)
	{
		if (status == NORMAL)
			animation = &attacking;

		if (status == HIT)
			animation = &attacking_hit;

		if (status == DAMAGED)
		{
			if (counter == 0)
				animation = &attacking_damaged;
			else
				animation = &attacking;
		}
	}
	counter++;
	if (counter == 20)counter = 0;
}

void Enemy_FirstTrump::Shoot()
{
	if (anim_type == ATTACKING)
	{
		reload++;
		if (reload == 5)
		{
			bullet_speed = ShootCalculator({ position.x + 12, position.y + 10 }, { App->player->position.x + 41, App->player->position.y + 11 });
			App->particles->AddParticle(App->particles->smallshot, position.x + 12, position.y + 3, COLLIDER_ENEMY_SHOT, bullet_speed.x, bullet_speed.y);
			bullet_speed = ShootCalculator({ position.x + 12, position.y + 3 }, { App->player->position.x - 41, App->player->position.y + 11 });
			App->particles->AddParticle(App->particles->smallshot, position.x + 12, position.y + 3, COLLIDER_ENEMY_SHOT, bullet_speed.x, bullet_speed.y);
		}
	}
}
