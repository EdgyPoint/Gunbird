#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;
	
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({0, 64, 32, 32});
	idle.PushBack({32, 64, 32, 32});
	idle.PushBack({64, 64, 32, 32});
	idle.PushBack({96, 64, 32, 32});
	idle.loop = true;
	idle.speed = 0.2f;

	// left animation (arcade sprite sheet)
	tleft.PushBack({ 0, 32, 32, 32 });
	tleft.PushBack({ 32, 32, 32, 32 });
	tleft.PushBack({ 64, 32, 32, 32 });
	tleft.PushBack({ 96, 32, 32, 32 });
	tleft.speed = 0.2f;

	left.PushBack({ 0, 0, 32, 32 });
	left.PushBack({ 32, 0, 32, 32 });
	left.PushBack({ 64, 0, 32, 32 });
	left.PushBack({ 96, 0, 32, 32 });
	left.loop = true;
	left.speed = 0.2f;

	tright.PushBack({ 0, 128, 32, 32 });
	tright.PushBack({ 32, 128, 32, 32 });
	tright.PushBack({ 64, 128, 32, 32 });
	tright.PushBack({ 96, 128, 32, 32 });
	tright.speed = 0.2f;

	right.PushBack({ 0, 96, 32, 32 });
	right.PushBack({ 32, 96, 32, 32 });
	right.PushBack({ 64, 96, 32, 32 });
	right.PushBack({ 96, 96, 32, 32 });
	right.loop = true;
	right.speed = 0.2f;
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

		if (current_animation != &left && transition >= TRANSITION_SPEED)
		{
			left.Reset();
			current_animation = &left;
		}
		if (current_animation != &tleft && transition < TRANSITION_SPEED)
		{
			current_animation = &tleft;
		}
		transition++;
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (position.x >= 196)
		{
			position.x = 196;
		}
		if (current_animation != &right && transition >= TRANSITION_SPEED)
		{
			right.Reset();
			current_animation = &right;
		}
		if (current_animation != &tright && transition < TRANSITION_SPEED)
		{
			current_animation = &tright;
		}
		transition++;
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

	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
	{
			App->particles->AddParticle(App->particles->marionbeam1, position.x + 11, position.y - 25);
		
			App->particles->AddParticle(App->particles->marionbeam2, position.x + 11, position.y - 25, 500);

			App->particles->AddParticle(App->particles->marionbeam3, position.x + 11, position.y - 25, 1000);

			App->particles->AddParticle(App->particles->marionbeam1, position.x + 11, position.y - 25, 1500);
	}
	
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
	{
		current_animation = &idle;
		transition = 0;
	}

	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}