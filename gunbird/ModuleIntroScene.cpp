#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntroScene.h"
#include "ModuleVillageScene.h"
#include "ModuleCastleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScoreScene.h"
#include "ModuleMineScene.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleIntroScene::ModuleIntroScene()
{
	background.h = 320;
	background.w = 224;
	background.x = 0;
	background.y = 0;

	startbutton.PushBack({ 0, 320, 68, 13});
	startbutton.PushBack({ 0, 333, 68, 13 });
	startbutton.speed = 0.03f;
}

ModuleIntroScene::~ModuleIntroScene()
{}

// Load assets
bool ModuleIntroScene::Start()
{
	LOG("Loading intro scene");

	graphics = App->textures->Load("assets/images/Intro Screen.png");
	App->audio->audio = App->audio->Load("assets/bgm/castle.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	return true;
}

// UnLoad assets
bool ModuleIntroScene::CleanUp()
{
	LOG("Unloading intro scene");
	App->textures->Unload(graphics);
	App->scene_intro->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleIntroScene::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky

	App->render->Blit(graphics, 75, 224, &(startbutton.GetCurrentFrame()), 0.01f);

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_DOWN) && !App->fade->fading)
	{
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/ganbaado.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
		App->fade->FadeToBlack(this, App->scene_village, 2.0f);	
	}
	
	return UPDATE_CONTINUE;
}