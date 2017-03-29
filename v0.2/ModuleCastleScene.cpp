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



ModuleCastleScene::ModuleCastleScene()
{
	background.h = 2108;
	background.w = 234;
	background.x = 0;
	background.y = 0;
}

ModuleCastleScene::~ModuleCastleScene()
{}

bool ModuleCastleScene::Start()
{
	LOG("Loading castle scene");

	graphics = App->textures->Load("assets/images/Castle Background.png");
	App->audio->audio = App->audio->Load("assets/bgm/Gunbird OST Castle.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	return true;
}

// UnLoad assets
bool ModuleCastleScene::CleanUp()
{
	LOG("Unloading castle scene");
	yflag = -1788;
	SDL_DestroyTexture(graphics);
	return true;
}

// Update: draw background
update_status ModuleCastleScene::Update()
{
	yflag += 1;


	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, yflag, &background, 0.75f); // sea and sky

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false || yflag > -320)
	{

		App->fade->FadeToBlack(this, App->scene_mine, 2.0f);
		App->fade->fading = true;

	}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}
