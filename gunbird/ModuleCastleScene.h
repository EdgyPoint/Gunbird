#ifndef __MODULECASTLESCENE_H__
#define __MODULECASTLESCENE_H__

#include "Module.h"
#include "Path.h"
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

	float yflag;
	fPoint knight1 = { 0.0f,0.0f };
	fPoint knight2 = { 0.0f, 0.0f };
	float bridge_speed_y;
	float mortar_speed_y = 0;
};

#endif