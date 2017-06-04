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

	arriving_left1.PushBack({ 866, 328, 32, 33 });
	arriving_left1.PushBack({ 866, 382, 32, 33 });
	arriving_left1.PushBack({ 866, 433, 32, 33 });
	arriving_left1.PushBack({ 777, 477, 32, 33 });
	arriving_left1.PushBack({ 741, 477, 32, 33 });
	arriving_left1.PushBack({ 777, 328, 32, 33 });
	arriving_left1.PushBack({ 777, 433, 32, 33 });
	arriving_left1.PushBack({ 741, 433, 32, 33 });
	arriving_left1.loop = false;
	arriving_left1.speed = 1.0f;

	
	arriving_left2.PushBack({ 741, 382, 32, 33 });
	arriving_left2.PushBack({ 814, 382, 32, 33 });
	arriving_left2.PushBack({ 777, 382, 32, 33 });
	arriving_left2.loop = true;
	arriving_left2.speed = 0.4f;
	

	animation = &arriving_left1;

	hp = 1.0f;

	if (option == 0)
	{
		path.PushBack({ 0.0f, 0.4f }, 190);
		path.PushBack({ 0.6f, 0.4f }, 20000);
	}

	collider = App->collision->AddCollider({ 0, 0,  32, 33 }, COLLIDER_TYPE::COLLIDER_ENEMY_F, (Module*)App->enemies);

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

	if (status == OPENING && animation->Finished() == true) { status = NORMAL; }
	if (status == NORMAL) {	animation = &arriving_left2; }

}

