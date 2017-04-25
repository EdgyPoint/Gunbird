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
	

	background.h = 1677;
	background.w = 224;
	background.x = 0;
	background.y = 0;

	npi.h = 5;
	npi.w = 1000;
	npi.x = 0;
	npi.y = -10;

	knightleft.PushBack({ 0, 25, 15, 25 });
	knightleft.PushBack({ 15, 25, 15, 25 });
	knightleft.PushBack({ 30, 25, 15, 25 });
	knightleft.PushBack({ 45, 25, 15, 25 });
	knightleft.speed = 0.03f;

	knightup.PushBack({ 0, 0, 15, 25 });
	knightup.PushBack({ 15, 0, 15, 25 });
	knightup.PushBack({ 30, 0, 15, 25 });
	knightup.PushBack({ 45, 0, 15, 25 });
	knightup.speed = 0.03f;

	river1.PushBack({ 0,0,224, 102 });
	river1.PushBack({ 0,102,224,102 });
	river1.PushBack({ 0,204,224,102 });
	river1.PushBack({ 0,306, 224, 102 });
	river1.speed = 0.07f;
	

	river2.PushBack({ 224,0,224,92 });
	river2.PushBack({ 224,92,224,92 });
	river2.PushBack({ 224,184,224,92 });
	river2.PushBack({ 0, 306, 224, 92 }); // its a blank space to see the backround. Ask Lorién.
	river2.speed = 0.07f;

	bridge_anim.PushBack({ 0, 0, 125, 165 });
	bridge_anim.PushBack({ 125, 0, 125, 165 });
	bridge_anim.PushBack({ 250, 0, 125, 165 });
	bridge_anim.PushBack({ 375, 0, 125, 165 });
	bridge_anim.PushBack({ 0, 165, 125, 165 });
	bridge_anim.PushBack({ 125, 165, 125, 165 });
	bridge_anim.PushBack({ 250, 165, 125, 165 });
	bridge_anim.PushBack({ 375, 165, 125, 165 });
	bridge_anim.PushBack({ 0, 330, 125, 165 });
	bridge_anim.loop = false;
	bridge_anim.speed = 0.1f;

	dead_mortar.PushBack({ 32, 10, 32, 32 });
	dead_mortar.PushBack({ 66, 10, 32, 32 });
	dead_mortar.PushBack({ 32, 44, 32, 32 });
	dead_mortar.PushBack({ 66, 44, 32, 32 });
	dead_mortar.PushBack({ 49, 81, 32, 32 });
	dead_mortar.PushBack({ 66, 44, 32, 32 });
	dead_mortar.PushBack({ 32, 44, 32, 32 });
	dead_mortar.PushBack({ 66, 10, 32, 32 });
	dead_mortar.loop = true;
	dead_mortar.speed = 0.1f;

	thebossstanding.PushBack({ 170, 166, 14, 24 });
	thebossstanding.PushBack({ 189, 166, 14, 24 });
	thebossstanding.loop = true;
	thebossstanding.speed = 0.125f;

	/*thebossup.PushBack({});
	thebossup.speed = 0.25f;*/

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

	yflag = -1357;
	knight1 = { 0.0f,0.0f };
	knight2 = { 0.0f, 0.0f };
	bridge_speed_y = -83;
	mortar_speed_y = 0;


	App->collision->AddCollider(npi, COLLIDER_WALL);

	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 97,-170, 0);
	
	//spawn houses
	App->enemies->AddEnemy(ENEMY_TYPES::HOUSE1, 145, -305, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::HOUSE2, 74, -563, 0);
	
	//spawn Vases
	App->enemies->AddEnemy(ENEMY_TYPES::VASE, 8, -671, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::VASE, 8, -879, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::VASE, 184, -879, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::VASE, 184, -671, 0);
	//spawn redbombs
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -20, -315, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -48, -347, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -76, -375, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, -106, -411, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 5);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 7);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 225, -710, 8);

	//1st final wave
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 77, -1190, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 125, -1190, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 51, -1280, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 147, -1280, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 3, -1280, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 195, -1280, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 51, -1366, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 147, -1366, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 3, -1366, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 195, -1366, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 77, -1456, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 125, -1456, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 112, -1473, 10);

	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 77, -1746, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 125, -1746, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 51, -1836, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 147, -1836, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 3, -1836, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 195, -1836, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 51, -1932, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 147, -1932, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 3, -1922, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 195, -1922, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 77, -2012, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 125, -2012, 9);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBOMB, 112, -2029, 10);
	
	//Spawn Castle Mortar
	App->enemies->AddEnemy(ENEMY_TYPES::CASTLEMORTAR, 160, -127, 0);
	
	graphics2 = App->textures->Load("assets/images/Castle Upper Background better.png");
	graphics = App->textures->Load("assets/images/Castle Background better.png");
	trump = App->textures->Load("assets/images/thetrump.png");
	knight = App->textures->Load("assets/images/knight.png");
	river = App->textures->Load("assets/images/river.png");
	bridge = App->textures->Load("assets/images/castle_bridge.png");
	mortar = App->textures->Load("assets/images/destroyed mortar.png");


	App->audio->audio = App->audio->Load("assets/bgm/castle.ogg");
	Mix_PlayMusic(App->audio->audio, -1);

	return true;
}

