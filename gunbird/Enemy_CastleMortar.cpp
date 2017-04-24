#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_CastleMortar.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_CastleMortar::Enemy_CastleMortar(int x, int y, int option) : Enemy(x, y, option)
{
		
	//enemy closed
	closed.PushBack({0, 140, 32, 32});
	closed.loop = false;
	status = NONE;

	//animation when the mortar opens
	opening.PushBack({34, 140, 32, 32});
	opening.PushBack({68, 140, 32, 32});
	opening.PushBack({102, 140, 32, 32});
	opening.PushBack({137, 140, 32, 32 });
	opening.PushBack({ 0, 174, 32, 32 });
	opening.loop = false;
	opening.speed = 0.1f;
	

	//animation when the mortar is being shot while opening
	opening2.PushBack({ 0, 140, 32, 32 });
	opening2.PushBack({ 0, 208, 32, 32 });
	opening2.PushBack({ 34, 140, 32, 32 });
	opening2.PushBack({ 34, 208, 32, 32 });
	opening2.loop = false;
	opening2.speed = 0.175f;

	//animation when the mortar has opened and is shooting
	stand.PushBack({ 34, 174, 32, 32 });
	stand.PushBack({ 68, 174, 32, 32 });
	stand.PushBack({ 102, 174, 32, 32 });
	stand.PushBack({ 137, 174, 32, 32 });
	stand.loop = true;
	stand.speed = 0.175f;

	//animation when the mortar is being shot while is active
	stand2.PushBack({ 34, 208, 32, 32 });
	stand2.PushBack({ 68, 208, 32, 32 });
	stand2.PushBack({ 102, 208, 32, 32 });
	stand2.PushBack({ 137, 208, 32, 32 });
	stand2.loop = true;
	stand2.speed = 0.175f;
	
	//animation when the mortar is damaged
	stand3.PushBack({ 34, 174, 32, 32 });
	stand3.PushBack({ 34, 242, 32, 32 });
	stand3.PushBack({ 68, 174, 32, 32 });
	stand3.PushBack({ 68, 242, 32, 32 });
	stand3.PushBack({ 102, 174, 32, 32 });
	stand3.PushBack({ 102, 242, 32, 32 });
	stand3.PushBack({ 137, 174, 32, 32 });
	stand3.PushBack({ 137, 242, 32, 32 });
	stand3.loop = true;
	stand3.speed = 0.175f;

	
	animation = &closed;
	

	collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.55f }, 1000);

	original_pos.x = x;
	original_pos.y = y;
	
	hp = 20.0f;
	damaged_hp = 8;
	death_type = SMALL_ENEMY;
	flying = false;
	killscore = 4000;
}

void Enemy_CastleMortar::Move()
{
	position = original_pos + path.GetCurrentPosition();

	if (status == OPENING || status == NONE)
		collider->type = COLLIDER_NONE;
	if (status == NORMAL)
		collider->type = COLLIDER_ENEMY;

	if (position.y == -20) { animation = &opening; status = OPENING; }
	if (status == OPENING && animation->Finished() == true) { status = NORMAL; }
	if (status == NORMAL) { animation = &stand; }
	if (status == HIT && animation == &opening) { animation = &opening2; }
	if (status == HIT) { animation = &stand2; }
	if (status == DAMAGED) { animation = &stand3; }
	}

void Enemy_CastleMortar::Shoot()
{
	initcounter += 1;
	if (initcounter > 210 && initcounter < 500)
	{
			if (SDL_GetTicks() >= reload[0] && status != OPENING && status != NONE)//first wave
			{
				//App->particles->AddParticle(App->particles->prebigshot, position.x + 7, position.y + 5, COLLIDER_ENEMY_SHOT, 0, 0, false); 
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -1, -1);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 1, -1);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -1, 1);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 1, 1);

				reload[0] = SDL_GetTicks() + 1500;
				reload[1] = SDL_GetTicks() + 200;
				reload[2] = SDL_GetTicks() + 400;
			}

			if (SDL_GetTicks() >= reload[1] && status != OPENING && status != NONE)
			{
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 1.05, 0.35);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -1.25, 0.6);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -0.4, -0.7);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 0.3, 1.6);

				reload[1] = SDL_GetTicks() + 1300;
			}

			if (SDL_GetTicks() >= reload[2] && status != OPENING && status != NONE)
			{
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -1.25, 0.1);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 1.05, 0.6);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, 0.3, -0.6);
				App->particles->AddParticle(App->particles->bigshot, position.x + 10, position.y + 10, COLLIDER_ENEMY_SHOT, -0.3, 1.6);

				reload[2] = SDL_GetTicks() + 1100;
			}
	}

}
