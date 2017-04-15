#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
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

	Turretcopter_animation.PushBack({ 0, 0, 35, 35 });
	Turretcopter_animation.PushBack({ 35, 0, 35, 35 });
	Turretcopter_animation.PushBack({ 70, 0, 35, 35 });
	Turretcopter_animation.PushBack({ 0, 35, 35, 35 });
	Turretcopter_animation.PushBack({ 35, 35, 35, 35 });
	Turretcopter_animation.PushBack({ 70, 35, 35, 35 });
	Turretcopter_animation.loop = true;
	Turretcopter_animation.speed = 0.2f;
}

ModuleCastleScene::~ModuleCastleScene()
{}

bool ModuleCastleScene::Start()
{
	LOG("Loading castle scene");
	graphics2 = App->textures->Load("assets/images/Castle Upper Background.png");
	graphics = App->textures->Load("assets/images/Castle Background.png");
	graphics3 = App->textures->Load("assets/images/Castle Structures.png");
	Turretcopter_texture = App->textures->Load("assets/images/enemy_turretcopter.png");
	App->audio->audio = App->audio->Load("assets/bgm/castle.ogg");
	Turretcopter = App->collision->AddCollider({ 100, 50, 35, 35 }, COLLIDER_ENEMY, this);
	Mix_PlayMusic(App->audio->audio, -1);
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
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
	SDL_DestroyTexture(Turretcopter_texture);
	App->player->Disable();
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
	App->render->Blit(Turretcopter_texture, 100, 50, &(Turretcopter_animation.GetCurrentFrame()));
	if (yflag >= -1503.00 || houseflag == true)
	{
		houseflag = true;
		App->render->Blit(graphics3, 152, house1counter, &castlehouse1, 10.0f);
		App->render->Blit(graphics3, 181, house1counter - 10, &(flag.GetCurrentFrame()));
		house1counter += 0.55f;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || yflag > -320)
	{
		App->fade->FadeToBlack(this, App->scene_mine, 2.0f);
	}

	return UPDATE_CONTINUE;
}

void ModuleCastleScene::OnCollision(Collider* c1, Collider* c2)
{

	if (c2->type == COLLIDER_PLAYER_SHOT && c1->type == COLLIDER_ENEMY)
		c1->to_delete = true;
	Turretcopter_texture = nullptr;

}
