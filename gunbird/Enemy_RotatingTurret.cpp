#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Enemy_RotatingTurret.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>



Enemy_RotatingTurret::Enemy_RotatingTurret(int x, int y, int option) : Enemy(x, y, option)
{

	aditionalanimation = true;
	
	//normal base animation
	normal_base_anim.PushBack({ 506, 250, 28, 35 });
	normal_base_anim.PushBack({ 536, 249, 28, 36 });
	normal_base_anim.PushBack({ 566, 250, 28, 35 });
	normal_base_anim.PushBack({ 596, 249, 28, 36 });
	normal_base_anim.PushBack({ 626, 250, 28, 35 });
	normal_base_anim.PushBack({ 656, 250, 28, 35 }); 
	normal_base_anim.loop = true;
	normal_base_anim.speed = 0.2f;

	//hit base animation
	hit_base_anim.PushBack({ 506, 311, 28, 35 });
	hit_base_anim.PushBack({ 536, 310, 28, 36 });
	hit_base_anim.PushBack({ 566, 311, 28, 35 });
	hit_base_anim.PushBack({ 596, 310, 28, 36 });
	hit_base_anim.PushBack({ 626, 311, 28, 35 });
	hit_base_anim.PushBack({ 656, 311, 28, 35 });
	hit_base_anim.loop = true;
	hit_base_anim.speed = 0.6f;

	//damaged base animation
	damaged_base_anim.PushBack({ 506, 250, 28, 35 });
	damaged_base_anim.PushBack({ 536, 249, 28, 36 });
	damaged_base_anim.PushBack({ 566, 250, 28, 35 });
	damaged_base_anim.PushBack({ 596, 249, 28, 36 });
	damaged_base_anim.PushBack({ 626, 250, 28, 35 });
	damaged_base_anim.PushBack({ 656, 250, 28, 35 });
	damaged_base_anim.loop = true;
	damaged_base_anim.speed = 0.6f;


	down.PushBack({ 506, 369, 27, 32 });

	downr1.PushBack({ 536, 369, 27, 32 });

	downr2.PushBack({ 566, 369, 27, 32 });

	downr3.PushBack({ 596, 369, 27, 32 });

	downr4.PushBack({ 626, 369, 27, 32 });

	downr5.PushBack({ 656, 369, 27, 32 });

	downr6.PushBack({ 686, 369, 27, 32 });

	downr7.PushBack({ 716, 369, 27, 32 });

	right.PushBack({ 747, 369, 27, 32 });

	rightu1.PushBack({ 506, 404, 27, 32 });

	rightu2.PushBack({ 536, 404, 27, 32 });

	rightu3.PushBack({ 566, 404, 27, 32 });

	rightu4.PushBack({ 596, 404, 27, 32 });

	rightu5.PushBack({ 626, 404, 27, 32 });

	up.PushBack({ 656, 404, 27, 32 });

	upl1.PushBack({ 686, 404, 27, 32 });

	upl2.PushBack({ 716, 404, 27, 32 });

	upl3.PushBack({ 747, 404, 27, 32 });

	upl4.PushBack({ 503, 441, 27, 32 });

	upl5.PushBack({ 532, 441, 27, 32 });

	upl6.PushBack({ 561, 441, 27, 32 });

	downr1.PushBack({ 591, 441, 27, 32 });

	downr1.PushBack({ 622, 441, 27, 32 });

	downr1.PushBack({ 652, 441, 27, 32 });

	downr1.PushBack({ 682, 441, 27, 32 });

	downr1.PushBack({ 712, 441, 27, 32 });

	downr1.PushBack({ 743, 441, 27, 32 });

	downr1.PushBack({ 502, 479, 27, 32 });

	
	collider = App->collision->AddCollider({ 0, 0, 28, 36 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &normal_base_anim;

	aditional_animation = &down;

	path.PushBack({ 0.0f, 0.4f }, 10000);

	original_pos.x = x;
	original_pos.y = y;

	hp = 2.0f;

	death_type = SMALL_ENEMY;
	flying = false;
	killscore = 500;
}

void Enemy_RotatingTurret::Move()
{
	position = original_pos + path.GetCurrentPosition();
	
	if (status == NORMAL) { animation = &normal_base_anim; }
	if (status == HIT) { animation = &hit_base_anim; }
	if (status == DAMAGED) { animation = &damaged_base_anim; }
	
}

void Enemy_RotatingTurret::Extra_animation()
{
	if (status == NORMAL)
	{
		App->render->Blit(App->enemies->sprites, position.x + 4, position.y - 5, &down.GetCurrentFrame());
		//flag2.GetCurrentFrame();
		//flag3.GetCurrentFrame();
	}
	/*if (status == HIT)
	{
		App->render->Blit(App->enemies->sprites, position.x + 29, position.y - 15, &flag2.GetCurrentFrame());
		flag.GetCurrentFrame();
		flag3.GetCurrentFrame();
	}

	if (status == DAMAGED)
	{
		App->render->Blit(App->enemies->sprites, position.x + 29, position.y - 15, &flag3.GetCurrentFrame());
		flag.GetCurrentFrame();
		flag2.GetCurrentFrame();
	}*/

}
void Enemy_RotatingTurret::Shoot()
{

}