// UnLoad assets
bool ModuleCastleScene::CleanUp()
{
	LOG("Unloading castle scene");

	SDL_DestroyTexture(graphics);
	SDL_DestroyTexture(graphics2);
	SDL_DestroyTexture(knight);
	SDL_DestroyTexture(bridge);
	SDL_DestroyTexture(mortar);
	SDL_DestroyTexture(river);
	SDL_DestroyTexture(trump);
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	App->particles->Disable();
	App->collision->Disable();
	
	
	return true;
}

// Update: draw background
update_status ModuleCastleScene::Update()
{
	
	//App->render->camera.y += 0.55f;
	
		yflag += 0.55f;
	 
		
	

	// Draw everything --------------------------------------



	// --- Draw knights
	knight1.x -= 0.30f;
	knight1.y += 0.55f;
	knight2.x -= 0.30f;
	knight2.y += 0.55f;
	App->render->Blit(graphics, 0, yflag, &background, 10.0f);
	App->render->Blit(river, 0, knight1.y - 378, &(river2.GetCurrentFrame()), 0.07f, false);
	App->render->Blit(river, 0, knight1.y - 1, &(river1.GetCurrentFrame()), 0.07f, false);
	//First two moving left
	App->render->Blit(knight, 57 + knight1.x, 170 + knight1.y, &(knightleft.GetCurrentFrame()), 0.75f);
	App->render->Blit(knight, 67 + knight1.x, 180 + knight1.y, &(knightleft.GetCurrentFrame()), 0.75f);
	//Two more moving up
	if (yflag < -1200)
	{
		App->render->Blit(knight, 94, 60, &(knightup.GetCurrentFrame()), 0.75f);
	}

	if (yflag < -1200)
	{
		App->render->Blit(knight, 76, 70, &(knightup.GetCurrentFrame()), 0.75f);
	}

	if (yflag < -1620)
	{
		knight2.x = 0;
	}



	// --- Draw background top layer
	App->render->Blit(graphics2, 0, yflag, &background, 10.0f);

	//Draw knights on fortress

	App->render->Blit(knight, 97 + knight2.x, -130 + knight2.y, &(knightleft.GetCurrentFrame()), 0.75f);
	App->render->Blit(knight, 107 + knight2.x, -130 + knight2.y, &(knightleft.GetCurrentFrame()), 0.75f);
	App->render->Blit(knight, 137 + knight2.x, -130 + knight2.y, &(knightleft.GetCurrentFrame()), 0.75f);

	//Draw dead mortar
	if (yflag > -1230)
	{
		mortar_speed_y += 0.55f;
		App->render->Blit(mortar, 160, mortar_speed_y, &(dead_mortar.GetCurrentFrame()), 1.0f);
	}


	if (yflag > -964)
	{
		bridge_speed_y += 0.55f;
		App->render->Blit(bridge, 63, bridge_speed_y, &(bridge_anim.GetCurrentFrame()), 0.75f);
	}

	

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN || yflag >= -10)
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
