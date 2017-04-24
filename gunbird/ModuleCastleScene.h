#ifndef __MODULECASTLESCENE_H__
#define __MODULECASTLESCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleCastleScene : public Module
{
public:
	ModuleCastleScene();
	~ModuleCastleScene();

	bool Start();
	update_status Update();
	bool CleanUp();


	void ModuleCastleScene::OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* trump = nullptr;
	SDL_Texture* knight = nullptr;
	SDL_Texture* river = nullptr;
	SDL_Texture* bridge = nullptr;
	SDL_Texture* mortar = nullptr;
	SDL_Rect background;
	SDL_Rect npi;
	Animation flag;
	Animation knightleft;
	Animation knightup;
	Animation thebossstanding;
	Animation thebossup;
	Animation acestanding;
	Animation aceup;
	Animation acelaughing;


	Animation river1;
	Animation river2;
	Animation bridge_anim;
	Animation dead_mortar;

	bool houseflag = false;
	float yflag = -1357;
	float knight_1_x_pos = 0;
	float knight_1_y_pos = 0;
	float knight_2_x_pos = 0;
	float knight_2_y_pos = 0;
	float bridge_speed_y = -83;
	float mortar_speed_y = 0;
};

#endif