#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_Balloon.h"
#include "Enemy_Redbomb.h"
#include "Enemy_House1.h"
#include "Enemy_House2.h"
#include "Enemy_Turretcopter.h"
#include "Enemy_CastleMortar.h"
#include "Enemy_Vase.h"
#include "Enemy_GreenRobot.h"
#include "Enemy_RotatingTurret.h"
#include "Enemy_WindowGun.h"
#include "Enemy_2CannonTurret.h"
#include "Enemy_4CannonTurret.h"
#include "Enemy_FlyingGunner.h"
#include "Enemy_TrumpFirst.h"


#define SPAWN_MARGIN 500

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	sprites = App->textures->Load("assets/images/Enemies.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites, enemies[i]);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr &&  enemies[i]->specialanimation) enemies[i]->Special_animation();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr &&  enemies[i]->aditionalanimation) enemies[i]->Extra_animation();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Shoot();

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.y * SCREEN_SIZE > (App->render->camera.y) + SPAWN_MARGIN * SCREEN_SIZE)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int option)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].pathoption = option;
			ret = true;
			break;
		}
	}

	return ret;
}

float ModuleEnemies::ModuleCalc(iPoint target, fPoint you)
{
	float modul;
	fPoint distance;

	distance.x = you.x - target.x;
	distance.y = you.y - target.y;

	modul = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));

	return modul;
}

fPoint ModuleEnemies::NearestEnemy(fPoint your_position, bool player1)
{
	min_module = 10000;
	float modul;
	fPoint distance;
	fPoint speed;
	_enemy = false;
	for (uint i = 0; i < MAX_ENEMIES-1; ++i)
	{
		if (enemies[i] != nullptr)
		if (enemies[i]->hp <= 0) enemies[i]->anim_type = DEAD;

		if (enemies[i] != nullptr && enemies[i]->anim_type != DEAD && enemies[i]->position.y > 0 && enemies[i]->position.y < SCREEN_HEIGHT && enemies[i]->position.x > 0 && enemies[i]->position.x < SCREEN_WIDTH)
		{
			_enemy = true;
			break;
		}
	}
	if (_enemy)
	{
		for (uint i = 0; i < MAX_ENEMIES -1; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->anim_type != DEAD && enemies[i]->position.y > 0 && enemies[i]->position.y < SCREEN_HEIGHT && enemies[i]->position.x > 0 && enemies[i]->position.x < SCREEN_WIDTH)
			{
				module = ModuleCalc(enemies[i]->position, your_position);
				if (module < min_module && enemies[i]->anim_type != DEAD)
				{
					min_module = module;
					j = i;
				}
			}
		}
		

		distance.x = enemies[j]->position.x - your_position.x;
		distance.y = enemies[j]->position.y - your_position.y;

		modul = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));

		distance.x /= modul;
		distance.y /= modul;

		speed.x = distance.x*STAR_SPEED + 0.3f;
		speed.y = distance.y*STAR_SPEED + 0.3f;
	}
	else
	{
		if (player1)
		{
			if (your_position.x < App->player->position.x)
				speed.x = -2;
			else
				speed.x = 2;
		}
		else
		{
			if (your_position.x < App->player2->position.x)
				speed.x = -2;
			else
				speed.x = 2;
		}
		speed.y = -3;
	}
	return speed;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BALLOON:
			enemies[i] = new Enemy_Balloon(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::REDBOMB:
			enemies[i] = new Enemy_Redbomb(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::HOUSE1:
			enemies[i] = new Enemy_House1(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::HOUSE2:
			enemies[i] = new Enemy_House2(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::TURRETCOPTER:
			enemies[i] = new Enemy_Turretcopter(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::CASTLEMORTAR:
			enemies[i] = new Enemy_CastleMortar(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::VASE:
			enemies[i] = new Enemy_Vase(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::ROTATINGTURRET:
			enemies[i] = new Enemy_RotatingTurret(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::WINDOWGUN:
			enemies[i] = new Enemy_WindowGun(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::TWOCANNONTURRET:
			enemies[i] = new Enemy_2CannonTurret(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::FOURCANNONTURRET:
			enemies[i] = new Enemy_4CannonTurret(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::FLYINGGUNNER:
			enemies[i] = new Enemy_FlyingGunner(info.x, info.y, info.pathoption);
			break;
		case ENEMY_TYPES::GREENROBOT:
			enemies[i] = new Enemy_GreenRobot(info.x, info.y, info.pathoption);
			break; 
		case ENEMY_TYPES::TRUMPFIRST:
			enemies[i] = new Enemy_TrumpFirst(info.x, info.y, info.pathoption);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2, enemies[i]);
			if (enemies[i]->hp <= 0.0f)
			{
				enemies[i]->ToDie(enemies[i], c2);
				if (!enemies[i]->dead_anim)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			break;
		}
	}
}