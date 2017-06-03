#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntroScene.h"
#include "ModuleCastleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScoreScene.h"
#include "ModuleMineScene.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScoreScene::ModuleScoreScene()
{
	background.h = 320;
	background.w = 234;
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
	App->audio->audio = App->audio->Load("assets/bgm/Gunbird OST Character Selection.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	return true;
}

// UnLoad assets
bool ModuleScoreScene::CleanUp()
{
	LOG("Unloading score scene");
	App->player->score = 0;
	App->player2->score = 0;
	App->textures->Unload(graphics);
	/*App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();*/

	return true;
}

// Update: draw background
update_status ModuleScoreScene::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky


	App->render->Blit(App->player->ui, 90, 55, &App->player->p1display, 0, true);
	App->render->Blit(App->player->ui, 90, 80, &App->player2->p2display, 0, true); // if not gives the invalid texture LOG. (player2 uses the player 1 ui texture)

	App->fonts->BlitText(120, 79, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 103, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 127, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 151, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 175, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 199, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 223, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 247, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 271, App->player->font_scorescene, "      0");
	App->fonts->BlitText(120, 55, App->player->font_scorescene, App->player->text_score);
	App->fonts->BlitText(120, 79, App->player->font_scorescene, App->player2->text_score2);

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->controller[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_DOWN) && !App->fade->fading)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.0f);
	}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}