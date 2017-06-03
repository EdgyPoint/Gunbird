#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_Balloon.h"
#include "Enemy_Redbomb.h"
#include "Enemy_Turretcopter.h"
#include "Enemy_CastleMortar.h"
#include "Enemy_RotatingTurret.h"
#include "Enemy_WindowGun.h"
#include "Enemy_GreenRobot.h"
#include "Enemy_2CannonTurret.h"
#include "Enemy_4CannonTurret.h"

#define MAX_ENEMIES 100


enum ENEMY_TYPES
{
	NO_TYPE,
	BALLOON,
	REDBOMB,
	HOUSE1,
	HOUSE2,
	TURRETCOPTER,
	CASTLEMORTAR,
	VASE,
	GREENROBOT,
	ROTATINGTURRET,
	WINDOWGUN,
	TWOCANNONTURRET,
	FOURCANNONTURRET,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, pathoption;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int pathoption);

private:

	void SpawnEnemy(const EnemyInfo& info);

public:


	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__
