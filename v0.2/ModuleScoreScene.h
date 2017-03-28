#ifndef __MODULESCORESCENE_H__
#define __MODULESCORESCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct Mix_Music;

class ModuleScoreScene : public Module
{
public:
	ModuleScoreScene();
	~ModuleScoreScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Music* music = nullptr;
	SDL_Rect background;
	bool fading = false;
};

#endif 