#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


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
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* ui = nullptr;
	SDL_Rect p1display;
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
	iPoint position;
	int transition = 0;
	int beam = 0;
	int powerup_lv = 0;
	bool godmode = false;
	bool _dying = false;
	bool respawning = false;
	bool temp_invincibility = false;
	bool stunned = false;
	int invincibilitycounter = 0;
	int respawncounter = 0;
	int deathcounter = 0;
	int stuncounter = 0;
	int magicsparks = 0;
	int lives = 2;
	bool out = false;
	uint shot;
	int font_score = -1;
	int score = 0;
	char text_score[10];
};

#endif