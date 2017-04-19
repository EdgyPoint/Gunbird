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

const int Enemy::GetOption() { return pathoption; }

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
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

	App->particles->AddParticle(App->particles->powerup, collider->rect.x, collider->rect.y, COLLIDER_PICKUP);
}