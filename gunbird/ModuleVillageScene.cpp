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
	ycounter = 0;
	
	graphics = App->textures->Load("assets/images/backgrounds/Village lower background.png");
	graphics2 = App->textures->Load("assets/images/backgrounds/Village upper background.png");
	graphics3 = App->textures->Load("assets/images/backgrounds/Village lower train background.png");
	graphics4 = App->textures->Load("assets/images/backgrounds/Village upper train background.png");


	App->collision->AddCollider(npi, COLLIDER_WALL);

	

	return true;
}

// UnLoad assets
bool ModuleVillageScene::CleanUp()
{
	LOG("Unloading Village scene");

	
	App->player->Disable();
	App->player2->Disable();
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
	yflag += 0.4;

	App->render->Blit(graphics, -320, yflag, &background1, 10.0f);
	App->render->Blit(graphics2, -320, yflag, &background1, 10.0f);
	

	return UPDATE_CONTINUE;
}

void ModuleVillageScene::OnCollision(Collider* c1, Collider* c2)
{

}
