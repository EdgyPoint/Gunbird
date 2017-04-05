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
	SDL_Texture* graphics3 = nullptr;
	SDL_Texture* Turretcopter_texture = nullptr;
	SDL_Rect background;
	SDL_Rect castlehouse1;
	SDL_Rect backgroundup;
	Animation flag;
	Animation Turretcopter_animation;
	Collider* Turretcopter;
	bool houseflag = false;
	float house1counter = -86;
	float yflag = -1788;
	float yflag2 = -1269;
};

#endif