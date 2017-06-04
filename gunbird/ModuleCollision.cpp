#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;


	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_CHARGEDSHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_CHARGEDSHOT2] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_WALL][COLLIDER_COIN] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOMBSHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_BOMBSHOT2] = true;
	matrix[COLLIDER_WALL][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOMB] = false;
	
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_COIN] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB] = true;

	matrix[COLLIDER_PLAYER2][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_COIN] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOMB] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_CHARGEDSHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_WALL] = true;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_COIN] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_CHARGEDSHOT2][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_CHARGEDSHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_CHARGEDSHOT2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_COIN] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMBSHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMBSHOT2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY_F][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_CHARGEDSHOT] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_CHARGEDSHOT2] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_COIN] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_BOMBSHOT] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_BOMBSHOT2] = true;
	matrix[COLLIDER_ENEMY_F][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_ENEMY_F][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMBCLEAN] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_POWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_COIN] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_BOMB] = false;

	matrix[COLLIDER_COIN][COLLIDER_WALL] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_COIN][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_COIN][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_COIN][COLLIDER_COIN] = false;
	matrix[COLLIDER_COIN][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_COIN][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_COIN][COLLIDER_BOMB] = false;

	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMBSHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_BOMBSHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMBSHOT2][COLLIDER_WALL] = true;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_ENEMY_F] = true;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_COIN] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_BOMBSHOT2][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMBCLEAN][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_COIN] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_BOMBCLEAN][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_F] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_CHARGEDSHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_CHARGEDSHOT2] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BOMB][COLLIDER_COIN] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMBSHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMBSHOT2] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMBCLEAN] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
			
		}
	}
	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if ((App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN ) && !App->fade->fading)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, 0);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER2: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 180, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ENEMY_F: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER2_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_CHARGEDSHOT: // darker yellow
			App->render->DrawQuad(colliders[i]->rect, 100, 100, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_POWERUP: // purple
			App->render->DrawQuad(colliders[i]->rect, 138, 0, 255, alpha);
			break;
		case COLLIDER_COIN: // golden
			App->render->DrawQuad(colliders[i]->rect, 151, 120, 11, alpha);
			break;
		case COLLIDER_BOMBSHOT: // dark yellow
			App->render->DrawQuad(colliders[i]->rect, 200, 200, 0, alpha);
			break;
		case COLLIDER_BOMBCLEAN: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}
void ModuleCollision::EditMatrix(COLLIDER_TYPE col_type1, COLLIDER_TYPE col_type2, bool state)
{
	matrix[col_type1][col_type2] = state;
}


bool ModuleCollision::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------
bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x + rect.w >= r.x && rect.x <= r.x + r.w && rect.y + rect.h >= r.y && rect.y < r.y + r.h);
}