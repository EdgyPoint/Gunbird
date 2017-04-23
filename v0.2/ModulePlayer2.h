#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


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
	Animation tilting; //used for stun
	iPoint position;
	int transition = 0;
	int powerup_lv = 0;
	bool _dying = false;
	bool respawning = false;
	bool temp_invincibility = false;
	bool stunned = false;
	int invincibilitycounter = 0;
	int respawncounter = 0;
	int deathcounter = 0;
	int lives = 2;
	bool out = true;

};

#endif