#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
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
}

ModuleMineScene::~ModuleMineScene()
{}

bool ModuleMineScene::Start()
{
	LOG("Loading mine scene");

	graphics = App->textures->Load("assets/images/Mine Background.png");
	App->audio->audio = App->audio->Load("assets/bgm/Gunbird OST Mine.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	return true;
}

// UnLoad assets
bool ModuleMineScene::CleanUp()
{
	LOG("Unloading mine scene");
	yflag = -3215;
	SDL_DestroyTexture(graphics);
	return true;
}

// Update: draw background
update_status ModuleMineScene::Update()
{
	yflag += 5;
	

	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, yflag, &background, 0.75f); // sea and sky

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false || yflag > -320)
	{
		
		App->fade->FadeToBlack(this, App->scene_score, 2.0f);
		App->fade->fading = true;
		
	}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}
