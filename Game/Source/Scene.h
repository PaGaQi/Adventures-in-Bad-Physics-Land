#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Render.h"
#include "Textures.h"
#include "Defs.h"

struct SDL_Texture;

class Scene : public Module
{
public:
	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	SDL_Rect battlefield;
	Vec2 battlefieldPos;

	SDL_Rect battlefieldUp;
	SDL_Rect battlefieldRight;
	SDL_Rect battlefieldLeft;
	
	int battlefieldWidth;
	int battlefieldHeight;

	SDL_Rect wallRight;
	Vec2 wallRightPos;

	SDL_Rect wallLeft;
	Vec2 wallLeftPos;

	int wallWidth;
	int wallHeight;

	Collider* near_up;
	Collider* near_down;
	Collider* near_right;
	Collider* near_left;

	Collider* battlefieldCol;

	Collider* battlefieldUpCol;
	Collider* battlefieldRightCol;
	Collider* battlefieldLeftCol;

	bool right;
	bool left;
	bool down;
	bool up;

private:
	SDL_Texture* img;
};

#endif // __SCENE_H__