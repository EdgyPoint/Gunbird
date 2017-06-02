#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum BUTTON_STATE
{
	B_IDLE = 0,
	B_DOWN,
	B_REPEAT,
	B_UP
};

//struct Gamepad
//{
//	p2Point<float> left_joystick;
//	bool f1_button;
//	bool f2_button;
//	bool f3_button;
//	bool f4_button;
//	bool f5_button;
//	bool c_button;
//	bool space_button;
//};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	BUTTON_STATE controller[SDL_CONTROLLER_BUTTON_MAX];
	SDL_GameController* Controller = nullptr;
		//Gamepad controller1;

		bool controller_connected;
};

#endif // __ModuleInput_H__