#include <stdio.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntroScene.h"
#include "ModuleVillageScene.h"
#include "ModuleCastleScene.h"
#include "ModuleScoreScene.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 0, 64, 32, 32 });
	idle.PushBack({ 32, 64, 32, 32 });
	idle.PushBack({ 64, 64, 32, 32 });
	idle.PushBack({ 96, 64, 32, 32 });
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
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player2");

	powerup_lv = 0;
	lives = 2;
	bombs = 2;

	graphics = App->textures->Load("assets/images/Marion.png");
	ui = App->textures->Load("assets/images/UI.png");

	p2display.x = 28;
	p2display.y = 0;
	p2display.w = 15;
	p2display.h = 12;

	lifedisplay.x = 15;
	lifedisplay.y = 0;
	lifedisplay.w = 13;
	lifedisplay.h = 13;

	bombdisplay.x = 15;
	bombdisplay.y = 15;
	bombdisplay.w = 12;
	bombdisplay.h = 15;

	position.x = 141;
	position.y = 320;

	player_col = App->collision->AddCollider({ 0, 0, 8, 8 }, COLLIDER_PLAYER2, this);

	respawning = true;

	return true;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if (!shooting && poweruping)
	{
		powerup_lv++;
		poweruping = false;
		if (powerup_lv == MAX_LEVEL)
			powerup_lv = MAX_LEVEL - 1;
	}

	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
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

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
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

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
	{
		position.y += speed;
		if (position.y >= 288)
		{
			position.y = 288;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && !_dying && !respawning && !App->fade->fading)
	{
		position.y -= speed;
		if (position.y <= 0)
		{
			position.y = 0;
		}

	}

	// Charged shot

		// Charge up
	if ((App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_REPEAT || App->input->controller2[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_REPEAT) && !_dying && !respawning && !stunned && !App->fade->fading && charge_up < 110)
	{
		charge_up++;
	}
		// Finishing charge
	if ((App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_REPEAT || App->input->controller2[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_REPEAT) && !_dying && !respawning && !stunned && !App->fade->fading && charge_up == 110 && finishing_charge < 26)
	{
		finishing_charge++;
	}
	if (time_since_last_charged < 100)
		time_since_last_charged++;
		// Release
	if ((App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_UP || App->input->controller2[SDL_CONTROLLER_BUTTON_A] == BUTTON_STATE::B_UP) && !_dying && !respawning && !stunned && !App->fade->fading)

	{
		if (charge_up == 110)
		{
			App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionchargedshot.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);

			App->particles->AddParticle(App->particles->chargedbeam, position.x - 2, position.y - 32, COLLIDER_CHARGEDSHOT2);

			time_since_last_charged = 0;
		}
		charge_up = 0;
		finishing_charge = 0;
	}

	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && !_dying && !respawning && !stunned && !App->fade->fading)

	{
		if (!shooting)
		{
			shot = SDL_GetTicks();

			App->audio->sfx = App->audio->LoadSFX("assets/SFX/Marion Shot.wav");
			Mix_PlayChannel(-1, App->audio->sfx, 0);
		}

		shooting = true;
	}


	if (App->input->keyboard[SDL_SCANCODE_KP_1] == KEY_STATE::KEY_DOWN && !_dying && !respawning && !stunned && !App->fade->fading && bombCD == 0 && bombs > 0)
	{
		bombs--;
		bombCD = 125;
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionbomb.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
		App->particles->AddParticle(App->particles->bombshot_up, position.x - 8, position.y - 35, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_upleft, position.x - 6, position.y - 6, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_left, position.x - 35, position.y - 8, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_downleft, position.x - 6, position.y - 10, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_down, position.x - 8, position.y + 23, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_downright, position.x - 10, position.y - 10, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_right, position.x + 23, position.y - 8, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_upright, position.x - 10, position.y - 6, COLLIDER_BOMBSHOT2);

		App->particles->AddParticle(App->particles->particle_clearer, 0, 0, COLLIDER_BOMBCLEAN);
	}
	if (bombCD == 95)
	{
		App->particles->AddParticle(App->particles->bombshot_up, position.x - 8, position.y - 35, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_upleft, position.x - 6, position.y - 6, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_left, position.x - 35, position.y - 8, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_downleft, position.x - 6, position.y - 10, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_down, position.x - 8, position.y + 23, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_downright, position.x - 10, position.y - 10, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_right, position.x + 23, position.y - 8, COLLIDER_BOMBSHOT2);
		App->particles->AddParticle(App->particles->bombshot_upright, position.x - 10, position.y - 6, COLLIDER_BOMBSHOT2);
	}
	if (bombCD != 0)
		bombCD--;

	//Adding all 4 particles
	if (shot <= SDL_GetTicks() && shooting)
		shootburst(powerup_lv);




	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
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
			position.x = 141;
		}
	}

	if (respawning)
	{
		if (App->player->godmode == false)
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
				App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_F, true);
				App->collision->EditMatrix(COLLIDER_PLAYER, COLLIDER_ENEMY_SHOT, true);
				App->collision->EditMatrix(COLLIDER_ENEMY_F, COLLIDER_PLAYER, true);
				App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER, true);

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

	//Blit UI
	if (!out)
	{
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

		if (lives == 1)
			App->render->Blit(ui, 116, 21, &lifedisplay, 0, true);

		if (lives == 2)
		{
			App->render->Blit(ui, 116, 21, &lifedisplay, 0, true);
			App->render->Blit(ui, 132, 21, &lifedisplay, 0, true);
		}
		if (bombs == 1)
			App->render->Blit(ui, 118, 300, &bombdisplay, 0, true);

		if (bombs == 2)
		{
			App->render->Blit(ui, 118, 300, &bombdisplay, 0, true);
			App->render->Blit(ui, 134, 300, &bombdisplay, 0, true);
		}

		if (bombs == 3)
		{
			App->render->Blit(ui, 118, 300, &bombdisplay, 0, true);
			App->render->Blit(ui, 134, 300, &bombdisplay, 0, true);
			App->render->Blit(ui, 150, 300, &bombdisplay, 0, true);
		}

		if (bombs == 4)
		{
			App->render->Blit(ui, 118, 300, &bombdisplay, 0, true);
			App->render->Blit(ui, 134, 300, &bombdisplay, 0, true);
			App->render->Blit(ui, 150, 300, &bombdisplay, 0, true);
			App->render->Blit(ui, 166, 300, &bombdisplay, 0, true);
		}

		sprintf_s(text_score2, 10, "%7d", score);
	}


	App->fonts->BlitText(132, 6, App->player->font_score, text_score2);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::shootburst(int level)
{
	switch (level)
	{
	case 0:
		App->particles->AddParticle(App->particles->marionbeam_lv1[beam++], position.x + 11, position.y - 25, COLLIDER_PLAYER_SHOT);
		break;
	case 1:
		App->particles->AddParticle(App->particles->marionbeam_lv2[beam++], position.x + 7, position.y - 25, COLLIDER_PLAYER_SHOT);
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

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (!out)
	{
		if (c2->type == COLLIDER_PLAYER2_SHOT)
		{
			if (c1->type == COLLIDER_ENEMY)
			{
				c1->to_delete = true;
			}
			else if (c1->type == COLLIDER_WALL)
			{
				c2->to_delete = true;
			}
		}

		if (c1->type == COLLIDER_PLAYER2)
		{

			if (c2->type == COLLIDER_ENEMY_SHOT && App->player->godmode == false)
			{
				lives -= 1;
				_dying = true;
				App->collision->EditMatrix(COLLIDER_PLAYER2, COLLIDER_ENEMY, false);
				App->collision->EditMatrix(COLLIDER_PLAYER2, COLLIDER_ENEMY_SHOT, false);
				App->collision->EditMatrix(COLLIDER_ENEMY, COLLIDER_PLAYER2, false);
				App->collision->EditMatrix(COLLIDER_ENEMY_SHOT, COLLIDER_PLAYER2, false);

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

			if (c2->type == COLLIDER_ENEMY_F && !stunned && App->player->godmode == false)
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
				App->audio->sfx = App->audio->LoadSFX("assets/SFX/marionpowerup.wav");;
				Mix_PlayChannel(-1, App->audio->sfx, 0);

				poweruping = true;


				App->particles->DeleteParticle(c2);
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
			}
		}

	}
}