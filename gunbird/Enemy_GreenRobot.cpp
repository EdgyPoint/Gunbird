//#include "Application.h"
//#include "ModuleParticles.h"
//#include "Enemy_GreenRobot.h"
//#include "ModulePlayer.h"
//#include "ModuleCollision.h"
//#include "SDL/include/SDL_timer.h"
//#include <cmath>
//
//
//
//Enemy_GreenRobot::Enemy_GreenRobot(int x, int y, int option) : Enemy(x, y, option)
//{
//
//
//	path.PushBack({ -0.1f, -0.7f }, 100);
//	path.PushBack({ -0.1f, 0.7f }, 200);
//	path.PushBack({ -0.1f, 1.2f }, 200);
//
//	collider = App->collision->AddCollider({ 0, 0, 32, 35 }, COLLIDER_TYPE::COLLIDER_ENEMY_F, (Module*)App->enemies);
//
//	original_pos.x = x;
//	original_pos.y = y;
//
//	hp = 87.0f;
//
//	death_type = MEDIUM_ENEMY;
//	flying = false;
//	killscore = 4000;
//}
//
//void Enemy_GreenRobot::Move()
//{
//
//}