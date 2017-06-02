#include "Application.h"
#include "Enemy.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y, int option) : position(x, y), pathoption(option)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

fPoint Enemy::ShootCalculator(iPoint position, iPoint player)
{
	int module;
	fPoint distance;
	fPoint speed;

	distance.x = App->player->position.x - position.x;
	distance.y = App->player->position.y - position.y;

	module = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));

	distance.x /= module;
	distance.y /= module;

	speed.x = distance.x*BULLET_SPEED;
	speed.y = distance.y*BULLET_SPEED;

	return speed;
}

void Enemy::Draw(SDL_Texture* sprites, Enemy* enemy)
{
	if (collider != nullptr)
	{
			collider->SetPos(position.x, position.y);
	}


	if (enemy->hp <= enemy->damaged_hp && enemy->hp > 0)
		enemy->status = DAMAGED;

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));

	if (enemy->status == HIT)
	{
		if (enemy->hp > enemy->damaged_hp)
			enemy->status = NORMAL;
		else
			enemy->status = DAMAGED;
	}
}

void Enemy::OnCollision(Collider* collider, Enemy* enemy)
{

		if (collider->type == COLLIDER_PLAYER_SHOT && App->player->powerup_lv == 0)
			enemy->hp -= 1.0f;
		else if (collider->type == COLLIDER_PLAYER2_SHOT && App->player2->powerup_lv == 0)
			enemy->hp -= 1.0f;
		else if (collider->type == COLLIDER_PLAYER_SHOT && App->player->powerup_lv == 1)
			enemy->hp -= 1.25f;
		else if (collider->type == COLLIDER_PLAYER2_SHOT && App->player2->powerup_lv == 1)
			enemy->hp -= 1.25f;
		else if (collider->type == COLLIDER_PLAYER_SHOT && App->player->powerup_lv == 2)
			enemy->hp -= 1.0f;
		else if (collider->type == COLLIDER_PLAYER2_SHOT && App->player2->powerup_lv == 2)
			enemy->hp -= 1.0f;
		else if (collider->type == COLLIDER_PLAYER_SHOT && App->player->powerup_lv == 3)
			enemy->hp -= 1.25f;
		else if (collider->type == COLLIDER_PLAYER2_SHOT && App->player2->powerup_lv == 3)
			enemy->hp -= 1.25f;

		if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER2_SHOT)
		{
			enemy->status = HIT;
			collider->already_hit = true;
			App->particles->AddParticle(App->particles->impact, collider->rect.x - 6, collider->rect.y - 47, COLLIDER_NONE);
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/impact.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}
	

}


void Enemy::ToDie(Enemy* enemy, Collider* col)
{
	if (enemy->drops_powerup)
	{
		App->particles->AddParticle(App->particles->powerup, enemy->position.x + 12, enemy->position.y + 26, COLLIDER_POWERUP, 1, 1, 0, true, ITEM_POWERUP);
	}

	if (enemy->drops_coin)
		App->particles->AddParticle(App->particles->coin, enemy->position.x + 10, enemy->position.y + 25, COLLIDER_COIN, 0, 0.55f);


	if (enemy->death_type == MEDIUM_ENEMY)
	{
		App->particles->AddParticle(App->particles->medium_explosion, enemy->position.x - 26, enemy->position.y - 10, COLLIDER_NONE);
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/mediumexplosion.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}

	if (enemy->death_type == SMALL_ENEMY)
	{
		App->particles->AddParticle(App->particles->small_explosion, enemy->position.x - 12, enemy->position.y - 14, COLLIDER_NONE);
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/smallexplosion.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}

	if (col->type == COLLIDER_PLAYER_SHOT)
	App->player->score += enemy->killscore;

	if (col->type == COLLIDER_PLAYER2_SHOT)
		App->player2->score += enemy->killscore;
}