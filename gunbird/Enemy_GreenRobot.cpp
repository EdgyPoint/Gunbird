#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_GreenRobot.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_GreenRobot::Enemy_GreenRobot(int x, int y, int option) : Enemy(x, y, option)
{
	stand.PushBack({ 912, 0, 76, 76 });
	stand_hit.PushBack({ 912, 152, 76, 76 });
	stand_damaged.PushBack({ 912, 304, 76, 76 });

	walk_backward.PushBack({ 912, 0, 76, 76 });
	walk_backward.PushBack({ 988, 0, 76, 76 });
	walk_backward.PushBack({ 1064, 0, 76, 76 });
	walk_backward.PushBack({ 1140, 0, 76, 76 });
	walk_backward.PushBack({ 1216, 0, 76, 76 });
	walk_backward.PushBack({ 912, 76, 76, 76 });
	walk_backward.PushBack({ 988, 76, 76, 76 });
	walk_backward.PushBack({ 1064, 76, 76, 76 });
	walk_backward.PushBack({ 1140, 76, 76, 76 });
	walk_backward.PushBack({ 1216, 76, 76, 76 });
	walk_backward.loop = true;
	walk_backward.speed = 0.16f;

	walk_backward_hit.PushBack({ 912, 152, 76, 76 });
	walk_backward_hit.PushBack({ 988, 152, 76, 76 });
	walk_backward_hit.PushBack({ 1064, 152, 76, 76 });
	walk_backward_hit.PushBack({ 1140, 152, 76, 76 });
	walk_backward_hit.PushBack({ 1216, 152, 76, 76 });
	walk_backward_hit.PushBack({ 912, 228, 76, 76 });
	walk_backward_hit.PushBack({ 988, 228, 76, 76 });
	walk_backward_hit.PushBack({ 1064, 228, 76, 76 });
	walk_backward_hit.PushBack({ 1140, 228, 76, 76 });
	walk_backward_hit.PushBack({ 1216, 228, 76, 76 });
	walk_backward_hit.loop = true;
	walk_backward_hit.speed = 0.16f;

	walk_backward_damaged.PushBack({ 912, 304, 76, 76 });
	walk_backward_damaged.PushBack({ 988, 304, 76, 76 });
	walk_backward_damaged.PushBack({ 1064, 304, 76, 76 });
	walk_backward_damaged.PushBack({ 1140, 304, 76, 76 });
	walk_backward_damaged.PushBack({ 1216, 304, 76, 76 });
	walk_backward_damaged.PushBack({ 912, 380, 76, 76 });
	walk_backward_damaged.PushBack({ 988, 380, 76, 76 });
	walk_backward_damaged.PushBack({ 1064, 380, 76, 76 });
	walk_backward_damaged.PushBack({ 1140, 380, 76, 76 });
	walk_backward_damaged.PushBack({ 1216, 380, 76, 76 });
	walk_backward_damaged.loop = true;
	walk_backward_damaged.speed = 0.16f;

	animation = &walk_backward;

	path.PushBack({ 0.0f, 0.4f }, 200);
	path.PushBack({ 0.0f, 0.0f }, 1000);

	collider = App->collision->AddCollider({ 0, 0, 32, 35 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	hp = 87.0f;

	death_type = MEDIUM_ENEMY;
	flying = false;
	killscore = 4000;
}

void Enemy_GreenRobot::Move()
{
	position = original_pos + path.GetCurrentPosition();
}