#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.PushBack({624, 16, 32, 56});
	girl.PushBack({624, 80, 32, 56});
	girl.PushBack({624, 144, 32, 56});
	girl.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");
	
	App->player->Enable();// TODO 1: Enable (and properly disable) the player module

	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// Calculate boat Y position -----------------------------
	if(foreground_pos < -6.0f)
		forward = false;
	else if(foreground_pos > 0.0f)
		forward = true;
	
	if(forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	App->render->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation
	
	App->render->Blit(graphics, 0, 170, &ground);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false)
	{
		App->fade->FadeToBlack(this, App->scene_honda, 2.0f);
		fading = true;
	}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}