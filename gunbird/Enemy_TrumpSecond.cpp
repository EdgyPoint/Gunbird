#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_TrumpSecond.h"
#include "ModuleVillageScene.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_TrumpSecond::Enemy_TrumpSecond(int x, int y, int option) : Enemy(x, y, option)
{
	stand.PushBack({ 1392, 120, 60, 60 });

	stand_hit.PushBack({ 1572, 120, 60, 60 });

	stand_damaged.PushBack({ 1752, 120, 60, 60 });


	attacking.PushBack({ 1392, 120, 60, 60 });
	attacking.PushBack({ 1452, 120, 60, 60 });
	attacking.PushBack({ 1512, 120, 60, 60 });
	attacking.speed = 0.1f;

	attacking_hit.PushBack({ 1572, 120, 60, 60 });
	attacking_hit.PushBack({ 1632, 120, 60, 60 });
	attacking_hit.PushBack({ 1692, 120, 60, 60 });

	attacking.speed = 0.1f;


	attacking_damaged.PushBack({ 1752, 120, 60, 60 });
	attacking_damaged.PushBack({ 1812, 120, 60, 60 });
	attacking_damaged.PushBack({ 1872, 120, 60, 60 });

	attacking.speed = 0.1f;



	animation = &stand;

	collider = App->collision->AddCollider({ 0, 0, 60, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);






	original_pos.x = x;
	original_pos.y = y;

	hp = 106.0f;
	damaged_hp = 7;
	death_type = SMALL_ENEMY;
	anim_type = ATTACKING;
	flying = false;
	killscore = 6000;
	discount = false;

}

void Enemy_TrumpSecond::Move()
{

	position.x = App->scene_village->train_x + 15;
	position.y = App->scene_village->back_train_y + 60;


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

void Enemy_TrumpSecond::Shoot()
{
	if (anim_type != DEAD && App->scene_village->trumpcounter == 2 && App->scene_village->trumpattack)
	{
		if (reload == 0)
		{
		App->particles->AddParticle(App->particles->smallshot, position.x + 10, position.y + 13, COLLIDER_ENEMY_SHOT, 0, 3);
		App->particles->AddParticle(App->particles->smallshot, position.x + 46, position.y + 13, COLLIDER_ENEMY_SHOT, 0, 3);
		}

		if (reload == 10)
		{
		App->particles->AddParticle(App->particles->smallshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 0, 3);
		App->particles->AddParticle(App->particles->smallshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 0, 3);
		}

		if (reload == 60)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 1.5, 2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 2, 1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 0.5, 2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 2.5, 0.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -1.5, 2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -2, 1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -0.5, 2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -2.5, 0.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 1.5, -2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 2, -1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 0.5, -2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, 2.5, -0.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -1.5, -2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -2, -1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -0.5, -2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 5, position.y + 13, COLLIDER_ENEMY_SHOT, -2.5, -0.5);
		}

		if (reload == 80)
		{
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 1.5, 2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 2, 1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 0.5, 2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 2.5, 0.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -1.5, 2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -2, 1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -0.5, 2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -2.5, 0.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 1.5, -2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 2, -1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 0.5, -2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, 2.5, -0.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -1.5, -2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -2, -1.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -0.5, -2.5);
			App->particles->AddParticle(App->particles->bigshot, position.x + 51, position.y + 13, COLLIDER_ENEMY_SHOT, -2.5, -0.5);
		}

		reload++;
		if (reload == 180)reload = 0;
	}
}