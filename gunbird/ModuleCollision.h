#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 500

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_PLAYER2,
	COLLIDER_ENEMY,
	COLLIDER_ENEMY_F,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_PLAYER2_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWERUP,
	COLLIDER_COIN,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	bool already_hit = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void EditMatrix(COLLIDER_TYPE col_type1, COLLIDER_TYPE col_type2, bool state);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__