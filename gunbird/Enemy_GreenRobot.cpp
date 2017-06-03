#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_GreenRobot.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_GreenRobot::Enemy_GreenRobot(int x, int y, int option) : Enemy(x, y, option)
{
	dead.PushBack({ 1292, 76, 76, 76 });

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
	walk_backward.speed = 0.15f;

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
	walk_backward_hit.speed = 0.15f;

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
	walk_backward_damaged.speed = 0.15f;

	animation = &walk_backward;

	path.PushBack({ 0.0f, 0.4f }, 300);
	path.PushBack({ 0.0f, 0.05f }, 1800);
	path.PushBack({ 0.0f, 0.8f }, 300);

	collider = App->collision->AddCollider({ 0, 0, 76, 76 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	hp = 87.0f;
	damaged_hp = 20.0f;
	death_type = MEDIUM_ENEMY;
	flying = false;
	killscore = 4000;
	dead_anim = true;
}

void Enemy_GreenRobot::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (hp <= 0)anim_type = DEAD;

	if (anim_type != DEAD)
	{
		if (path.steps[0].active)anim_type = STAND;
		if (path.steps[1].active)anim_type = BACKWARD;
		if (path.steps[2].active)anim_type = FORWARD;
	}

	switch (anim_type)
	{
	case STAND:
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
		break;
	}
	case BACKWARD:
	{
		if (status == NORMAL)
			animation = &walk_backward;

		if (status == HIT)
			animation = &walk_backward_hit;
		if (status == DAMAGED)
		{
			if (counter == 0)
				animation = &walk_backward_damaged;
			else
				animation = &walk_backward;
		}
		break;
	}
	case FORWARD:
	{
		if (status == NORMAL)
			animation = &walk_backward;

		if (status == HIT)
			animation = &walk_backward_hit;
		if (status == DAMAGED)
		{
			if (counter == 0)
				animation = &walk_backward_damaged;
			else
				animation = &walk_backward;
		}
		walk_backward.speed = 0.3f;
		walk_backward_hit.speed = 0.3f;
		walk_backward_damaged.speed = 0.3f;
		break;
	}
	case DEAD:
	{
		animation = &dead;
		path.Stop();
		collider->rect.h = 0;
		collider->rect.w = 0;
		collider->SetPos(-100, 500);
	}
	}
	counter++;
	if (counter == 20)
		counter = 0;
}