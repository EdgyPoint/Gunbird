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
#include"ModuleVillageScene.h"
#include "ModuleCastleScene.h"
#include "ModuleScoreScene.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_gamecontroller.h"

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

	completingcharge.PushBack({ 0, 160, 32, 37 });
	completingcharge.PushBack({ 32, 160, 32, 37 });
	completingcharge.PushBack({ 32, 160, 32, 37 });
	completingcharge.PushBack({ 32, 160, 32, 37 });
	completingcharge.PushBack({ 32, 160, 32, 37 });
	completingcharge.PushBack({ 64, 160, 32, 37 });
	completingcharge.PushBack({ 64, 160, 32, 37 });
	completingcharge.PushBack({ 64, 160, 32, 37 });
	completingcharge.PushBack({ 64, 160, 32, 37 });
	completingcharge.PushBack({ 96, 160, 32, 37 });
	completingcharge.PushBack({ 96, 160, 32, 37 });
	completingcharge.PushBack({ 96, 160, 32, 37 });
	completingcharge.PushBack({ 96, 160, 32, 37 });
	completingcharge.loop = true;
	completingcharge.speed = 0.5f;

	shotcharged.PushBack({ 0, 197, 32, 37 });
	shotcharged.PushBack({ 32, 197, 32, 37 });
	shotcharged.loop = true;
	shotcharged.speed = 0.25f;

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
	bombs = 2;
	godmode = false;

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

	bombdisplay.x = 15;
	bombdisplay.y = 15;
	bombdisplay.w = 12;
	bombdisplay.h = 15;

	gmdisplay.x = 28;
	gmdisplay.y = 12;
	gmdisplay.w = 11;
	gmdisplay.h = 16;

	position.x = 51;
	position.y = 320;
	
	player_col = App->collision->AddCollider({ 0, 0, 8, 8 }, COLLIDER_PLAYER, this);

	font_score = App->fonts->Load("assets/images/fonts.png", " 1234567890", 1, 1);
	font_scorescene = App->fonts->Load("assets/images/fonts2.png", " 1234567890", 1, 1);

	respawning = true;


	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	powerup_lv = 0;
	App->textures->Unload(graphics);
	App->textures -> Unload(ui);
	App->textures->Unload(ui2);
	out = false;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->scene_village->ending)
		position.y -= 3;

	if (!shooting && poweruping)
	{
		powerup_lv++;
		poweruping = false;
		if (powerup_lv > MAX_LEVEL)
			powerup_lv = MAX_LEVEL;
	}

	int speed = 2;
	if (counter != 0)
	counter++;
	if (counter == 120)counter = 0;




	// Move left
if ((!App->scene_village->ending && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->Controller1, SDL_CONTROLLER_AXIS_LEFTX) < -13000) && !_dying && !respawning && !App->fade->fading)
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

	// --------------------------


	

	// Move right
if ((!App->scene_village->ending && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->Controller1, SDL_CONTROLLER_AXIS_LEFTX) > 10000) && !_dying && !respawning && !App->fade->fading)
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
	// --------------------------

	// Move down
if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->Controller1, SDL_CONTROLLER_AXIS_LEFTY) > 10000) && !_dying && !respawning && !App->fade->fading)
	{
		position.y += speed;
		if (position.y >= 288)
		{
			position.y = 288;
		}
	
	}
	// --------------------------

	// Move up
if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->Controller1, SDL_CONTROLLER_AXIS_LEFTY) < -13000) && !_dying && !respawning && !App->fade->fading)
	{
		position.y -= speed;
		if (position.y <= 0)
		{
			position.y = 0;
		}
	
	}
	// --------------------------

	// Charged shot
		// Charge up
if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_REPEAT || App->input->controller1[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_REPEAT) && !_dying && !respawning && !stunned && !App->fade->fading && charge_up < 110)
	{
		charge_up++;
	}
		// Finishing charge
