#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleItems.h"

#include "SDL/include/SDL_timer.h"

ModuleItems::ModuleItems()
{
}


ModuleItems::~ModuleItems()
{
}


bool ModuleItems::Start()
{
	LOG("Loading items");
	graphics = App->textures->Load("assets/images/particles.png"); 

	powerup.anim.PushBack({ 235, 423, 22, 13 });
	powerup.anim.PushBack({ 259, 423, 22, 13 });
	powerup.anim.PushBack({ 282, 423, 22, 13 });
	powerup.anim.PushBack({ 305, 423, 22, 13 });
	powerup.anim.PushBack({ 328, 423, 22, 13 });
	powerup.anim.PushBack({ 351, 423, 22, 13 });
	powerup.anim.PushBack({ 374, 423, 22, 13 });
	powerup.anim.PushBack({ 397, 423, 22, 13 });
	powerup.anim.loop = true;
	powerup.anim.speed = 0.3f;
	powerup.speed.x = 1;
	powerup.speed.y = 1;
	powerup.life = 20000;



	return true;
}

bool ModuleItems::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleItems::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_ITEMS; ++i)
	{
		Item* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			p = nullptr;
			active[i] = nullptr;
		}
	}
	return UPDATE_CONTINUE;
}



Item::Item()
{
	position.SetToZero();
	speed.SetToZero();
}

Item::Item(const Item& p) :
	anim(p.anim), position(p.position), speed(p.speed), born(p.born), life(p.life)
{}

Item::~Item()
{
	if (collider != nullptr)
		collider->to_delete = true;

}

bool Item::Update()
{
	bool ret = true;
	int aux = (SDL_GetTicks() - born);

	if (life > 0)
	{
		if (aux > (int)life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr && SDL_GetTicks() >= born)
		collider->SetPos(position.x, position.y);
	if (collider != nullptr && SDL_GetTicks() < born)
		collider->SetPos(-50, 500);
	return ret;
}

