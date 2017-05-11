#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum CONTROLLER_STATE {
	BUTTON_IDLE = 0,
	BUTTON_DOWN,
	BUTTON_REPEAT,
	BUTTON_UP
};

struct Gamepad {
	CONTROLLER_STATE A;
	CONTROLLER_STATE X;
	CONTROLLER_STATE START;
	CONTROLLER_STATE LEFT_AXIS_POS_X;
	CONTROLLER_STATE LEFT_AXIS_NEG_X;
	CONTROLLER_STATE LEFT_AXIS_POS_Y;
	CONTROLLER_STATE LEFT_AXIS_NEG_Y;
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	void inputGamepad();

	KEY_STATE keyboard[MAX_KEYS];
	Gamepad gamepad;

private:

	SDL_GameController* controller;
};

#endif // __ModuleInput_H__