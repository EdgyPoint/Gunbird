#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_TrainTurret.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"




Enemy_TrainTurret::Enemy_TrainTurret(int x, int y, int option) : Enemy(x, y, option)
{
	//closed animation
	closed.PushBack({ 0, 291, 22, 23 });

	closed_hit.PushBack({ 0, 314, 22, 23 });

	closed_damaged.PushBack({ 0, 337, 22, 23 });


	collider = App->collision->AddCollider({ 0, 0, 22, 23 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &closed;


	path.PushBack({ 0.0f, 0.4f }, 10000);
	original_pos.x = x;
	original_pos.y = y;

	hp = 7.0f;
	damaged_hp = 4.0f;
	death_type = SMALL_ENEMY;
	anim_type = CLOSED;
	drops_coin = false;
	flying = false;
	dead_anim = true;
	killscore = 200;
}

void Enemy_TrainTurret::Move()
{
	position = original_pos + path.GetCurrentPosition();

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
	counter++;
	if (counter == 20)counter = 0;
}

void Enemy_TrainTurret::Shoot()
{
	if (position.y > 0 && position.y < SCREEN_HEIGHT && reloadd == 0 && anim_type != DEAD)
	{
		bullet_speed = ShootCalculator({ position.x + 5, position.y + 10 }, { App->player->position.x, App->player->position.y });
		App->particles->AddParticle(App->particles->smallshot, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, bullet_speed.x, bullet_speed.y);
		App->particles->AddParticle(App->particles->smallshot, position.x + 32, position.y + 10, COLLIDER_ENEMY_SHOT, bullet_speed.x, bullet_speed.y);
	}
	reloadd++;
	if (reloadd == 60) reloadd = 0;
}

