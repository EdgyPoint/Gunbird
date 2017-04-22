#include<cstring>
#include<stdlib.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntroScene.h"
#include "ModuleCastleScene.h"
#include "ModuleScoreScene.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;
	
	// idle animation (arcade sprite sheet)
	idle.PushBack({0, 64, 32, 32});
	idle.PushBack({32, 64, 32, 32});
	idle.PushBack({64, 64, 32, 32});
	idle.PushBack({96, 64, 32, 32});
	idle.loop = true;
	idle.speed = 0.1f;

	// left animation (arcade sprite sheet)
	tleft.PushBack({ 0, 32, 32, 32 });
	tleft.PushBack({ 32, 32, 32, 32 });
	tleft.PushBack({ 64, 32, 32, 32 });
	tleft.PushBack({ 96, 32, 32, 32 });
	tleft.speed = 0.1f;

	left.PushBack({ 0, 0, 32, 32 });
	left.PushBack({ 32, 0, 32, 32 });
	left.PushBack({ 64, 0, 32, 32 });
	left.PushBack({ 96, 0, 32, 32 });
	left.loop = true;
	left.speed = 0.1f;

	tright.PushBack({ 0, 128, 32, 32 });
	tright.PushBack({ 32, 128, 32, 32 });
	tright.PushBack({ 64, 128, 32, 32 });
	tright.PushBack({ 96, 128, 32, 32 });
	tright.speed = 0.1f;

	right.PushBack({ 0, 96, 32, 32 });
	right.PushBack({ 32, 96, 32, 32 });
	right.PushBack({ 64, 96, 32, 32 });
	right.PushBack({ 96, 96, 32, 32 });
	right.loop = true;
	right.speed = 0.1f;

	dying.PushBack({ 129, 0, 30, 30 });
	dying.loop = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/images/Marion.png");

	position.x = 100;
	position.y = 220;
	
	player_col = App->collision->AddCollider({ 0, 0, 21, 32 }, COLLIDER_PLAYER, this);

	font_score = App->fonts->Load("assets/images/fonts.png", "-1234567890", 1);

	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	strcpy(yokse, score);
	yokse[0] = 49;

	if (lives < 0)
	App->fade->FadeToBlack(App->scene_castle, App->scene_score, 0.1f);

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !_dying && !respawning)
	{
		position.x -= speed;
		if (position.x <= 0)
		{
			position.x = 0;
		}

		if (current_animation != &left && transition >= TRANSITION_SPEED)
		{
			left.Reset();
			current_animation = &left;
		}
		if (current_animation != &tleft && transition < TRANSITION_SPEED)
		{
			current_animation = &tleft;
		}
		transition++;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !_dying && !respawning)
	{
		position.x += speed;
		if (position.x >= 196)
		{
			position.x = 196;
		}
		if (current_animation != &right && transition >= TRANSITION_SPEED)
		{
			right.Reset();
			current_animation = &right;
		}
		if (current_animation != &tright && transition < TRANSITION_SPEED)
		{
			current_animation = &tright;
		}
		transition++;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !_dying && !respawning)
	{
		position.y += speed;
		if (position.y >= 288)
		{
			position.y = 288;
		}
	
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !_dying && !respawning)
	{
		position.y -= speed;
		if (position.y <= 0)
		{
			position.y = 0;
		}
	
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_REPEAT && SDL_GetTicks() >= shot && !_dying && !respawning)
	{
		shot = (SDL_GetTicks() + 500);
		if (powerup_lv == 0)
		{
			App->particles->AddParticle(App->particles->marionbeam_lv1[beam++], position.x + 11, position.y - 25, COLLIDER_PLAYER_SHOT);
			if (beam == 3) beam = 0;
			App->particles->AddParticle(App->particles->marionbeam_lv1[beam++], position.x + 11, position.y + 5, COLLIDER_PLAYER_SHOT, 0, -4, 140);
			if (beam == 3) beam = 0;
			App->particles->AddParticle(App->particles->marionbeam_lv1[beam++], position.x + 11, position.y + 35, COLLIDER_PLAYER_SHOT, 0, -4, 280);
			if (beam == 3) beam = 0;
			App->particles->AddParticle(App->particles->marionbeam_lv1[beam++], position.x + 11, position.y + 65, COLLIDER_PLAYER_SHOT, 0, -4, 420);
			if (beam == 3) beam = 0;
		}

		if (powerup_lv == 1)
		{
			App->particles->AddParticle(App->particles->marionbeam_lv2[beam++], position.x + 11, position.y - 25, COLLIDER_PLAYER_SHOT);
			if (beam == 3) beam = 0;
			App->particles->AddParticle(App->particles->marionbeam_lv2[beam++], position.x + 11, position.y + 5, COLLIDER_PLAYER_SHOT, 0, -4, 140);
			if (beam == 3) beam = 0;
			App->particles->AddParticle(App->particles->marionbeam_lv2[beam++], position.x + 11, position.y + 35, COLLIDER_PLAYER_SHOT, 0, -4, 280);
			if (beam == 3) beam = 0;
			App->particles->AddParticle(App->particles->marionbeam_lv2[beam++], position.x + 11, position.y + 65, COLLIDER_PLAYER_SHOT, 0, -4, 420);
			if (beam == 3) beam = 0;
		}
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/Marion Shot.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		current_animation = &idle;
		transition = 0;
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && godmode == false)
	{
		godmode = true;
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY, false);
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, false);
		App->collision->EditMatrix(COLLIDER_ENEMY, COLLIDER_PLAYER, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, false);
	}

	else if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && godmode == true)
	{
		godmode = false;
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY, true);
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, true);
		App->collision->EditMatrix(COLLIDER_ENEMY, COLLIDER_PLAYER, true);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, true);
	}

	player_col->SetPos(position.x + 3, position.y);

	if (_dying)
	{
		current_animation = &dying;
		if (deathcounter > 13)
		{
			position.y += 2;
		}
		deathcounter++;

		if (position.y > 320)
		{
			current_animation = &idle;
			_dying = false;
			respawning = true;
			deathcounter = 0;
			position.x = 51;
		}
	}

	if (respawning)
	{
		position.y -= 1;
		respawncounter++;
		if (respawncounter == 80)
		{
			respawning = false;
			temp_invincibility = true;
			respawncounter = 0;
		}
	}

	if (temp_invincibility)
	{
		invincibilitycounter++;
		if (invincibilitycounter == 120)
		{
			App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY, true);
			App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, true);
			App->collision->EditMatrix(COLLIDER_ENEMY, COLLIDER_PLAYER, true);
			App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, true);
			invincibilitycounter = 0;
		}
	}

	
	// Draw everything --------------------------------------

	App->fonts->BlitText(position.x, position.y, font_score, yokse);

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_ENEMY_SHOT)
	{
		lives -= 1;
		_dying = true;
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY, false);
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, false);
		App->collision->EditMatrix(COLLIDER_ENEMY, COLLIDER_PLAYER, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, false);

		if (lives < 0)
		{
			App->fade->FadeToBlack(App->scene_castle, App->scene_intro, 2.0f);
		}
	}
	if (c2->type == COLLIDER_PICKUP)
	{
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionpowerup.wav");;
		Mix_PlayChannel(-1, App->audio->sfx, 0);

		powerup_lv++;
		if (powerup_lv > 1);
		{
			powerup_lv = 1;
		}
	}
}
