#include<cstring>
#include<stdlib.h>
#include <stdio.h>
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
#include "ModulePlayer2.h"
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

	tilting.PushBack({ 0, 64, 32, 32 });
	tilting.PushBack({ 0, 32, 32, 32 });
	tilting.PushBack({ 0, 0, 32, 32 });
	tilting.PushBack({ 0, 32, 32, 32 });
	tilting.PushBack({ 0, 64, 32, 32 });
	tilting.PushBack({ 0, 128, 32, 32 });
	tilting.PushBack({ 0, 96, 32, 32 });
	tilting.PushBack({ 0, 128, 32, 32 });
	tilting.loop = true;
	tilting.speed = 0.5f;

	startbutton.PushBack({ 0, 320, 68, 13 });
	startbutton.PushBack({ 0, 333, 68, 13 });
	startbutton.speed = 0.03f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	powerup_lv = 0;
	lives = 2;

	graphics = App->textures->Load("assets/images/Marion.png");


	//Init UI
	ui = App->textures->Load("assets/images/UI.png");
	ui2 = App->textures->Load("assets/images/Intro Screen.png");

	p1display.x = 0;
	p1display.y = 0;
	p1display.w = 15;
	p1display.h = 12;

	lifedisplay.x = 15;
	lifedisplay.y = 0;
	lifedisplay.w = 13;
	lifedisplay.h = 13;

	position.x = 51;
	position.y = 320;
	
	player_col = App->collision->AddCollider({ 0, 0, 8, 8 }, COLLIDER_PLAYER, this);

	font_score = App->fonts->Load("assets/images/fonts.png", " 1234567890", 1, 1);

	respawning = true;


	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	powerup_lv = 0;
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
	{
		position.x -= speed;
		if (position.x <= 0)
		{
			position.x = 0;
		}
		if (!stunned)
		{
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
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
	{
		position.x += speed;
		if (position.x >= 196)
		{
			position.x = 196;
		}

		if (!stunned)
		{
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
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
	{
		position.y += speed;
		if (position.y >= 288)
		{
			position.y = 288;
		}
	
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
	{
		position.y -= speed;
		if (position.y <= 0)
		{
			position.y = 0;
		}
	
	}


	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN && SDL_GetTicks() >= shot && !_dying && !respawning && !stunned && !App->fade->fading)

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
		if (!stunned)
		{
			current_animation = &idle;
			transition = 0;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && godmode == false && !App->fade->fading)
	{
		godmode = true;
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_F, false);
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, false);
		App->collision->EditMatrix(COLLIDER_PLAYER2, COLLIDER_ENEMY_F, false);
		App->collision->EditMatrix(COLLIDER_PLAYER2, COLLIDER_ENEMY_SHOT, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER2, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER2, false);
	}

	else if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && godmode == true && !App->fade->fading)
	{
		godmode = false;
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_F, true);
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, true);
		App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER, true);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, true);
		App->collision->EditMatrix(COLLIDER_PLAYER2, COLLIDER_ENEMY_F, true);
		App->collision->EditMatrix(COLLIDER_PLAYER2, COLLIDER_ENEMY_SHOT, true);
		App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER2, true);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER2, true);
	}

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN && !App->fade->fading)
	{
		App->player2->Enable();
		App->player2->out = false;
	}

	player_col->SetPos(position.x + 10, position.y + 9);

	if (stunned)
	{
		
		stuncounter++;
		if (stuncounter == 64)
		{
			stunned = false;
			current_animation = &idle;
			stuncounter = 0;
		}
	}

	if (_dying)
	{
		current_animation = &dying;
		if (deathcounter > 13 && deathcounter <= 18)
		{
			position.y += 2;
		}
		if (deathcounter > 18)
		{
			position.y += 3;
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
		if (godmode == false)
		{
			App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_F, false);
			App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, false);
			App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER, false);
			App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, false);
		}

		if (!out)
		{
			position.y -= 1;
			respawncounter++;
		}
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
			if (godmode == false)
			{
				App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_F, true);
				App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, true);
				App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER, true);
				App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, true);
			}
			temp_invincibility = false;
			invincibilitycounter = 0;
		}
	}

	//Leave particles behind (yay! magic sparks)
	magicsparks++;
	if (magicsparks == 6)
	{
		App->particles->AddParticle(App->particles->magicspark[0], position.x + 8, position.y + 31, COLLIDER_NONE);
	}
	if (magicsparks == 12)
	{
		App->particles->AddParticle(App->particles->magicspark[1], position.x + 8, position.y + 31, COLLIDER_NONE);
	}

	if (magicsparks == 18)
	{
		App->particles->AddParticle(App->particles->magicspark[2], position.x + 8, position.y + 31, COLLIDER_NONE);
	}

	if (magicsparks == 24)
	{
		App->particles->AddParticle(App->particles->magicspark[3], position.x + 8, position.y + 31, COLLIDER_NONE);
		magicsparks = 0;
	}

	//Return to intro scene if both players are out
	if (out && App->player2->out)
	{
		App->fade->FadeToBlack(App->scene_castle, App->scene_intro, 2.0f);
	}



	sprintf_s(text_score, 10, "%7d", score);
	
	blink++;
	if (blink == 6)
	blink = 0;

	blinkcounter++;
	if (blinkcounter == 6)
		blinkcounter = 0;

	// Draw everything --------------------------------------
	if (blinkcounter > 3 && (respawning || temp_invincibility))
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	else if (!respawning && !temp_invincibility)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	//Blit UI
	App->render->Blit(ui, 5, 6, &p1display, 0, true);

	if (lives == 1)
	App->render->Blit(ui, 5, 21, &lifedisplay, 0, true);
	 
	if (lives == 2)
	{
		App->render->Blit(ui, 5, 21, &lifedisplay, 0, true);
		App->render->Blit(ui, 21, 21, &lifedisplay, 0, true);
	}

	App->fonts->BlitText(20, 6, font_score, text_score);

	if (App->player2->out == true)
	{
		App->render->Blit(ui2, 117, 6, &(startbutton.GetCurrentFrame()), 0, true);
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_ENEMY_SHOT)
	{
		lives -= 1;
		_dying = true;
		
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_F, false);
		App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER, false);
		App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, false);

		App->particles->AddParticle(App->particles->medium_explosion, position.x - 40, position.y - 25, COLLIDER_NONE);
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/mediumexplosion.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);

		App->audio->sfx = App->audio->LoadSFX("assets/SFX/mariondeath.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);

		if (lives < 0)
		{
			out = true;
		}
	}

	if (c2->type == COLLIDER_ENEMY_F && !stunned)
	{
		stunned = true;
		powerup_lv--;
		App->particles->AddParticle(App->particles->playercollision, position.x, position.y, COLLIDER_NONE);
		current_animation = &tilting;

		if (powerup_lv < 0)
		{
			powerup_lv = 0;
		}
	}

	if (c2->type == COLLIDER_POWERUP)
	{
		if (powerup_lv == 0)
		{
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionpowerup.wav");;
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}

		if (powerup_lv == 1)
		{
			App->player->score += 2000;
			App->particles->AddParticle(App->particles->powerupscore, position.x + 4, position.y + 4, COLLIDER_NONE);
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/MaxPower.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}

		if (powerup_lv < 1)
		powerup_lv++;
	}

	if (c2->type == COLLIDER_COIN)
	{
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/collectcoin.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
		score += 200;
	}
}
