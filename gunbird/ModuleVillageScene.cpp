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
#include "ModuleVillageScene.h"
#include "ModuleCastleScene.h"
#include "ModuleMineScene.h"
#include "ModuleScoreScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL.h"



ModuleVillageScene::ModuleVillageScene()
{

	background1.h = 5632;
	background1.w = 544;
	background1.x= 0;
	background1.y = 0;

	background2.h = 4000;
	background2.w = 544;
	background2.x = 0;
	background2.y = 0;


	npi.h = 5;
	npi.w = 1000;
	npi.x = 0;
	npi.y = -10;



}

ModuleVillageScene::~ModuleVillageScene()
{}

bool ModuleVillageScene::Start()
{
	LOG("Loading village scene");
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	yflag = -5312;
	xflag = -320;
	ycounter = 0;
	speed = 0.4;
	cinematic = false;
	timerup = false;
	on_rails = false;
	going_left = true;
	scroll_timer = false;
	scrolling = false;

	graphics = App->textures->Load("assets/images/backgrounds/Village lower background.png");
	graphics2 = App->textures->Load("assets/images/backgrounds/Village upper background.png");
	graphics3 = App->textures->Load("assets/images/backgrounds/Village train background.png");
	graphics4 = App->textures->Load("assets/images/backgrounds/Village train background.png");


	App->collision->AddCollider(npi, COLLIDER_WALL);

	//---ENEMIES---

	//--Adding Balloons--
	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 50, 20, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, 150, -50, 0);

	//--Adding Rotating Turrets--
	App->enemies->AddEnemy(ENEMY_TYPES::ROTATINGTURRET, 20, -70, 0);

	//--Adding Window Guns--
	App->enemies->AddEnemy(ENEMY_TYPES::WINDOWGUN, 26, -122, 0);

	//--Adding Rooftop Turrets--
	App->enemies->AddEnemy(ENEMY_TYPES::TWOCANNONTURRET, 26, -525, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::TWOCANNONTURRET, 26, -585, 0);

	App->enemies->AddEnemy(ENEMY_TYPES::FOURCANNONTURRET, 135, -520, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::FOURCANNONTURRET, 135, -570, 0);

	return true;
}

bool ModuleVillageScene::CleanUp()
{
	LOG("Unloading castle scene");
	
	App->enemies->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->player->Disable();
	App->player2->Disable();

	
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);
	App->textures->Unload(graphics4);

	return true;
}

// Update: draw background
update_status ModuleVillageScene::Update()
{
	if (!on_rails)
	{
		if (yflag <= -4350)
		{
			yflag += speed;
		}
		if (yflag >= -4350 && xflag < -129)
		{
			xflag += 0.66;
			yflag +=speed;
		}
		if (yflag >= -4234 && !cinematic)
		{
			if (!timerup)
			{
				timer = SDL_GetTicks() + 3500;
				timerup = true;
			}
			if (SDL_GetTicks() > timer)
			{
				cinematic = true;
			}
		}

		if (xflag < -60 && cinematic)
		{
			xflag += 0.66;
			yflag += speed;
			timerup = false;
		}
		if (xflag >= -60 && !timerup && !scrolling)
		{
			timer2 = SDL_GetTicks() + 2000;
			timerup = true;
		}
		if (SDL_GetTicks() > timer2 && xflag >= -60 && speed < 10.0 && !scrolling)
		{
			speed *= 1.02;
			yflag += speed;
		}
		if (yflag >= 320.0f)
		{
			on_rails = true;
			yflag = -3680;
		}

		if (speed >= 10.0)
		{
			Side_scrolling();
			scrolling == true;
		}

		

	App->render->Blit(graphics, xflag, yflag, &background1, 10.0f);
	App->render->Blit(graphics2, xflag, yflag, &background1, 10.0f);
	App->render->Blit(graphics3, xflag, yflag-4000, &background2, 10.0f);

	}

	if (on_rails)
	{

		Side_scrolling();
		if(yflag >= 3680)
		{
			yflag = -3680;
		}
		App->render->Blit(graphics3, xflag, yflag - 4000, &background2, 10.0f);
		App->render->Blit(graphics4, xflag, yflag, &background2, 10.0f);
	}
	
   	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
	{
  		speed = 9.0;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
	{
		speed = 0.4;
	}

	



	
	
	if ((App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN ) && !App->fade->fading)
	{
		App->fade->FadeToBlack(this, App->scene_score, 2.0f);

	}
	if ((App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN ) && !App->fade->fading)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.0f);
	}

	return UPDATE_CONTINUE;
}

void ModuleVillageScene::Side_scrolling()
{
	if (going_left && !scroll_timer)
	{
		yflag += speed;
		xflag += 0.66;
		if (xflag >= 0)
		{
			timer = SDL_GetTicks() + 1000;
			scroll_timer = true;
		}
	}

	else if (scroll_timer)
	{
		yflag += speed;
		if (SDL_GetTicks() >= timer)
		{
			scroll_timer = false;
			if (going_left)
			{
				going_left = false;
			}
			else
			{
				going_left = true;
			}
		}
	}

	if (!going_left && !scroll_timer)
	{
		yflag += speed;
		xflag -= 0.66;
		if (xflag <= -60)
		{
			timer = SDL_GetTicks() + 1000;
			scroll_timer = true;
		}
	}
}

void ModuleVillageScene::OnCollision(Collider* c1, Collider* c2)
{

}
