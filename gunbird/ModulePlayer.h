#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_LEVEL 4
#define MARION_RELOAD 90

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void shootburst(int level);
	void to_powerup();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* ui = nullptr;
	SDL_Texture* ui2 = nullptr;
	SDL_Rect p1display;
	SDL_Rect lifedisplay;
	SDL_Rect bombdisplay;
	Collider* player_col = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation left;
	Animation tleft;
	Animation right;
	Animation tright;
	Animation dying;
	Animation tilting; //used for stun
	Animation completingcharge;
	Animation shotcharged;
	Animation startbutton; //part of the UI
	iPoint position;
	int transition, beam, powerup_lv, invincibilitycounter, respawncounter, burst_counter, deathcounter, stuncounter, magicsparks, blinkcounter, score, blink = 0, bombCD = 0;
	bool godmode, _dying, respawning, temp_invincibility, stunned, shooting, poweruping = false;
	int lives = 2;
	int bombs = 2;
	int charge_up = 0;
	int finishing_charge = 0;
	bool out = false;
	uint shot;
	int font_score = -1;
	int font_scorescene = -1;
	char text_score[10];
	bool joystick_up;
	bool joystick_down;
	bool joystick_left;
	bool joystick_right;
};

#endif