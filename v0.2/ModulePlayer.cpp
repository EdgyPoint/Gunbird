#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({4, 64, 20, 32});
	idle.PushBack({36, 64, 20, 32});
	idle.PushBack({67, 64, 20, 32});
	idle.PushBack({100, 64, 20, 32});
	idle.loop = false;
	idle.speed = 0.2f;

	// left animation (arcade sprite sheet)
	left.PushBack({ 2, 32, 21, 32 });
	left.PushBack({ 34, 32, 21, 32 });
	left.PushBack({ 66, 32, 20, 32 });
	left.PushBack({ 98, 32, 21, 32 });

	left.PushBack({ 0, 0, 23, 32 });
	left.PushBack({ 32, 0, 23, 32 });
	left.PushBack({ 65, 0, 22, 32 });
	left.PushBack({ 96, 0, 23, 32 });
	idle.loop = false;
	left.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/images/Marion.png");

	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (position.x <= 0)
		{
			position.x = 0;
		}
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (position.x >= 203)
		{
			position.x = 203;
		}
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (position.y >= 288)
		{
			position.y = 288;
		}
	
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (position.y <= 0)
		{
			position.y = 0;
		}
	
	}

	// TODO 3: Shoot lasers when the player hits SPACE

	
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}