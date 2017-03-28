#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 8

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleMineScene;
class ModuleScoreScene;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleMineScene* scene_mine;
	ModuleScoreScene* scene_score;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__