if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_REPEAT || App->input->controller1[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_REPEAT) && !_dying && !respawning && !stunned && !App->fade->fading && charge_up == 110 && finishing_charge < 26)
	{
		finishing_charge++;
	}
	if (time_since_last_charged < 100)
	time_since_last_charged++;
		// Release
	if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_UP || App->input->controller1[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_UP) && !_dying && !respawning && !stunned && !App->fade->fading)
	{
		if (charge_up == 110)
		{
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionchargedshot.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);

			App->particles->AddParticle(App->particles->chargedbeam, position.x - 2, position.y - 32, COLLIDER_CHARGEDSHOT);

			time_since_last_charged = 0;
		}
		charge_up = 0;
		finishing_charge = 0;
	}
	// --------------------------

	// Shoot
	if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN || App->input->controller1[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_DOWN) && !_dying && !respawning && !stunned && !App->fade->fading)
	{
		if (!shooting)
		{
			shot = SDL_GetTicks();

			App->audio->sfx = App->audio->LoadSFX("assets/SFX/Marion Shot.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}

		shooting = true;
	}
	// --------------------------

	// Bomb
	if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN || App->input->controller1[SDL_CONTROLLER_BUTTON_X] == BUTTON_STATE::B_DOWN) && !_dying && !respawning && !stunned && !App->fade->fading && bombCD == 0 && bombs > 0)
	{
		bombs--;

		bombCD = 125;
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionbomb.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
		App->particles->AddParticle(App->particles->bombshot_up, position.x - 8, position.y - 35, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_upleft, position.x - 6, position.y - 6, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_left, position.x - 35, position.y - 8, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_downleft, position.x - 6, position.y - 10, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_down, position.x - 8, position.y + 23, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_downright, position.x - 10, position.y - 10, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_right, position.x + 23, position.y - 8, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_upright, position.x - 10, position.y - 6, COLLIDER_BOMBSHOT);

		App->particles->AddParticle(App->particles->particle_clearer, 0, 0, COLLIDER_BOMBCLEAN);
	}
	if (bombCD == 95)
	{
		App->particles->AddParticle(App->particles->bombshot_up, position.x - 8, position.y - 35, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_upleft, position.x - 6, position.y - 6, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_left, position.x - 35, position.y - 8, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_downleft, position.x - 6, position.y - 10, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_down, position.x - 8, position.y + 23, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_downright, position.x - 10, position.y - 10, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_right, position.x + 23, position.y - 8, COLLIDER_BOMBSHOT);
		App->particles->AddParticle(App->particles->bombshot_upright, position.x - 10, position.y - 6, COLLIDER_BOMBSHOT);
	}
	if (bombCD != 0)
		bombCD--;
	// --------------------------

	// Adding all 4 particles
	if (shot <= SDL_GetTicks() && shooting)
		shootburst(powerup_lv);
	// --------------------------


	// Returning to idle if no side movement input is detected
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		if (!stunned)
		{
			current_animation = &idle;
			transition = 0;
		}
	}

	if (charge_up == 110)
	{
		current_animation = &completingcharge;
	}
	if (finishing_charge == 26)
	{
		current_animation = &shotcharged;
	}
	// --------------------------

	// Debug features
	if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) && godmode == false && !App->fade->fading)
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

	else if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) && godmode == true && !App->fade->fading)
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

	else if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) && !App->fade->fading)
	{
			powerup_lv++;
			if (powerup_lv > MAX_LEVEL)
				powerup_lv = MAX_LEVEL;
			
			App->player2->powerup_lv++;
			if (App->player2->powerup_lv > MAX_LEVEL)
				App->player2->powerup_lv = MAX_LEVEL;
			

		App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionpowerup.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}
	else if ((!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) && !App->fade->fading)
	{
		if (bombs != 4)
			bombs++;
		if (App->player2->bombs != 4)
			App->player2->bombs++;

		App->audio->sfx = App->audio->LoadSFX("assets/SFX/collectbomb.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
	}

	if (!App->scene_village->ending &&App->input->keyboard[SDL_SCANCODE_KP_ENTER] == KEY_STATE::KEY_DOWN && !App->fade->fading)
	{
		App->player2->Enable();
		App->player2->out = false;
	}
	// --------------------------

	// Update player's collider to current position
	player_col->SetPos(position.x + 10, position.y + 9);
	// --------------------------

	// Stun, death and respawn
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
	// --------------------------

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
	// --------------------------

	//Return to intro scene if both players are out
	if (out && App->player2->out)
	{
		App->fade->FadeToBlack(App->scene_castle, App->scene_intro, 2.0f);
	}
	// --------------------------


	// Blit score
	sprintf_s(text_score, 10, "%7d", score);
	// --------------------------
	

	// Blit player
	blink++;
	if (blink == 6)
		blink = 0;

	blinkcounter++;
	if (blinkcounter == 6)
		blinkcounter = 0;

	if (blinkcounter > 3 && (respawning || temp_invincibility))
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	else if (!respawning && !temp_invincibility && charge_up != 110)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	// --------------------------

	// Blit shot charging
	if (charge_up == 110)
	{
		App->render->Blit(graphics, position.x, position.y - 5, &(current_animation->GetCurrentFrame()));
	}
	// --------------------------

	//Blit UI
	App->render->Blit(ui, 5, 6, &p1display, 0, true);

	if (godmode == true)
		App->render->Blit(ui, 6, 282, &gmdisplay, 0, true);

	if (lives == 1)
		App->render->Blit(ui, 5, 21, &lifedisplay, 0, true);
	 
	if (lives == 2)
	{
		App->render->Blit(ui, 5, 21, &lifedisplay, 0, true);
		App->render->Blit(ui, 21, 21, &lifedisplay, 0, true);
	}
	
	if (bombs == 1)
		App->render->Blit(ui, 6, 300, &bombdisplay, 0, true);

	if (bombs == 2)
	{
		App->render->Blit(ui, 6, 300, &bombdisplay, 0, true);
		App->render->Blit(ui, 22, 300, &bombdisplay, 0, true);
	}

	if (bombs == 3)
	{
		App->render->Blit(ui, 6, 300, &bombdisplay, 0, true);
		App->render->Blit(ui, 22, 300, &bombdisplay, 0, true);
		App->render->Blit(ui, 38, 300, &bombdisplay, 0, true);
	}

	if (bombs == 4)
	{
		App->render->Blit(ui, 6, 300, &bombdisplay, 0, true);
		App->render->Blit(ui, 22, 300, &bombdisplay, 0, true);
		App->render->Blit(ui, 38, 300, &bombdisplay, 0, true);
		App->render->Blit(ui, 56, 300, &bombdisplay, 0, true);
	}
	// --------------------------

	// Blit score
	App->fonts->BlitText(20, 6, font_score, text_score);
	// --------------------------

	if (App->player2->out == true)
	{
		App->render->Blit(ui2, 117, 6, &(startbutton.GetCurrentFrame()), 0, true);
	}
	// --------------------------

	return UPDATE_CONTINUE;
}

