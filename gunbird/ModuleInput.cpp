#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
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

	controller = nullptr;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				break;
			}
			else {
				LOG("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

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

	inputGamepad();

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			SDL_GameController *controller = SDL_GameControllerOpen(i);
			if (controller) {
				SDL_GameControllerClose(controller);
			}
			else {
				LOG("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

	return true;
}

void ModuleInput::inputGamepad() {
	//A
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) == 1) {
		if (gamepad.A == BUTTON_IDLE)
			gamepad.A = BUTTON_DOWN;
		else
			gamepad.A = BUTTON_REPEAT;
	}
	else
	{
		if (gamepad.A == BUTTON_REPEAT || (gamepad.A == BUTTON_DOWN))
			gamepad.A = BUTTON_UP;
		else
			gamepad.A = BUTTON_IDLE;
	}

	//X
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) == 1) {
		if (gamepad.A == BUTTON_IDLE)
			gamepad.A = BUTTON_DOWN;
		else
			gamepad.A = BUTTON_REPEAT;
	}
	else
	{
		if (gamepad.A == BUTTON_REPEAT || (gamepad.A == BUTTON_DOWN))
			gamepad.A = BUTTON_UP;
		else
			gamepad.A = BUTTON_IDLE;
	}

	//START
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START) == 1) {
		if (gamepad.START == BUTTON_IDLE)
			gamepad.START = BUTTON_DOWN;
		else
			gamepad.START = BUTTON_REPEAT;
	}
	else
	{
		if (gamepad.START == BUTTON_REPEAT || (gamepad.START == BUTTON_DOWN))
			gamepad.START = BUTTON_UP;
		else
			gamepad.START = BUTTON_IDLE;
	}

	//LEFT STICK AXIS X POSITIVE
	if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) > 8191) {
		if (gamepad.LEFT_AXIS_POS_X == BUTTON_IDLE)
			gamepad.LEFT_AXIS_POS_X = BUTTON_DOWN;
		else
			gamepad.LEFT_AXIS_POS_X = BUTTON_IDLE;
	}
	else
	{
		if (gamepad.LEFT_AXIS_POS_X == BUTTON_REPEAT || gamepad.LEFT_AXIS_POS_X == BUTTON_DOWN)
			gamepad.LEFT_AXIS_POS_X = BUTTON_UP;
		else
			gamepad.LEFT_AXIS_POS_X = BUTTON_IDLE;
	}

	//LEFT STICK AXIS X NEGATIVE
	if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) < -8191) {
		if (gamepad.LEFT_AXIS_NEG_X == BUTTON_IDLE)
			gamepad.LEFT_AXIS_NEG_X = BUTTON_DOWN;
		else
			gamepad.LEFT_AXIS_NEG_X = BUTTON_IDLE;
	}
	else
	{
		if (gamepad.LEFT_AXIS_NEG_X == BUTTON_REPEAT || gamepad.LEFT_AXIS_POS_X == BUTTON_DOWN)
			gamepad.LEFT_AXIS_NEG_X = BUTTON_UP;
		else
			gamepad.LEFT_AXIS_NEG_X = BUTTON_IDLE;
	}

	//LEFT STICK AXIS Y POSITIVE
	if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > 8191) {
		if (gamepad.LEFT_AXIS_POS_Y == BUTTON_IDLE)
			gamepad.LEFT_AXIS_POS_Y = BUTTON_DOWN;
		else
			gamepad.LEFT_AXIS_POS_Y = BUTTON_IDLE;
	}
	else
	{
		if (gamepad.LEFT_AXIS_POS_Y == BUTTON_REPEAT || gamepad.LEFT_AXIS_POS_X == BUTTON_DOWN)
			gamepad.LEFT_AXIS_POS_Y = BUTTON_UP;
		else
			gamepad.LEFT_AXIS_POS_Y  = BUTTON_IDLE;
	}

	//LEFT STICK AXIS Y NEGATIVE
	if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < -8191) {
		if (gamepad.LEFT_AXIS_NEG_Y == BUTTON_IDLE)
			gamepad.LEFT_AXIS_NEG_Y = BUTTON_DOWN;
		else
			gamepad.LEFT_AXIS_NEG_Y = BUTTON_IDLE;
	}
	else
	{
		if (gamepad.LEFT_AXIS_NEG_Y == BUTTON_REPEAT || gamepad.LEFT_AXIS_POS_X == BUTTON_DOWN)
			gamepad.LEFT_AXIS_NEG_Y = BUTTON_UP;
		else
		gamepad.LEFT_AXIS_NEG_Y = BUTTON_IDLE;
	}
}