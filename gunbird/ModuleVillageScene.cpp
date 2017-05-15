#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntroScene.h"
#include "ModuleVillageScene.h"
#include "ModuleCastleScene.h"
#include "ModuleMineScene.h"
#include "ModuleScoreScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL.h"



ModuleVillageScene::ModuleVillageScene()
{

	background1.h = 5632;
	background1.w = 544;
	background1.x= 0;
	background1.y = 0;

	background2.h = 4000;
	background2.w = 544;
	background2.x = 0;
	background2.y = 0;


	npi.h = 5;
	npi.w = 1000;
	npi.x = 0;
	npi.y = -10;



}

ModuleVillageScene::~ModuleVillageScene()
{}

bool ModuleVillageScene::Start()
{
	LOG("Loading village scene");
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	yflag = -5312;
	xflag = -320;
	ycounter = 0;
	cinematic = false;
	timerup = false;

	graphics = App->textures->Load("assets/images/backgrounds/Village lower background.png");
	graphics2 = App->textures->Load("assets/images/backgrounds/Village upper background.png");
	graphics3 = App->textures->Load("assets/images/backgrounds/Village lower train background.png");
	graphics4 = App->textures->Load("assets/images/backgrounds/Village upper train background.png");


	App->collision->AddCollider(npi, COLLIDER_WALL);

	//---ENEMIES---

	//--Adding Balloons--
	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 50, 20, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 150, -50, 0);

	//--Adding Rotating Turrets--
	App->enemies->AddEnemy(ENEMY_TYPES::ROTATINGTURRET, 20, -70, 0);

	//--Adding Window Guns--
	App->enemies->AddEnemy(ENEMY_TYPES::WINDOWGUN, 26, -122, 0);

	return true;
}

bool ModuleVillageScene::CleanUp()
{
	LOG("Unloading castle scene");
		
	App->enemies->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);
	App->textures->Unload(graphics4);

	return true;
}

// Update: draw background
update_status ModuleVillageScene::Update()
{

	if(yflag <= -4350)
	{
		yflag += 0.4;
	}
	if (yflag >= -4350 && yflag <= -3904 && xflag < -129)
	{
		xflag += 0.66;
		yflag += 0.4;
	}
	if (yflag >= -3904 && !cinematic)
	{
		if (!timerup)
		{
			timer = SDL_GetTicks() + 3500;
			timerup = true;
		}
		if (SDL_GetTicks() > timer)
		{
			cinematic = true;
		}
	}
	
	if (xflag < -60 && cinematic)
	{
		xflag += 0.66;
		yflag += 0.4;
	}

	



	App->render->Blit(graphics, xflag, yflag, &background1, 10.0f);
	App->render->Blit(graphics2,xflag, yflag, &background1, 10.0f);
	

	return UPDATE_CONTINUE;
}

void ModuleVillageScene::OnCollision(Collider* c1, Collider* c2)
{

}