void ModulePlayer::shootburst(int level)
{
	switch (level)
	{
	case 0:
		App->particles->AddParticle(App->particles->marionbeam_lv1[beam++], position.x +11, position.y, COLLIDER_PLAYER_SHOT);
		break;
	case 1:
		App->particles->AddParticle(App->particles->marionbeam_lv2[beam++], position.x +6, position.y, COLLIDER_PLAYER_SHOT);
		break;
	case 2:
		App->particles->AddParticle(App->particles->marionbeam_lv1[beam], position.x +11, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->marionbeamleft_lv1[beam], position.x +9, position.y, COLLIDER_PLAYER_SHOT, -1.75f);
		App->particles->AddParticle(App->particles->marionbeamright_lv1[beam++], position.x + 14, position.y, COLLIDER_PLAYER_SHOT, 1.75f);
		if (counter == 0)
		{
			counter = 1;
			App->particles->AddParticle(App->particles->star, position.x + 14, position.y, COLLIDER_PLAYER_SHOT, 0, true, NONE, true);
			App->particles->AddParticle(App->particles->star, position.x - 1, position.y, COLLIDER_PLAYER_SHOT, 0, true, NONE, true);
		}
		break;
	case 3:
		App->particles->AddParticle(App->particles->marionbeam_lv2[beam], position.x +6, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->marionbeamleft_lv2[beam], position.x +3, position.y, COLLIDER_PLAYER_SHOT, -1.75f);
		App->particles->AddParticle(App->particles->marionbeamright_lv2[beam++], position.x +10, position.y, COLLIDER_PLAYER_SHOT, 1.75f);
		if (counter == 0)
		{
			if (burst_counter != 3)
			{
				App->particles->AddParticle(App->particles->star, position.x + 14, position.y, COLLIDER_PLAYER_SHOT, 0, true, NONE, true);
				App->particles->AddParticle(App->particles->star, position.x - 1, position.y, COLLIDER_PLAYER_SHOT, 0, true, NONE, true);
			}
			else
				counter = 1;
		}
		break;
	}

	shot += MARION_RELOAD;
	if (beam == 3) beam = 0;
	burst_counter++;
	if (burst_counter == 4)
	{
		burst_counter = 0;
		shooting = false;
	}
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_ENEMY_SHOT)
	{
		charge_up = 0;
		finishing_charge = 0;

		lives -= 1;
		_dying = true;

		powerup_lv = 0;
		
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
		charge_up = 0;
		finishing_charge = 0;

		stunned = true;
		
		App->particles->AddParticle(App->particles->playercollision, position.x, position.y, COLLIDER_NONE);
		current_animation = &tilting;

		powerup_lv--;
		if (powerup_lv < 0)
			powerup_lv = 0;
	}

	if (c2->type == COLLIDER_POWERUP)
	{
		if (powerup_lv < MAX_LEVEL)
		{
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionpowerup.wav");;
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}

		if (powerup_lv == MAX_LEVEL)
		{
			App->player->score += 2000;
			App->particles->AddParticle(App->particles->powerupscore, position.x + 4, position.y + 4, COLLIDER_NONE);
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionmaxpowerup.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}
		App->particles->DeleteParticle(c2);

		poweruping = true;
	}

	if (c2->type == COLLIDER_BOMB)
	{
		if (bombs == 4)
		score += 10000;

		if (bombs < 4)
		{
			bombs++;
		}

		App->audio->sfx = App->audio->LoadSFX("assets/SFX/collectbomb.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);

		App->particles->DeleteParticle(c2);
	}

	if (c2->type == COLLIDER_COIN)
	{
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/collectcoin.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
		score += 200;
		App->particles->DeleteParticle(c2);
	}
}
