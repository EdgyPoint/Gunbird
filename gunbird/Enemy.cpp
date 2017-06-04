#include "Application.h"
#include "Enemy.h"
#include <math.h>
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
	float module;
	fPoint distance;
	fPoint speed;

	distance.x = player.x - position.x;
	distance.y = player.y - position.y;

	module = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));

	distance.x /= module;
	distance.y /= module;

	speed.x = distance.x*BULLET_SPEED +0.3f;
	speed.y = distance.y*BULLET_SPEED + 0.3f;

	return speed;
}

float Enemy::AngleCalc(iPoint position, iPoint player)
{
	float module;
	fPoint distance;
	float angle;

	distance.x = player.x - position.x;
	distance.y = player.y - position.y;

	module = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));


	angle = fabsf(distance.x) / module;


	angle = acosf(angle);

	angle *= 180 / PI;

	if (position.x >= player.x && position.y >= player.y)
		angle = 360 - angle;
	if (position.x < player.x && position.y >= player.y)
		angle = 180 + angle;
	if (position.x < player.x && position.y < player.y)
		angle = 180 - angle;

	return angle;
}

void Enemy::Draw(SDL_Texture* sprites, Enemy* enemy)
{
	if (collider != nullptr)
	{
		if (hp > 0)
			collider->SetPos(position.x, position.y);
	}


	if (enemy->hp <= enemy->damaged_hp && enemy->hp > 0)
		enemy->status = DAMAGED;

	if (animation != nullptr && to_draw)
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
		else if (collider->type == COLLIDER_BOMBSHOT && enemy->already_hit == false)
			enemy->hp -= 10;
		else if (collider->type == COLLIDER_CHARGEDSHOT && enemy->already_hit == false)
			enemy->hp -= 12;
		else if (collider->type == COLLIDER_BOMBSHOT2 && enemy->already_hit == false)
			enemy->hp -= 10;
		else if (collider->type == COLLIDER_CHARGEDSHOT2 && enemy->already_hit == false)
			enemy->hp -= 12;

	if (hitCD == 0)
	{
		enemy->already_hit = false;
	}

	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER2_SHOT)
	{
		enemy->status = HIT;
		App->particles->AddParticle(App->particles->impact, collider->rect.x - 6, collider->rect.y - 47, COLLIDER_NONE);
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/impact.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}
	if ((collider->type == COLLIDER_BOMBSHOT || collider->type == COLLIDER_CHARGEDSHOT || collider->type == COLLIDER_BOMBSHOT2 || collider->type == COLLIDER_CHARGEDSHOT2) && enemy->already_hit == false)
	{
		enemy->status = HIT;
		enemy->already_hit = true;
		enemy->hitCD = 6;
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/impact.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}
	if (enemy->already_hit == true)
	{
		enemy->hitCD--;
	}
}


void Enemy::ToDie(Enemy* enemy, Collider* col)
{
	if (enemy->drops_powerup)
	{
		App->particles->AddParticle(App->particles->powerup, enemy->position.x + 12, enemy->position.y + 26, COLLIDER_POWERUP, 1, 1, 0, true, ITEM_POWERUP);
	}

	if (enemy->drops_bomb)
	{
		App->particles->AddParticle(App->particles->bomb, enemy->position.x + 12, enemy->position.y + 26, COLLIDER_BOMB, 1, 1, 0, true, ITEM_BOMB);
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

	if (col->type == COLLIDER_PLAYER_SHOT || col->type == COLLIDER_CHARGEDSHOT || col->type == COLLIDER_BOMBSHOT)
		App->player->score += enemy->killscore;

	if (col->type == COLLIDER_PLAYER2_SHOT || col->type == COLLIDER_CHARGEDSHOT2 || col->type == COLLIDER_BOMBSHOT2)
		App->player2->score += enemy->killscore;
}