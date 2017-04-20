#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_House1.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"




Enemy_House1::Enemy_House1(int x, int y, int option) : Enemy(x, y, option)
{
	aditionalanimation = true;

	fly.PushBack({ 220, 58, 64, 86 });
	
	flag.PushBack({ 354, 94, 64, 21 });
	flag.PushBack({ 354, 120, 66, 21 });
	flag.PushBack({ 354, 145, 66, 20 });
	flag.PushBack({ 354, 170, 65, 21 });
	flag.PushBack({ 354, 195, 64, 21 });
	flag.PushBack({ 429, 97, 66, 20 });
	flag.PushBack({ 430, 126, 65, 21 });
	flag.PushBack({ 430, 153, 65, 21 });
	flag.loop = true;
	flag.speed = 0.2f;

	collider = App->collision->AddCollider({ 0, 0, 64, 86 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &fly;

	aditional_animation = &flag;


	path.PushBack({ 0.0f, 0.55f }, 10000);
	original_pos.x = x;
	original_pos.y = y;

	hp = 10.0f;
}

void Enemy_House1::Move()
{
	position = original_pos + path.GetCurrentPosition();
}
void Enemy_House1::Extra_animation()
{
	App->render->Blit(App->enemies->sprites, position.x+30, position.y-12, &flag.GetCurrentFrame());
}
