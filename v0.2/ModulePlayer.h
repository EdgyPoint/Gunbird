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
	Collider* player_col = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation left;
	Animation tleft;
	Animation right;
	Animation tright;
	Animation dying;
	iPoint position;
	int transition = 0;
	int beam = 0;
	int powerup_lv = 0;
	bool godmode = false;
	bool _dying = false;
	bool respawning = false;
	bool temp_invincibility = false;
	int invincibilitycounter = 0;
	int respawncounter = 0;
	int deathcounter = 0;
	int lives = 2;
	uint shot;
	int font_score = -1;
	char* score = "-----00";
	char yokse[8];
};

#endif