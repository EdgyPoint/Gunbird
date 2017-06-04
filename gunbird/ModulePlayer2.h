#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MARION_RELOAD 120

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
private:
	int beam = 0;
	uint shot;

public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void shootburst(int level);
	void to_powerup();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* ui = nullptr;
	SDL_Rect p2display;
	SDL_Rect lifedisplay;
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
	iPoint position;
	int transition, powerup_lv, invincibilitycounter, respawncounter, burst_counter, deathcounter, stuncounter, magicsparks, blinkcounter, score, blink = 0, bombCD = 0;
	bool _dying, respawning, temp_invincibility, stunned, poweruping, shooting = false;
	int lives = 2;
	int bombs = 0;
	int charge_up = 0;
	int finishing_charge = 0;
	int time_since_last_charged = 0; // this variable is to use acceleration on the charged shot
	bool out = true;
	char text_score2[10];
};

#endif