#include<math.h>
#include "Application.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleCastleScene.h"
#include "ModuleVillageScene.h"
#include "Enemy_FlyingGunner.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"

Enemy_FlyingGunner::Enemy_FlyingGunner(int x, int y, int option) : Enemy(x, y, option)
{
	status = OPENING;

	nothing.PushBack({ 866, 328, 32, 33 });
	//23 frames
	arriving_left.PushBack({ 836, 380, 32, 36 });
	arriving_left.PushBack({ 836, 422, 32, 36 });
	arriving_left.PushBack({ 836, 338, 32, 36 });
	arriving_left.speed = 0.5f;

	//5 frames
	arriving_left1.PushBack({ 874, 338, 32, 36 });
	arriving_left1.PushBack({ 874, 422, 32, 36 });
	arriving_left1.PushBack({ 732, 380, 32, 36 });
	arriving_left1.PushBack({ 764, 338, 32, 36 });
	arriving_left1.PushBack({ 764, 380, 32, 36 });
	arriving_left1.loop = false;
	arriving_left1.speed = 0.5f;
		
//7 frames
	arriving_left2.PushBack({ 798, 338, 32, 36 });
	arriving_left2.PushBack({ 798, 380, 32, 36 });
	arriving_left2.PushBack({ 798, 422, 32, 36 });
	arriving_left2.loop = false;
	arriving_left2.speed = 0.5f;
	 //4frames
	arriving_left3.PushBack({ 764, 380, 32, 36 });
	arriving_left3.PushBack({ 764, 422, 32, 36 });
	arriving_left3.PushBack({ 764, 338, 32, 36 });
	arriving_left3.PushBack({ 764, 465, 32, 36 });
	arriving_left3.speed = 0.5f;
	//29 frames
	staying.PushBack({ 732, 380, 32, 36 });
	staying.PushBack({ 732, 422, 32, 36 });
	staying.PushBack({ 732, 338, 32, 36 });
	staying.loop = true;
	staying.speed = 0.5f;

	arriving_right1.PushBack({ 798, 380, 32, 36 });
	arriving_right1.PushBack({ 798, 422, 32, 36 });
	arriving_right1.PushBack({ 798, 338, 32, 36 });
	arriving_right1.PushBack({ 798, 380, 32, 36 });
	arriving_right1.PushBack({ 798, 422, 32, 36 });
	arriving_right1.PushBack({ 798, 338, 32, 36 });
	arriving_right1.PushBack({ 798, 380, 32, 36 });
	arriving_right1.PushBack({ 798, 422, 32, 36 });
	arriving_right1.PushBack({ 798, 338, 32, 36 });

	arriving_right1.PushBack({ 764, 380, 32, 36 });
	arriving_right1.PushBack({ 764, 338, 32, 36 });
	arriving_right1.PushBack({ 732, 422, 32, 36 });
	arriving_right1.PushBack({ 874, 338, 32, 36 });
	arriving_right1.loop = false;
	arriving_right1.speed = 0.3f;

	arriving_right2.PushBack({ 836, 338, 32, 36 });
	arriving_right2.PushBack({ 836, 380, 32, 36 });
	arriving_right2.PushBack({ 836, 422, 32, 36 });
	arriving_right2.loop = true;
	arriving_right2.speed = 0.3f;

	arriving_right3.PushBack({ 874, 338, 32, 36 });
	arriving_right3.PushBack({ 874, 380, 32, 36 });
	arriving_right3.PushBack({ 874, 422, 32, 36 });
	arriving_right3.PushBack({ 874, 465, 32, 36 });
	arriving_right3.speed = 0.3f;

	animation = &nothing;

	hp = 1.0f;

	if (option == 0)
	{
		path.PushBack({ 0.0f, 0.4f }, 17000); 
		path.PushBack({ 0.6f, 0.4f }, 51);
		path.PushBack({ 0.0f, 0.4f }, 45);
	}

	if (option == 1)
	{
		animation = &arriving_left;
		path.PushBack({ 0.0f, 0.4f }, 1900);
		path.PushBack({ 0.6f, 0.0f }, 46);
		path.PushBack({ 0.1f, 0.0f }, 10);
		path.PushBack({ 0.1f, 0.0f }, 14);
		path.PushBack({ 0.0f, 0.0f }, 8);
		path.PushBack({ 0.0f, 0.0f }, 70);
		path.PushBack({ 0.0f, 0.0f }, 8);
		path.PushBack({ -0.6f, 0.0f }, 10000);

	//	path.PushBack({ 0.6f,0.0f }, 10000);
	}

	collider = App->collision->AddCollider({ 0, 0,  32, 36 }, COLLIDER_TYPE::COLLIDER_ENEMY_F, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	original_x = x;

	death_type = SMALL_ENEMY;

	flying = true;
	killscore = 200;
}

void Enemy_FlyingGunner::Move()
{
	position = original_pos + path.GetCurrentPosition();
	if (pathoption == 1)
	{
	if(path.steps[2].active)
			animation = &arriving_left1;
	if(path.steps[3].active)
			animation = &arriving_left2;
	if(path.steps[4].active)
			animation = &arriving_left3;
	if(path.steps[5].active)
			animation = &staying;
	if (path.steps[6].active)
		animation = &arriving_left3;
	if (path.steps[5].active)
		animation = &arriving_left2;
		}
	

	/*if (pathoption == 0 && position.y == -50) { hasfinishedleft = true; }
	if (pathoption == 1 && position.y == -50) { hasfinishedright = true; }
	
	if (status == OPENING && hasfinishedleft == true)
	{
		status = NORMAL;  animation = &arriving_left1;
	}
	if (status == OPENING && hasfinishedright == true && pathoption == 1 && position.y == -50)
	{
		status = NORMAL;  animation = &arriving_right1;
	}
	if (status == NORMAL && animation->Finished() == true && pathoption == 0) 
	{	
		animation = &arriving_left2; 
	}
	if (status == NORMAL && animation->Finished() == true && pathoption == 1)
	{
		animation = &arriving_right2;
	}
	if (status == NORMAL && animation->Finished() == true && pathoption == 0)
	{
		animation = &arriving_left3;
	}
	if (status == NORMAL && animation->Finished() == true && pathoption == 1)
	{
		animation = &arriving_right3;
	}
	if (status == NORMAL && animation->Finished() == true)
	{
		animation = &staying;
	}*/

}

