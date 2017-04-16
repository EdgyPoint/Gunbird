#include "Application.h"
#include "Enemy_Balloon.h"
#include "ModuleCollision.h"


Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0, 0, 53, 53 });
	fly.PushBack({ 53, 0, 53, 53 });
	fly.PushBack({ 106, 0, 53 ,53 });
	fly.PushBack({ 159, 0, 53, 53 });
	fly.PushBack({ 212, 0, 53, 53 });

	animation = &fly;

	path.PushBack({ 0.0f, 0.75f }, 50);
	path.PushBack({ 0.0f,0.0f }, 300);
	path.PushBack({ 0.0f, 0.75f }, 300);

	collider = App->collision->AddCollider({ 0, 0, 42, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Balloon::Move()
{
	position = original_pos + path.GetCurrentPosition();
}
