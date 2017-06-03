#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "Enemy_GreenRobot.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleVillageScene.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_GreenRobot::Enemy_GreenRobot(int x, int y, int option) : Enemy(x, y, option)
{
	aditionalanimation = true;

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

	down.PushBack({ 920, 460, 20, 20 });
	down_hit.PushBack({ 920, 480, 20, 20 });
	down_damaged.PushBack({ 920, 500, 20, 20 });

	downr1.PushBack({ 940, 460, 20, 20 });
	downr1_hit.PushBack({ 940, 480, 20, 20 });
	downr1_damaged.PushBack({ 940, 500, 20, 20 });

	downr2.PushBack({ 960, 460, 20, 20 });
	downr2_hit.PushBack({ 960, 480, 20, 20 });
	downr2_damaged.PushBack({ 960, 500, 20, 20 });

	downr3.PushBack({ 980, 460, 20, 20 });
	downr3_hit.PushBack({ 980, 480, 20, 20 });
	downr3_damaged.PushBack({ 980, 500, 20, 20 });

	right.PushBack({ 1000, 460, 20, 20 });
	right_hit.PushBack({ 1000, 480, 20, 20 });
	right_damaged.PushBack({ 1000, 500, 20, 20 });

	rightu1.PushBack({ 1020, 460, 20, 20 });
	rightu1_hit.PushBack({ 1020, 480, 20, 20 });
	rightu1_damaged.PushBack({ 1020, 500, 20, 20 });

	rightu2.PushBack({ 1040, 460, 20, 20 });
	rightu2_hit.PushBack({ 1040, 480, 20, 20 });
	rightu2_damaged.PushBack({ 1040, 500, 20, 20 });

	rightu3.PushBack({ 1060, 460, 20, 20 });
	rightu3_hit.PushBack({ 1060, 480, 20, 20 });
	rightu3_damaged.PushBack({ 1060, 500, 20, 20 });

	up.PushBack({ 1080, 460, 20, 20 });
	up_hit.PushBack({ 1080, 480, 20, 20 });
	up_damaged.PushBack({ 1080, 500, 20, 20 });

	upl1.PushBack({ 1100, 460, 20, 20 });
	upl1_hit.PushBack({ 1100, 480, 20, 20 });
	upl1_damaged.PushBack({ 1100, 500, 20, 20 });

	upl2.PushBack({ 1120, 460, 20, 20 });
	upl2_hit.PushBack({ 1120, 480, 20, 20 });
	upl2_damaged.PushBack({ 1120, 500, 20, 20 });

	upl3.PushBack({ 1140, 460, 20, 20 });
	upl3_hit.PushBack({ 1140, 480, 20, 20 });
	upl3_damaged.PushBack({ 1140, 500, 20, 20 });

	left.PushBack({ 1160, 460, 20, 20 });
	left_hit.PushBack({ 1160, 480, 20, 20 });
	left_damaged.PushBack({ 1160, 500, 20, 20 });

	leftd1.PushBack({ 1180, 460, 20, 20 });
	leftd1_hit.PushBack({ 1180, 480, 20, 20 });
	leftd1_damaged.PushBack({ 1180, 500, 20, 20 });

	leftd2.PushBack({ 1200, 460, 20, 20 });
	leftd2_hit.PushBack({ 1200, 480, 20, 20 });
	leftd2_damaged.PushBack({ 1200, 500, 20, 20 });

	leftd3.PushBack({ 1220, 460, 20, 20 });
	leftd3_hit.PushBack({ 1220, 480, 20, 20 });
	leftd3_damaged.PushBack({ 1120, 500, 20, 20 });

	animation = &walk_backward;

	path.PushBack({ 0.0f, 0.4f }, 300);
	path.PushBack({ 0.0f, 0.05f }, 1800);
	path.PushBack({ 0.0f, 0.8f }, 300);

	collider = App->collision->AddCollider({ 0, 0, 76, 76 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	to_draw = false;

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

	App->scene_village->tank_position.x = position.x;
	App->scene_village->tank_position.y = position.y;

	counter++;
	if (counter == 20)
		counter = 0;

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
	
	angle = AngleCalc({ App->player->position.x + 14, App->player->position.y + 16 }, { position.x + 5, position.y + 7 });
	angle2 = AngleCalc({ App->player->position.x + 14, App->player->position.y + 16 }, { position.x + 45, position.y + 7 });

	if (angle > 11.25 && angle <= 33.75)
	{
		if (status == NORMAL) { extra_animation = &rightu1; }
		if (status == HIT) { extra_animation = &rightu1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &rightu1_damaged;
			else
				extra_animation = &rightu1;
		}
	}
	else if (angle > 33.75 && angle <= 56.25)
	{
		if (status == NORMAL) { extra_animation = &rightu2; }
		if (status == HIT) { extra_animation = &rightu2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &rightu2_damaged;
			else
				extra_animation = &rightu2;
		}
	}
	else if (angle > 56.25 && angle <= 78.75)
	{
		if (status == NORMAL) { extra_animation = &rightu3; }
		if (status == HIT) { extra_animation = &rightu3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &rightu3_damaged;
			else
				extra_animation = &rightu3;
		}
	}
	else if (angle > 78.75 && angle <= 101.25)
	{
		if (status == NORMAL) { extra_animation = &up; }
		if (status == HIT) { extra_animation = &up_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &up_damaged;
			else
				extra_animation = &up;
		}
	}
	else if (angle > 101.25 && angle <= 123.75)
	{
		if (status == NORMAL) { extra_animation = &upl1; }
		if (status == HIT) { extra_animation = &upl1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &upl1_damaged;
			else
				extra_animation = &upl1;
		}
	}
	else if (angle > 123.75 && angle <= 146.25)
	{
		if (status == NORMAL) { extra_animation = &upl2; }
		if (status == HIT) { extra_animation = &upl2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &upl2_damaged;
			else
				extra_animation = &upl2;
		}
	}
	else if (angle > 146.25 && angle <= 168.75) 
	{
		if (status == NORMAL) { extra_animation = &upl3; }
		if (status == HIT) { extra_animation = &upl3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &upl3_damaged;
			else
				extra_animation = &upl3;
		}
	}
	else if (angle > 168.75 && angle <= 191.25)
	{
		if (status == NORMAL) { extra_animation = &left; }
		if (status == HIT) { extra_animation = &left_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &left_damaged;
			else
				extra_animation = &left;
		}
	}
	else if (angle > 191, 25 && angle <= 213.75)
	{
		if (status == NORMAL) { extra_animation = &leftd1; }
		if (status == HIT) { extra_animation = &leftd1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &leftd1_damaged;
			else
				extra_animation = &leftd1;
		}
	}
	else if (angle > 213.75 && angle <= 236.25)
	{
		if (status == NORMAL) { extra_animation = &leftd2; }
		if (status == HIT) { extra_animation = &leftd2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &leftd2_damaged;
			else
				extra_animation = &leftd2;
		}
	}
	else if (angle > 236.25 && angle <= 258.75) 
	{
		if (status == NORMAL) { extra_animation = &leftd3; }
		if (status == HIT) { extra_animation = &leftd3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &leftd3_damaged;
			else
				extra_animation = &leftd3;
		}
	}
	else if (angle > 258.75 && angle <= 281.25)
	{
		if (status == NORMAL) { extra_animation = &down; }
		if (status == HIT) { extra_animation = &down_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &down_damaged;
			else
				extra_animation = &down;
		}
	}
	else if (angle > 281.25 && angle <= 303.75)
	{
		if (status == NORMAL) { extra_animation = &downr1; }
		if (status == HIT) { extra_animation = &downr1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &downr1_damaged;
			else
				extra_animation = &downr1;
		}
	}
	else if (angle > 303.75 && angle <= 326.25)
	{
		if (status == NORMAL) { extra_animation = &downr2; }
		if (status == HIT) { extra_animation = &downr2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &downr2_damaged;
			else
				extra_animation = &downr2;
		}
	}
	else if (angle > 326.25 && angle <= 348.75) 
	{
		if (status == NORMAL) { extra_animation = &downr3; }
		if (status == HIT) { extra_animation = &downr3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &downr3_damaged;
			else
				extra_animation = &downr3;
		}
	}
	else
	{
		if (status == NORMAL) { extra_animation = &right; }
		if (status == HIT) { extra_animation = &right_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation = &right_damaged;
			else
				extra_animation = &right;
		}
	}





	if (angle2 > 11.25 && angle2 <= 33.75)
	{
		if (status == NORMAL) { extra_animation2 = &rightu1; }
		if (status == HIT) { extra_animation2 = &rightu1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &rightu1_damaged;
			else
				extra_animation2 = &rightu1;
		}
	}
	else if (angle2 > 33.75 && angle2 <= 56.25)
	{
		if (status == NORMAL) { extra_animation2 = &rightu2; }
		if (status == HIT) { extra_animation2 = &rightu2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &rightu2_damaged;
			else
				extra_animation2 = &rightu2;
		}
	}
	else if (angle2 > 56.25 && angle2 <= 78.75)
	{
		if (status == NORMAL) { extra_animation2 = &rightu3; }
		if (status == HIT) { extra_animation2 = &rightu3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &rightu3_damaged;
			else
				extra_animation2 = &rightu3;
		}
	}
	else if (angle2 > 78.75 && angle2 <= 101.25)
	{
		if (status == NORMAL) { extra_animation2 = &up; }
		if (status == HIT) { extra_animation2 = &up_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &up_damaged;
			else
				extra_animation2 = &up;
		}
	}
	else if (angle2 > 101.25 && angle2 <= 123.75)
	{
		if (status == NORMAL) { extra_animation2 = &upl1; }
		if (status == HIT) { extra_animation2 = &upl1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &upl1_damaged;
			else
				extra_animation2 = &upl1;
		}
	}
	else if (angle2 > 123.75 && angle2 <= 146.25)
	{
		if (status == NORMAL) { extra_animation2 = &upl2; }
		if (status == HIT) { extra_animation2 = &upl2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &upl2_damaged;
			else
				extra_animation2 = &upl2;
		}
	}
	else if (angle2 > 146.25 && angle2 <= 168.75)
	{
		if (status == NORMAL) { extra_animation2 = &upl3; }
		if (status == HIT) { extra_animation2 = &upl3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &upl3_damaged;
			else
				extra_animation2 = &upl3;
		}
	}
	else if (angle2 > 168.75 && angle2 <= 191.25)
	{
		if (status == NORMAL) { extra_animation2 = &left; }
		if (status == HIT) { extra_animation2 = &left_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &left_damaged;
			else
				extra_animation2 = &left;
		}
	}
	else if (angle2 > 191, 25 && angle2 <= 213.75)
	{
		if (status == NORMAL) { extra_animation2 = &leftd1; }
		if (status == HIT) { extra_animation2 = &leftd1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &leftd1_damaged;
			else
				extra_animation2 = &leftd1;
		}
	}
	else if (angle2 > 213.75 && angle2 <= 236.25)
	{
		if (status == NORMAL) { extra_animation2 = &leftd2; }
		if (status == HIT) { extra_animation2 = &leftd2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &leftd2_damaged;
			else
				extra_animation2 = &leftd2;
		}
	}
	else if (angle2 > 236.25 && angle2 <= 258.75)
	{
		if (status == NORMAL) { extra_animation2 = &leftd3; }
		if (status == HIT) { extra_animation2 = &leftd3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &leftd3_damaged;
			else
				extra_animation2 = &leftd3;
		}
	}
	else if (angle2 > 258.75 && angle2 <= 281.25)
	{
		if (status == NORMAL) { extra_animation2 = &down; }
		if (status == HIT) { extra_animation2 = &down_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &down_damaged;
			else
				extra_animation2 = &down;
		}
	}
	else if (angle2 > 281.25 && angle2 <= 303.75)
	{
		if (status == NORMAL) { extra_animation2 = &downr1; }
		if (status == HIT) { extra_animation2 = &downr1_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &downr1_damaged;
			else
				extra_animation2 = &downr1;
		}
	}
	else if (angle2 > 303.75 && angle2 <= 326.25)
	{
		if (status == NORMAL) { extra_animation2 = &downr2; }
		if (status == HIT) { extra_animation2 = &downr2_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &downr2_damaged;
			else
				extra_animation2 = &downr2;
		}
	}
	else if (angle2 > 326.25 && angle2 <= 348.75)
	{
		if (status == NORMAL) { extra_animation2 = &downr3; }
		if (status == HIT) { extra_animation2 = &downr3_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &downr3_damaged;
			else
				extra_animation2 = &downr3;
		}
	}
	else
	{
		if (status == NORMAL) { extra_animation2 = &right; }
		if (status == HIT) { extra_animation2 = &right_hit; }
		if (status == DAMAGED)
		{
			if (counter == 0)
				extra_animation2 = &right_damaged;
			else
				extra_animation2 = &right;
		}
	}

	App->scene_village->tank_anim = animation;
	App->scene_village->tank_extra1 = extra_animation;
	App->scene_village->tank_extra2 = extra_animation2;
	App->scene_village->tank_hp = hp;

}

void Enemy_GreenRobot::Shoot()
{

}

void Enemy_GreenRobot::Extra_animation()
{
	
}
