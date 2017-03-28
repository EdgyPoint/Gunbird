#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScoreScene.h"
#include "ModuleIntro.h"
//#include "ModuleIntro"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScoreScene::ModuleScoreScene()
{
	background.h = 320;
	background.w = 224;
	background.x = 0;
	background.y = 0;
}

ModuleScoreScene::~ModuleScoreScene()
{}

// Load assets
bool ModuleScoreScene::Start()
{
	LOG("Loading score scene");

	graphics = App->textures->Load("assets/images/Score Screen.png");

	return true;
}

// UnLoad assets
bool ModuleScoreScene::CleanUp()
{
	LOG("Unloading score scene");


	return true;
}

// Update: draw background
update_status ModuleScoreScene::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false)
	{
		App->fade->FadeToBlack(this, App->intro, 2.0f);
		App->fade->fading = true;
	}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}