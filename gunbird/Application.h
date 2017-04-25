#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModulePlayer2;
class ModuleCollision;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleParticles;
class ModuleRender;
class ModuleItems;
class ModuleIntroScene;
class ModuleCastleScene;
class ModuleMineScene;
class ModuleScoreScene;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleEnemies;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModulePlayer2* player2;
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleIntroScene* scene_intro;
	ModuleCastleScene* scene_castle;
	ModuleMineScene* scene_mine;
	ModuleScoreScene* scene_score;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleCollision* collision;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;
	ModuleItems* items;
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