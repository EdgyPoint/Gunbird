#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_gamecontroller.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
	for (uint i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		controller[i] =B_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_GAMEPAD could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		if (SDL_NumJoysticks() > 0)
		{
			Controller = SDL_GameControllerOpen(0);
			if (Controller == nullptr)
			{
				LOG("Controller couldn't be initialized SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				controller_connected == true;
			}
		}
	};

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	 Uint8 buttons[SDL_CONTROLLER_BUTTON_MAX];
	buttons[SDL_CONTROLLER_BUTTON_A] = SDL_GameControllerGetButton(App->input->Controller, SDL_CONTROLLER_BUTTON_A);
	buttons[SDL_CONTROLLER_BUTTON_Y] = SDL_GameControllerGetButton(App->input->Controller, SDL_CONTROLLER_BUTTON_Y);
	buttons[SDL_CONTROLLER_BUTTON_B] = SDL_GameControllerGetButton(App->input->Controller, SDL_CONTROLLER_BUTTON_B);
	buttons[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = SDL_GameControllerGetButton(App->input->Controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	buttons[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = SDL_GameControllerGetButton(App->input->Controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);

	
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (buttons[i] == 1)
		{
			if (controller[i] == B_IDLE)
				controller[i] = B_DOWN;
			else
				controller[i] =B_REPEAT;
		}
		else
		{
			if (controller[i] == B_REPEAT || keyboard[i] ==B_DOWN)
				controller[i] = B_UP;
			else
				controller[i] = B_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	//Uint8
	//controller1.left_joystick.x = ((float)SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f);
	//controller1.left_joystick.y = ((float)SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f);
	//controller1.c_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_A));
	//controller1.f1_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_Y));
	//controller1.f2_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_B));
	//controller1.f3_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));
	//controller1.f4_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER));
	//controller1.space_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_A));
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}