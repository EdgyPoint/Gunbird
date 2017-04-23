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

	npi.h = 5;
	npi.w = 1000;
	npi.x = 0;
	npi.y = -10;

	knightleft.PushBack({ 0, 25, 15, 25 });
	knightleft.PushBack({ 15, 25, 15, 25 });
	knightleft.PushBack({ 30, 25, 15, 25 });
	knightleft.PushBack({ 45, 25, 15, 25 });
	knightleft.speed = 0.1f;

	knightup.PushBack({ 0, 0, 15, 25 });
	knightup.PushBack({ 15, 0, 15, 25 });
	knightup.PushBack({ 30, 0, 15, 25 });
	knightup.PushBack({ 45, 0, 15, 25 });
	knightup.speed = 0.1f;
}

ModuleCastleScene::~ModuleCastleScene()
{}

bool ModuleCastleScene::Start()
{
	LOG("Loading castle scene");
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	App->collision->AddCollider(npi, COLLIDER_WALL);

	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 100, App->render->camera.y - 100, 0);
	
	//spawn houses
	App->enemies->AddEnemy(ENEMY_TYPES::HOUSE1, 153, -365, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::HOUSE2, 80, -624, 0);
	
	//spawn redbombs
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -10, -375, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -38, -407, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -66, -435, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -94, -471, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 5);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 7);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 230, -820, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 100, -1200, 9);

	/*App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -10, -580, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -38, -612, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -66, -640, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -94, -676, 2);*/
	//App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -10, 0, 2);
	//App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -38, 0, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TURRETCOPTER, 100, -470, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CASTLEMORTAR, 168, -187, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CASTLEMORTAR, 100, 20, 0);
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
	knight = App->textures->Load("assets/images/knight.png");
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

	App->render->Blit(graphics, 0, yflag, &background, 10.0f);


	// --- Draw knights
	knight_1_x_pos -= 0.30f;
	knight_1_y_pos += 0.55f;
	knight_2_x_pos -= 0.30f;
	knight_2_y_pos += 0.55f;
	//First two moving left
	App->render->Blit(knight, 65 + knight_1_x_pos, 110 + knight_1_y_pos, &(knightleft.GetCurrentFrame()), 0.75f);
	App->render->Blit(knight, 75 + knight_1_x_pos, 120 + knight_1_y_pos, &(knightleft.GetCurrentFrame()), 0.75f);
	//Two more moving up
	if (yflag < -1645)
	{
		App->render->Blit(knight, 102, 0, &(knightup.GetCurrentFrame()), 0.75f);
	}

	if (yflag < -1635)
	{
		App->render->Blit(knight, 84, 10, &(knightup.GetCurrentFrame()), 0.75f);
	}

	if (yflag < -1680)
	{
		knight_2_x_pos = 0;
	}


	// --- Draw background top layer
	App->render->Blit(graphics2, 0, yflag2, &backgroundup, 10.0f);

	//Draw knights on fortress
	App->render->Blit(knight, 65 + knight_2_x_pos, -190 + knight_2_y_pos, &(knightleft.GetCurrentFrame()), 0.75f);
	App->render->Blit(knight, 85 + knight_2_x_pos, -190 + knight_2_y_pos, &(knightleft.GetCurrentFrame()), 0.75f);
	App->render->Blit(knight, 105 + knight_2_x_pos, -190 + knight_2_y_pos, &(knightleft.GetCurrentFrame()), 0.75f);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || yflag > -320)
	{
		App->fade->FadeToBlack(this, App->scene_mine, 2.0f);
	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->scene_score, 2.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.0f);
	}

	return UPDATE_CONTINUE;
}

void ModuleCastleScene::OnCollision(Collider* c1, Collider* c2)
{

}
