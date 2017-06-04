#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_TrumpThird.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleVillageScene.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_TrumpThird::Enemy_TrumpThird(int x, int y, int option) : Enemy(x, y, option)
{
	stand.PushBack({ 1392, 240, 60, 60 });

	stand_hit.PushBack({ 1572, 240, 60, 60 });

	stand_damaged.PushBack({ 1752, 240, 60, 60 });


	attacking.PushBack({ 1392, 240, 60, 60 });
	attacking.PushBack({ 1452, 240, 60, 60 });
	attacking.PushBack({ 1512, 240, 60, 60 });
	attacking.speed = 0.1f;

	attacking_hit.PushBack({ 1572, 240, 60, 60 });
	attacking_hit.PushBack({ 1632, 240, 60, 60 });
	attacking_hit.PushBack({ 1692, 240, 60, 60 });
	attacking_hit.speed = 0.1f;

	attacking_damaged.PushBack({ 1752, 240, 60, 60 });
	attacking_damaged.PushBack({ 1812, 240, 60, 60 });
	attacking_damaged.PushBack({ 1872, 240, 60, 60 });
	attacking_damaged.speed = 0.1f;


	animation = &stand;

	collider = App->collision->AddCollider({ 0, 0, 60, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);






	original_pos.x = x;
	original_pos.y = y;


	hp = 106.0f;
	if (hp <= 0)	{ App->scene_village->ending = true; }

	damaged_hp = 7;
	death_type = SMALL_ENEMY;
	anim_type = ATTACKING;
	flying = false;
	killscore = 6000;
	discount = false;
	
}

void Enemy_TrumpThird::Move()
{
	position.x = App->scene_village->train_x + 15;
	position.y = App->scene_village->back_train_y + 2;

	if (hp <= 5 && !discount)
	{
		discount = true;
		App->scene_village->trumpcounter--;
	}

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

void Enemy_TrumpThird::Shoot()
{
	if (anim_type != DEAD && App->scene_village->trumpcounter == 1 && App->scene_village->trumpattack)
	{
		if (reload == 1)
		{
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -2, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, 2, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, -2, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 2, 1.5);
		}

		if (reload == 7)
		{
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -1.5, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, 1.5, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, -1.5, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 1.5, 1.5);
		}

		if (reload == 12)
		{
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.3, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, 0.3, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, -0.3, 1.5);
			App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.3, 1.5);
		}


		if (reload == 25)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.3, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.3, 3);
		}

		if (reload == 35)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.6, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.6, 3);
		}

		if (reload == 45)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.9, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.9, 3);
		}

		if (reload == 55)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.6, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.6, 3);
		}

		if (reload == 65)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.3, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.3, 3);
		}

		if (reload == 75)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.6, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.6, 3);
		}

		if (reload == 85)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.9, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.9, 3);
		}

		if (reload == 95)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, -0.6, 3);
			App->particles->AddParticle(App->particles->bigshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0.6, 3);
		}
		reload++;
		if (reload == 180)reload = 0;
	}
}