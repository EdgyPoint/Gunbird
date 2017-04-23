#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_CastleMortar.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_CastleMortar::Enemy_CastleMortar(int x, int y, int option) : Enemy(x, y, option)
{
	
		stand.PushBack({ 0, 140, 32, 32 });
		stand.PushBack({ 34, 140, 32, 32 });
		stand.PushBack({ 68, 140, 32, 32 });
		stand.PushBack({ 102, 140, 32, 32 });
		/*stand.PushBack({ 212, 140, 32, 32 });
		stand.PushBack({ 159, 140, 32, 32 });
		stand.PushBack({ 212, 140, 32, 32 });*/
		stand.speed = 0.3f;
		
	
	animation = &stand;

	collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.55f }, 10000);

	original_pos.x = x;
	original_pos.y = y;
	
	hp = 20.0f;
	damaged_hp = 8;
	death_type = SMALL_ENEMY;
	flying = false;
}

void Enemy_CastleMortar::Move()
{
	position = original_pos + path.GetCurrentPosition();
}

void Enemy_CastleMortar::Shoot()
{
	initcounter += 1;
	if (initcounter > 210 && initcounter < 500)
	{
		if (SDL_GetTicks() >= reload)//first wave
		{
			App->particles->AddParticle(App->particles->prebigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, 0, 0, true);
			 
			App->particles->AddParticle(App->particles->bigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, -2, -2); 
			App->particles->AddParticle(App->particles->bigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, 2, -2); 
			App->particles->AddParticle(App->particles->bigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, -2, 2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, 2, 2);
			reload = SDL_GetTicks() + 1000;
		}

		if (SDL_GetTicks() >= reload)//second wave
		{
			App->particles->AddParticle(App->particles->prebigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, 0, 0, true);
		
			App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -2, -2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 32, position.y, COLLIDER_ENEMY_SHOT, 2, -2);
			App->particles->AddParticle(App->particles->bigshot, position.x, position.y + 32, COLLIDER_ENEMY_SHOT, -2, 2);
			App->particles->AddParticle(App->particles->bigshot, position.x + 32, position.y + 32, COLLIDER_ENEMY_SHOT, 2, 2);
			reload = SDL_GetTicks() + 1000;
		}
		
	}

}
