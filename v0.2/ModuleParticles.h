#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	int apperance = 0;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, float speed_x = 0.0f, float speed_y = 0.0f, Uint32 delay = 0, bool using_camera = true);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	Particle marionbeam_lv1[3];
	Particle marionbeam_lv2[3];
	Particle smallshot;
	Particle prebigshot;
	Particle bigshot;
	Particle powerup;
	Particle magicspark[4];
	Particle impact;
	Particle small_explosion;
	Particle medium_explosion;
	Particle playercollision;
	Particle playerstunned;
};

#endif // __MODULEPARTICLES_H__