#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_4CannonTurret.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_4CannonTurret::Enemy_4CannonTurret(int x, int y, int option) : Enemy(x, y, option)
{
	closed.PushBack({ 0, 681, 30, 42 });
	closed.loop = false;

	closed_hit.PushBack({ 150, 681, 30, 42 });
	closed.loop = false;

	closed_damaged.PushBack({ 300, 681, 30, 42 });
	closed.loop = false;

	attacking.PushBack({ 30, 681, 30, 42 });
	attacking.PushBack({ 60, 681, 30, 42 });
	attacking.PushBack({ 90, 681, 30, 42 });
	attacking.PushBack({ 120, 681, 30, 42 });
	attacking.PushBack({ 0, 723, 30, 42 });
	attacking.PushBack({ 30, 723, 30, 42 });
	attacking.PushBack({ 60, 723, 30, 42 });
	attacking.PushBack({ 90, 723, 30, 42 });
	attacking.PushBack({ 120, 723, 30, 42 });
	attacking.PushBack({ 0, 765, 30, 42 });
	attacking.PushBack({ 30, 765, 30, 42 });
	attacking.PushBack({ 60, 765, 30, 42 });
	attacking.PushBack({ 90, 765, 30, 42 });
	attacking.PushBack({ 120, 765, 30, 42 });
	attacking.PushBack({ 0, 807, 30, 42 });
	attacking.PushBack({ 30, 807, 30, 42 });
	attacking.PushBack({ 60, 807, 30, 42 });
	attacking.PushBack({ 90, 807, 30, 42 });
	attacking.PushBack({ 120, 807, 30, 42 });
	attacking.PushBack({ 0, 849, 30, 42 });
	attacking.PushBack({ 30, 849, 30, 42 });
	attacking.PushBack({ 60, 849, 30, 42 });
	attacking.PushBack({ 90, 849, 30, 42 });
	attacking.PushBack({ 120, 849, 30, 42 });
	attacking.PushBack({ 0, 891, 30, 42 });
	attacking.PushBack({ 30, 891, 30, 42 });
	attacking.PushBack({ 60, 891, 30, 42 });
	attacking.PushBack({ 90, 891, 30, 42 });
	attacking.speed = 0.2f;
	
	attacking_hit.PushBack({ 180, 681, 30, 42 });
	attacking_hit.PushBack({ 210, 681, 30, 42 });
	attacking_hit.PushBack({ 240, 681, 30, 42 });
	attacking_hit.PushBack({ 270, 681, 30, 42 });
	attacking_hit.PushBack({ 150, 723, 30, 42 });
	attacking_hit.PushBack({ 180, 723, 30, 42 });
	attacking_hit.PushBack({ 210, 723, 30, 42 });
	attacking_hit.PushBack({ 240, 723, 30, 42 });
	attacking_hit.PushBack({ 270, 723, 30, 42 });
	attacking_hit.PushBack({ 150, 765, 30, 42 });
	attacking_hit.PushBack({ 180, 765, 30, 42 });
	attacking_hit.PushBack({ 210, 765, 30, 42 });
	attacking_hit.PushBack({ 240, 765, 30, 42 });
	attacking_hit.PushBack({ 270, 765, 30, 42 });
	attacking_hit.PushBack({ 150, 807, 30, 42 });
	attacking_hit.PushBack({ 180, 807, 30, 42 });
	attacking_hit.PushBack({ 210, 807, 30, 42 });
	attacking_hit.PushBack({ 240, 807, 30, 42 });
	attacking_hit.PushBack({ 270, 807, 30, 42 });
	attacking_hit.PushBack({ 150, 849, 30, 42 });
	attacking_hit.PushBack({ 180, 849, 30, 42 });
	attacking_hit.PushBack({ 210, 849, 30, 42 });
	attacking_hit.PushBack({ 240, 849, 30, 42 });
	attacking_hit.PushBack({ 270, 849, 30, 42 });
	attacking_hit.PushBack({ 150, 891, 30, 42 });
	attacking_hit.PushBack({ 170, 891, 30, 42 });
	attacking_hit.PushBack({ 210, 891, 30, 42 });
	attacking_hit.PushBack({ 240, 891, 30, 42 });
	attacking_hit.speed = 0.2f;

	attacking_damaged.PushBack({ 330, 681, 30, 42 });
	attacking_damaged.PushBack({ 360, 681, 30, 42 });
	attacking_damaged.PushBack({ 390, 681, 30, 42 });
	attacking_damaged.PushBack({ 420, 681, 30, 42 });
	attacking_damaged.PushBack({ 300, 723, 30, 42 });
	attacking_damaged.PushBack({ 330, 723, 30, 42 });
	attacking_damaged.PushBack({ 360, 723, 30, 42 });
	attacking_damaged.PushBack({ 390, 723, 30, 42 });
	attacking_damaged.PushBack({ 420, 723, 30, 42 });
	attacking_damaged.PushBack({ 300, 765, 30, 42 });
	attacking_damaged.PushBack({ 330, 765, 30, 42 });
	attacking_damaged.PushBack({ 360, 765, 30, 42 });
	attacking_damaged.PushBack({ 390, 765, 30, 42 });
	attacking_damaged.PushBack({ 420, 765, 30, 42 });
	attacking_damaged.PushBack({ 300, 807, 30, 42 });
	attacking_damaged.PushBack({ 330, 807, 30, 42 });
	attacking_damaged.PushBack({ 360, 807, 30, 42 });
	attacking_damaged.PushBack({ 390, 807, 30, 42 });
	attacking_damaged.PushBack({ 420, 807, 30, 42 });
	attacking_damaged.PushBack({ 300, 849, 30, 42 });
	attacking_damaged.PushBack({ 330, 849, 30, 42 });
	attacking_damaged.PushBack({ 360, 849, 30, 42 });
	attacking_damaged.PushBack({ 390, 849, 30, 42 });
	attacking_damaged.PushBack({ 420, 849, 30, 42 });
	attacking_damaged.PushBack({ 300, 891, 30, 42 });
	attacking_damaged.PushBack({ 330, 891, 30, 42 });
	attacking_damaged.PushBack({ 360, 891, 30, 42 });
	attacking_damaged.PushBack({ 390, 891, 30, 42 });
	attacking_damaged.speed = 0.2f;

	animation = &closed;

	collider = App->collision->AddCollider({ 0, 0, 30, 43 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.4f }, 10000);

	original_pos.x = x;
	original_pos.y = y;

	hp = 10.0f;
	damaged_hp = 7;
	death_type = SMALL_ENEMY;
	drops_coin = true;
	anim_type = CLOSED;
	flying = false;
	killscore = 200;
}

void Enemy_4CannonTurret::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (position.y > 0 && position.y < 100) anim_type = ATTACKING;
	else anim_type = CLOSED;


	if (anim_type == CLOSED)
	{
		if (status == NORMAL)
			animation = &closed;

		if (status == HIT)
			animation = &closed_hit;

		if (status == DAMAGED)
		{
			if (counter == 0)
				animation = &closed_damaged;
			else
				animation = &closed;
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

void Enemy_4CannonTurret::Shoot()
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
