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
	SDL_Texture* knight = nullptr;
	SDL_Texture* bridge = nullptr;

	SDL_Rect background;

	SDL_Rect backgroundup;
	SDL_Rect npi;
	Animation flag;
	Animation knightleft;
	Animation knightright;
	Animation knightup;
	Animation knightdown;
	Animation bridge_anim;
	bool houseflag = false;
	float house1counter = -86;
	float yflag = -1788;
	float yflag2 = -1269;
	float knight_1_x_pos = 0;
	float knight_1_y_pos = 0;
	float knight_2_x_pos = 0;
	float knight_2_y_pos = 0;
	float bridge_speed_y = -83;
};

#endif