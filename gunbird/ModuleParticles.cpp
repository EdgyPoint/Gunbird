#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Init()
{

	marionbeam_lv1[0].anim.PushBack({ 150, 60, 30, 30 });
	marionbeam_lv1[0].anim.loop = false;
	marionbeam_lv1[0].anim.speed = 0.3f;
	marionbeam_lv1[0].speed.y = -10;
	marionbeam_lv1[0].life = 4000;

	marionbeam_lv1[1].anim.PushBack({ 150, 90, 30, 30 });
	marionbeam_lv1[1].anim.loop = false;
	marionbeam_lv1[1].anim.speed = 0.3f;
	marionbeam_lv1[1].speed.y = -10;
	marionbeam_lv1[1].life = 4000;

	marionbeam_lv1[2].anim.PushBack({ 150, 120, 30, 30 });
	marionbeam_lv1[2].anim.loop = false;
	marionbeam_lv1[2].anim.speed = 0.3f;
	marionbeam_lv1[2].speed.y = -10;
	marionbeam_lv1[2].life = 4000;

	marionbeam_lv2[0].anim.PushBack({ 180, 60, 30, 30 });
	marionbeam_lv2[0].anim.loop = false;
	marionbeam_lv2[0].anim.speed = 0.3f;
	marionbeam_lv2[0].speed.y = -10;
	marionbeam_lv2[0].life = 4000;

	marionbeam_lv2[1].anim.PushBack({ 180, 90, 30, 30 });
	marionbeam_lv2[1].anim.loop = false;
	marionbeam_lv2[1].anim.speed = 0.3f;
	marionbeam_lv2[1].speed.y = -10;
	marionbeam_lv2[1].life = 4000;

	marionbeam_lv2[2].anim.PushBack({ 180, 120, 30, 30 });
	marionbeam_lv2[2].anim.loop = false;
	marionbeam_lv2[2].anim.speed = 0.3f;
	marionbeam_lv2[2].speed.y = -10;
	marionbeam_lv2[2].life = 4000;

	marionbeamleft_lv1[0].anim.PushBack({ 210, 60, 30, 30 });
	marionbeamleft_lv1[0].anim.loop = false;
	marionbeamleft_lv1[0].anim.speed = 0.3f;
	marionbeamleft_lv1[0].speed.y = -10;
	marionbeamleft_lv1[0].life = 4000;

	marionbeamleft_lv1[1].anim.PushBack({ 210, 90, 30, 30 });
	marionbeamleft_lv1[1].anim.loop = false;
	marionbeamleft_lv1[1].anim.speed = 0.3f;
	marionbeamleft_lv1[1].speed.y = -10;
	marionbeamleft_lv1[1].life = 4000;

	marionbeamleft_lv1[2].anim.PushBack({ 210, 120, 30, 30 });
	marionbeamleft_lv1[2].anim.loop = false;
	marionbeamleft_lv1[2].anim.speed = 0.3f;
	marionbeamleft_lv1[2].speed.y = -10;
	marionbeamleft_lv1[2].life = 4000;

	marionbeamleft_lv2[0].anim.PushBack({ 270, 60, 30, 30 });
	marionbeamleft_lv2[0].anim.loop = false;
	marionbeamleft_lv2[0].anim.speed = 0.3f;
	marionbeamleft_lv2[0].speed.y = -10;
	marionbeamleft_lv2[0].life = 4000;

	marionbeamleft_lv2[1].anim.PushBack({ 270, 90, 30, 30 });
	marionbeamleft_lv2[1].anim.loop = false;
	marionbeamleft_lv2[1].anim.speed = 0.3f;
	marionbeamleft_lv2[1].speed.y = -10;
	marionbeamleft_lv2[1].life = 4000;

	marionbeamleft_lv2[2].anim.PushBack({ 270, 120, 30, 30 });
	marionbeamleft_lv2[2].anim.loop = false;
	marionbeamleft_lv2[2].anim.speed = 0.3f;
	marionbeamleft_lv2[2].speed.y = -10;
	marionbeamleft_lv2[2].life = 4000;

	marionbeamright_lv1[0].anim.PushBack({ 240, 60, 30, 30 });
	marionbeamright_lv1[0].anim.loop = false;
	marionbeamright_lv1[0].anim.speed = 0.3f;
	marionbeamright_lv1[0].speed.y = -10;
	marionbeamright_lv1[0].life = 4000;

	marionbeamright_lv1[1].anim.PushBack({ 240, 90, 30, 30 });
	marionbeamright_lv1[1].anim.loop = false;
	marionbeamright_lv1[1].anim.speed = 0.3f;
	marionbeamright_lv1[1].speed.y = -10;
	marionbeamright_lv1[1].life = 4000;

	marionbeamright_lv1[2].anim.PushBack({ 240, 120, 30, 30 });
	marionbeamright_lv1[2].anim.loop = false;
	marionbeamright_lv1[2].anim.speed = 0.3f;
	marionbeamright_lv1[2].speed.y = -10;
	marionbeamright_lv1[2].life = 4000;

	marionbeamright_lv2[0].anim.PushBack({ 300, 60, 30, 30 });
	marionbeamright_lv2[0].anim.loop = false;
	marionbeamright_lv2[0].anim.speed = 0.3f;
	marionbeamright_lv2[0].speed.y = -10;
	marionbeamright_lv2[0].life = 4000;

	marionbeamright_lv2[1].anim.PushBack({ 300, 90, 30, 30 });
	marionbeamright_lv2[1].anim.loop = false;
	marionbeamright_lv2[1].anim.speed = 0.3f;
	marionbeamright_lv2[1].speed.y = -10;
	marionbeamright_lv2[1].life = 4000;

	marionbeamright_lv2[2].anim.PushBack({ 300, 120, 30, 30 });
	marionbeamright_lv2[2].anim.loop = false;
	marionbeamright_lv2[2].anim.speed = 0.3f;
	marionbeamright_lv2[2].speed.y = -10;
	marionbeamright_lv2[2].life = 4000;

	smallshot.anim.PushBack({ 31, 425, 6, 6 });
	smallshot.anim.PushBack({ 47, 425, 6, 6 });
	smallshot.anim.PushBack({ 79, 425, 6, 6 });
	smallshot.anim.PushBack({ 111, 425, 6, 6 });
	smallshot.anim.PushBack({ 143, 425, 6, 6 });
	smallshot.anim.PushBack({ 191, 425, 6, 6 });
	smallshot.anim.PushBack({ 15, 441, 6, 6 });
	smallshot.anim.PushBack({ 47, 441, 6, 6 });
	smallshot.anim.loop = true;
	smallshot.anim.speed = 0.3f;
	smallshot.speed.y = 3;
	smallshot.life = 4000;

	presmallshot.anim.PushBack({ 0, 424, 8, 8 });
	presmallshot.anim.PushBack({ 8, 424, 8, 8 });
	smallshot.anim.loop = true;
	presmallshot.anim.speed = 0.3f;
	presmallshot.life = 1;

	//First two frames of the mortar shot
	prebigshot.anim.PushBack({ 23, 388, 16, 16 }); 
	prebigshot.anim.PushBack({ 47, 387, 19, 19 }); 
	prebigshot.anim.loop = false;
	prebigshot.anim.speed = 1;
	prebigshot.speed.y = 0.55f;
	prebigshot.life = 400;

	//Mortar shot
	bigshot.anim.PushBack({ 74, 391, 12, 12 });
	bigshot.anim.PushBack({ 96, 391, 12, 12 });
	bigshot.anim.PushBack({ 118, 391, 12, 12 });
	bigshot.anim.loop = true;
	bigshot.anim.speed = 0.55f;
	bigshot.speed.y = 3;
	bigshot.life = 4000;
	
	//coin
	coin.anim.PushBack({ 234, 362, 16, 16 });
	coin.anim.PushBack({ 256, 362, 16, 16 });
	coin.anim.PushBack({ 282, 362, 16, 16 });
	coin.anim.PushBack({ 310, 362, 16, 16 });
	coin.anim.PushBack({ 234, 388, 16, 16 });
	coin.anim.PushBack({ 256, 388, 16, 16 });
	coin.anim.PushBack({ 282, 388, 16, 16 });
	coin.anim.PushBack({ 310, 388, 16, 16 });
	coin.anim.loop = true;
	coin.life = 10000;
	coin.anim.speed = 0.25f;


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

	impact.anim.PushBack({448, 768, 16, 42});
	impact.anim.PushBack({464, 768, 16, 42 });
	impact.anim.PushBack({480, 768, 16, 42 });
	impact.anim.PushBack({496, 768, 16, 42 });
	impact.anim.PushBack({512, 768, 16, 42 });
	impact.anim.PushBack({528, 768, 16, 42 });
	impact.anim.PushBack({544, 768, 16, 42 });
	impact.anim.PushBack({560, 768, 16, 42 });
	impact.anim.PushBack({576, 768, 16, 42 });
	impact.anim.PushBack({592, 768, 16, 42 });
	impact.anim.PushBack({608, 768, 16, 42 });
	impact.anim.PushBack({448, 810, 16, 42});
	impact.anim.PushBack({464, 810, 16, 42 });
	impact.anim.PushBack({480, 810, 16, 42 });
	impact.anim.PushBack({496, 810, 16, 42 });
	impact.anim.PushBack({512, 810, 16, 42 });
	impact.anim.PushBack({528, 810, 16, 42 });
	impact.anim.PushBack({544, 810, 16, 42 });
	impact.anim.PushBack({560, 810, 16, 42 });
	impact.anim.PushBack({576, 810, 16, 42 });
	impact.anim.PushBack({592, 810, 16, 42 });
	impact.anim.loop = false;
	impact.anim.speed = 0.5f;
	impact.life = 500;


	small_explosion.anim.PushBack({0, 768, 56, 64});
	small_explosion.anim.PushBack({56, 768, 56, 64});
	small_explosion.anim.PushBack({112, 768, 56, 64 });
	small_explosion.anim.PushBack({168, 768, 56, 64 });
	small_explosion.anim.PushBack({224, 768, 56, 64 });
	small_explosion.anim.PushBack({280, 768, 56, 64 });
	small_explosion.anim.PushBack({336, 768, 56, 64 });
	small_explosion.anim.PushBack({392, 768, 56, 64 });
	small_explosion.anim.PushBack({0, 832, 56, 64});
	small_explosion.anim.PushBack({56, 832, 56, 64 });
	small_explosion.anim.PushBack({112, 832, 56, 64 });
	small_explosion.anim.PushBack({168, 832, 56, 64 });
	small_explosion.anim.PushBack({224, 832, 56, 64 });
	small_explosion.anim.PushBack({280, 832, 56, 64 });
	small_explosion.anim.PushBack({336, 832, 56, 64 });
	small_explosion.anim.loop = false;
	small_explosion.anim.speed = 0.5f;
	small_explosion.life = 500;

	medium_explosion.anim.PushBack({ 0, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 106, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 212, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 318, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 424, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 530, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 0, 593, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 106, 593, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 212, 593, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 318, 593, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 424, 593, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.PushBack({ 530, 593, 106, 106 });
	medium_explosion.anim.PushBack({ 636, 477, 106, 106 });
	medium_explosion.anim.loop = false;
	medium_explosion.anim.speed = 0.5f;
	medium_explosion.life = 1000;

	playercollision.anim.PushBack({ 0, 896, 31, 31 });
	playercollision.anim.PushBack({ 31, 896, 31, 31 });
	playercollision.anim.PushBack({ 62, 896, 31, 31 });
	playercollision.anim.PushBack({ 93, 896, 31, 31 });
	playercollision.anim.PushBack({ 124, 896, 31, 31 });
	playercollision.anim.PushBack({ 155, 896, 31, 31 });
	playercollision.anim.PushBack({ 186, 896, 31, 31 });
	playercollision.anim.PushBack({ 217, 896, 31, 31 });
	playercollision.anim.PushBack({ 248, 896, 31, 31 });
	playercollision.anim.loop = false;
	playercollision.anim.speed = 0.5f;
	playercollision.life = 450;

	playerstunned.anim.PushBack({ 279, 896, 28, 20});
	playerstunned.anim.PushBack({ 307, 896, 28, 20 });
	playerstunned.anim.PushBack({ 335, 896, 28, 20 });
	playerstunned.anim.PushBack({ 363, 896, 28, 20 });
	playerstunned.anim.PushBack({ 391, 896, 28, 20 });
	playerstunned.anim.PushBack({ 419, 896, 28, 20 });
	playerstunned.anim.PushBack({ 447, 896, 28, 20 });
	playerstunned.anim.loop = true;
	playerstunned.anim.speed = 0.5f;
	playerstunned.life = 1000;

	magicspark[0].anim.PushBack({ 168, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 183, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 198, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 213, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 228, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 243, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 258, 0, 11, 11 });
	magicspark[0].anim.PushBack({ 273, 0, 11, 11 });
	magicspark[0].anim.loop = false;
	magicspark[0].anim.speed = 0.33f;
	magicspark[0].speed.y = 1.0f;
	magicspark[0].life = 300;

	magicspark[1].anim.PushBack({ 168, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 183, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 198, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 213, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 228, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 243, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 258, 15, 11, 11 });
	magicspark[1].anim.PushBack({ 273, 15, 11, 11 });
	magicspark[1].anim.loop = false;
	magicspark[1].anim.speed = 0.33f;
	magicspark[1].speed.y = 1.0f;
	magicspark[1].life = 300;

	magicspark[2].anim.PushBack({ 168, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 183, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 198, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 213, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 228, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 243, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 258, 30, 11, 11 });
	magicspark[2].anim.PushBack({ 273, 30, 11, 11 });
	magicspark[2].anim.loop = false;
	magicspark[2].anim.speed = 0.33f;
	magicspark[2].speed.y = 1.0f;
	magicspark[2].life = 300;

	magicspark[3].anim.PushBack({ 168, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 183, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 198, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 213, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 228, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 243, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 258, 45, 11, 11 });
	magicspark[3].anim.PushBack({ 273, 45, 11, 11 });
	magicspark[3].anim.loop = false;
	magicspark[3].anim.speed = 0.33f;
	magicspark[3].speed.y = 1.0f;
	magicspark[3].life = 300;

	powerupscore.anim.PushBack({ 44, 0, 15, 7 });
	powerupscore.anim.PushBack({ 44, 7, 15, 7 });
	powerupscore.anim.loop = true;
	powerupscore.anim.speed = 0.1f;
	powerupscore.life = 1000;

	return true;
}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/images/particles.png");
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
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

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), false);
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}


	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, float speed_x, float speed_y, Uint32 delay,  bool using_camera, ITEM_TYPE item_type)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			
			if(speed_x != 0)
			p->speed.x = speed_x;
			if(speed_y != 0)
			p->speed.y = speed_y;

			p->aux = p->anim.GetCurrentFrame();
			p->aux.x = x;
			p->aux.y = y;

			p->position.x = x;
			p->position.y = y;
			p->collider = App->collision->AddCollider(p->aux, collider_type, this);
			p->itemtype = item_type;
			active[i] = p;
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
	
}

bool Particle::Update()
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

	if (itemtype == ITEM_POWERUP)

	{
		if (position.x < 10 || position.x > 192)
		{
			speed.x = speed.x * -1;
		}
		if (position.y < 45 || position.y > 222)
		{
			speed.y = speed.y * -1;
		}
	}

	if (collider != nullptr && SDL_GetTicks() >= born)
		collider->SetPos(position.x, position.y);
	if (collider != nullptr && SDL_GetTicks() < born)
		collider->SetPos(-50, 500);
	return ret;
}

