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
#include "SDL/include/SDL.h"



ModuleMineScene::ModuleMineScene()
{
	background.h = 3535;
	background.w = 234;
	background.x = 0;
	background.y = 0;

	upperbackground.h = 3535;
	upperbackground.w = 234;
	upperbackground.x = 0;
	upperbackground.y = 0;
}

ModuleMineScene::~ModuleMineScene()
{}

bool ModuleMineScene::Start()
{
	LOG("Loading mine scene");

	
	graphics = App->textures->Load("assets/images/Mine Upper Background.png");
	graphics2 = App->textures->Load("assets/images/Mine Background.png");
	App->audio->audio = App->audio->Load("assets/bgm/Gunbird OST Mine.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	return true;
}

// UnLoad assets
bool ModuleMineScene::CleanUp()
{
	LOG("Unloading mine scene");
	yflag = -3215;
	SDL_DestroyTexture(graphics);
	SDL_DestroyTexture(graphics2);
	App->player->Disable();
	App->particles->Disable();
	App->collision->Disable();
	return true;
}

// Update: draw background
update_status ModuleMineScene::Update()
{
	yflag += 0.40f;
	

	// Draw everything --------------------------------------

	App->render->Blit(graphics2, 0, 0.75*yflag, &background, 10.0f); // sea and sky
	App->render->Blit(graphics, 0, yflag, &upperbackground, 10.0f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false || yflag > -320)
	{
		
		App->fade->FadeToBlack(this, App->scene_score, 2.0f);
			
	}

	return UPDATE_CONTINUE;
}
