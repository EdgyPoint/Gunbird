#ifndef __ModuleItems_H__
#define __ModuleItems_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_ITEMS 50

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Item
{
	Collider* collider = nullptr;
	Animation anim;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	int apperance = 0;

	Item();
	Item(const Item& p);
	~Item();
	bool Update();
};

class ModuleItems : public Module
{ 
public:

	ModuleItems();
	~ModuleItems();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	SDL_Texture* graphics = nullptr;
	Item* active[MAX_ACTIVE_ITEMS];
	uint last_particle = 0;

public:

	Item powerup;
	Item coin;
};

#endif // __ModuleInput_H__
