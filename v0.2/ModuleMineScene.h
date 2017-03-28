#ifndef __MODULEMINESCENE_H__
#define __MODULEMINESCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct Mix_Music;

class ModuleMineScene : public Module
{
public:
	ModuleMineScene();
	~ModuleMineScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Music* music = nullptr;
	SDL_Rect background;
	bool fading = false;
	int yflag = -3215;
};

#endif