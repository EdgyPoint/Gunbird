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
#include "ModuleCastleScene.h"
#include "ModuleMineScene.h"
#include "ModuleScoreScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL.h"



ModuleCastleScene::ModuleCastleScene()
{
	background.h = 2108;
	background.w = 234;
	background.x = 0;
	background.y = 0;

	backgroundup.h = 1539;
	backgroundup.w = 234;
	backgroundup.x = 0;
	backgroundup.y = 0;

	castlehouse1.h = 86;
	castlehouse1.w = 64;
	castlehouse1.x = 0;
	castlehouse1.y = 0;

	npi.h = 1;
	npi.w = 1000;
	npi.x = 0;
	npi.y = 0;

	flag.PushBack({ 13, 94, 64, 21 });
	flag.PushBack({ 13, 120, 66, 21 });
	flag.PushBack({ 13, 145, 66, 20 });
	flag.PushBack({ 13, 170, 65, 21 });
	flag.PushBack({ 13, 195, 64, 21 });
	flag.PushBack({ 88, 97, 66, 20 });
	flag.PushBack({ 89, 126, 65, 21 });
	flag.PushBack({ 89, 153, 65, 21 });
	flag.loop = true;
	flag.speed = 0.2f;

}

ModuleCastleScene::~ModuleCastleScene()
{}

bool ModuleCastleScene::Start()
{
	LOG("Loading castle scene");
	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	App->collision->AddCollider(npi, COLLIDER_WALL);

	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 100, App->render->camera.y - 100, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::HOUSE1, 153, -365, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::HOUSE2, 80, -624, 0);
	/*App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -10, -380, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -38, -412, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -66, -440, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -94, -476, 2);*/
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -10, -580, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -38, -612, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -66, -640, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -94, -676, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -10, 0, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -38, 0, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, 100, -470, 0);
	/*App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -25, -410, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -10, -400, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -15, -440, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -25, -440, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -10, -430, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -10, -460, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -15, -470, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -20, -470, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -10, -500, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -15, -510, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, -20, -510, 0);*/
	graphics2 = App->textures->Load("assets/images/Castle Upper Background.png");
	graphics = App->textures->Load("assets/images/Castle Background.png");
	//graphics3 = App->textures->Load("assets/images/Castle Structures.png");
	App->audio->audio = App->audio->Load("assets/bgm/castle.ogg");
	Mix_PlayMusic(App->audio->audio, -1);

	return true;
}

// UnLoad assets
bool ModuleCastleScene::CleanUp()
{
	LOG("Unloading castle scene");
	yflag = -1788;
	yflag2 = -1279;
	SDL_DestroyTexture(graphics);
	SDL_DestroyTexture(graphics2);
	SDL_DestroyTexture(graphics3);
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	App->particles->Disable();
	App->collision->Disable();
	houseflag = false;
	return true;
}

// Update: draw background
update_status ModuleCastleScene::Update()
{
	

	yflag += 0.55f;
	yflag2 += 0.55f;

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, yflag, &background, 10.0f); // sea and sky
	App->render->Blit(graphics2, 0, yflag2, &backgroundup, 10.0f);
	/*if (yflag >= -1503.00 || houseflag == true)
	{
		houseflag = true;
		App->render->Blit(graphics3, 152, house1counter, &castlehouse1, 10.0f);
		App->render->Blit(graphics3, 181, house1counter - 10, &(flag.GetCurrentFrame()));
		house1counter += 0.55f;
	}*/
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || yflag > -320)
	{
		App->fade->FadeToBlack(this, App->scene_mine, 2.0f);
	}

	return UPDATE_CONTINUE;
}

void ModuleCastleScene::OnCollision(Collider* c1, Collider* c2)
{

}
