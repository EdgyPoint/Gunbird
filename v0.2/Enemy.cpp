#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
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

void Enemy::Draw(SDL_Texture* sprites, Enemy* enemy)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (enemy->hp <= enemy->damaged_hp)
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

	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER2_SHOT)
		enemy->status = HIT;
}

void Enemy::ToDie(Enemy* enemy)
{
	App->particles->AddParticle(App->particles->powerup, enemy->position.x + 12, enemy->position.y + 26, COLLIDER_PICKUP);

	if (enemy->death_type == MEDIUM_ENEMY)
		App->particles->AddParticle(App->particles->medium_explosion, enemy->position.x - 26, enemy->position.y - 10, COLLIDER_NONE);
}