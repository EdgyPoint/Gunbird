#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_House1.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"




Enemy_House1::Enemy_House1(int x, int y, int option) : Enemy(x, y, option)
{
	aditionalanimation = true; 

	fly.PushBack({ 220, 58, 64, 86 });

	fly2.PushBack({ 216, 230, 64, 86 });

	fly3.PushBack({ 220,58,64,86 });
	fly3.PushBack({ 280, 230, 64, 86 });
	fly3.speed = 0.2f;
	
	flag.PushBack({ 354, 94, 64, 21 });
	flag.PushBack({ 354, 120, 66, 21 });
	flag.PushBack({ 354, 145, 66, 20 });
	flag.PushBack({ 354, 145, 66, 20 });
	flag.PushBack({ 354, 170, 65, 21 });
	flag.PushBack({ 354, 195, 64, 21 });
	flag.PushBack({ 429, 97, 66, 20 });
	flag.PushBack({ 430, 126, 65, 21 });
	flag.PushBack({ 430, 153, 65, 21 });
	flag.loop = true;
	flag.speed = 0.2f;

	flag2.PushBack({ 495, 94, 64, 21 });
	flag2.PushBack({ 495, 120, 66, 21 });
	flag2.PushBack({ 495, 145, 66, 20 });
	flag2.PushBack({ 495, 170, 65, 21 });
	flag2.PushBack({ 495, 195, 64, 21 });
	flag2.PushBack({ 570, 97, 66, 20 });
	flag2.PushBack({ 570, 126, 65, 21 });
	flag2.PushBack({ 570, 153, 65, 21 });
	flag2.loop = true;
	flag2.speed = 0.2f;

	flag3.PushBack({ 354, 94, 64, 21 });
	flag3.PushBack({646, 120, 66, 21 });
	flag3.PushBack({ 354, 145, 66, 20 });
	flag3.PushBack({ 646, 170, 65, 21 });
	flag3.PushBack({ 354, 195, 64, 21 });
	flag3.PushBack({712, 97, 66, 20 });
	flag3.PushBack({ 430, 126, 65, 21 });
	flag3.PushBack({712, 153, 65, 21 });
	flag3.loop = true;
	flag3.speed = 0.2f;


	collider = App->collision->AddCollider({ 0, 0, 64, 86 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &fly;

	aditional_animation = &flag;


	path.PushBack({ 0.0f, 0.55f }, 10000);
	original_pos.x = x;
	original_pos.y = y;

	hp = 10.0f;
	damaged_hp = 2.0f;
	death_type = MEDIUM_ENEMY;
	enemy_drops = true;
	flying = false;
	killscore = 3000;
}

void Enemy_House1::Move()
{
	position = original_pos + path.GetCurrentPosition();
	
	if (status == NORMAL)
	{
		animation = &fly;
		aditional_animation = &flag;
	}
	if (status == HIT)
	{
		animation = &fly2;
		aditional_animation = &flag2;
	}

	if (status == DAMAGED)
	{
		animation = &fly3;
		aditional_animation = &flag3;
	}
}
void Enemy_House1::Extra_animation()
{
	if (status == NORMAL)
	{
		App->render->Blit(App->enemies->sprites, position.x + 29, position.y - 15, &flag.GetCurrentFrame());
		flag2.GetCurrentFrame();
		flag3.GetCurrentFrame();
	}
	if (status == HIT)
	{
		App->render->Blit(App->enemies->sprites, position.x + 29, position.y - 15, &flag2.GetCurrentFrame());
		flag.GetCurrentFrame();
		flag3.GetCurrentFrame();
	}

	if (status == DAMAGED)
	{
		App->render->Blit(App->enemies->sprites, position.x + 29, position.y - 15, &flag3.GetCurrentFrame());
		flag.GetCurrentFrame();
		flag2.GetCurrentFrame();
	}
	
}
