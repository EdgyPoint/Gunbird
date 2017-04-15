#include "Application.h"
#include "Enemy_Balloon.h"
#include "ModuleCollision.h"


Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 11, 6,42,53 });
	fly.PushBack({ 64, 6,42,53 });
	fly.PushBack({ 116, 6,42,53 });
	fly.PushBack({ 158, 6,42,53 });
	fly.PushBack({ 219, 6,42,53 });

	animation = &fly;

	path.PushBack({ -1.0f,-0.75f }, 120);
	path.PushBack({ -1.0f,0.75f }, 100);
	path.PushBack({ -1.0f,1.25f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 21, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Balloon::Move()
{
	position = original_pos + path.GetCurrentPosition();
}
