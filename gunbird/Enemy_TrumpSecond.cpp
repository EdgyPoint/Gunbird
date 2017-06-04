#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_TrumpSecond.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_TrumpSecond::Enemy_TrumpSecond(int x, int y, int option) : Enemy(x, y, option)
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

void Enemy_TrumpSecond::Move()
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

void Enemy_TrumpSecond::Shoot()
{
	if (anim_type == ATTACKING)
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