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
	idle.PushBack({4, 62, 20, 32});
	idle.PushBack({34, 62, 21, 32});
	idle.PushBack({66, 62, 20, 32});
	idle.PushBack({98, 62, 21, 32});
	idle.speed = 0.2f;

	// left animation (arcade sprite sheet)
	left.PushBack({ 2, 32, 21, 32 });
	left.PushBack({ 34, 32, 21, 32 });
	left.PushBack({ 66, 32, 20, 32 });
	left.PushBack({ 98, 32, 21, 32 });

	left.PushBack({ 4, 62, 20, 32 });
	left.PushBack({ 34, 62, 21, 32 });
	left.PushBack({ 66, 62, 20, 32 });
	left.PushBack({ 98, 62, 21, 32 });
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

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	// TODO 3: Shoot lasers when the player hits SPACE

	
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}