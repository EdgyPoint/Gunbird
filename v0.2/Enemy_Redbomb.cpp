#include "Application.h"
#include "ModuleParticles.h"

#include "Enemy_Redbomb.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"

Enemy_Redbomb :: Enemy_Redbomb(int x, int y, int option) : Enemy(x, y, option)
{
	
	fly.PushBack({ 100, 58, 28, 32 });
	fly.PushBack({ 128, 58, 28, 32 });
	fly.PushBack({ 156, 58, 28, 32 });
	fly.PushBack({ 184, 58, 28, 32 });
	fly.PushBack({ 100, 90, 28, 32 });
	fly.PushBack({ 128, 90, 28, 32 });
	fly.PushBack({ 156, 90, 28, 32 });
	fly.PushBack({ 184, 90, 28, 32 });

	fly.speed = 0.3f;

	animation = &fly;

	hp = 1.0f;

	if (option == 0)
	{
		path.PushBack({ 0.0f, 0.55f }, 600);
		path.PushBack({ 1.75f, 1.75f }, 2000);
	}

	if (option == 1)
	{
		path.PushBack({ 0.0f, 2.0f }, 10000);
	}
	if (option == 2)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 18);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}
	if (option == 3)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 33);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}
	if (option == 4)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 49);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}
	if (option == 5)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 64);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}
	if (option == 6)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 80);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}
	if (option == 7)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 96);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}
	if (option == 8)
	{
		path.PushBack({ 0.0f, 0.55f }, 1500);
		path.PushBack({ -2.0f, 0.55f }, 112);
		path.PushBack({ 0.0f, 0.55f }, 30);
		path.PushBack({ 0.0f, 2.0f }, 1000);
	}

	if (option == 9)
	{
		path.PushBack({ 0.0f, 0.55f }, 10000000);
	}

	

	


	

	collider = App->collision->AddCollider({ 0, 0,  28, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	original_x = x;

	death_type = SMALL_ENEMY;

	flying = true;
}

void Enemy_Redbomb::Move()
{
	/*if (pathoption == 2)
	{
		if(going_right)
		{
			if (wave > 1000.0f)
				going_right = false;
			else
				wave += 0.01f;
		}
	else
	{
		if (wave < -1000.0f)
			going_right = true;
		else
			wave -= 0.01f;
	}

	position.x = original_x + (200.0f * sinf(wave));
	position.y += 2;
	}*/
	
	
		position = original_pos + path.GetCurrentPosition();
	
}

void Enemy_Redbomb::Shoot()
{
	
}
