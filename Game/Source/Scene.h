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

	//Ground Positions and Colliders
	SDL_Rect battlefield;
	Vec2 battlefieldPos;

	SDL_Rect battlefieldUp;
	SDL_Rect battlefieldRight;
	SDL_Rect battlefieldLeft;
	
	int battlefieldWidth;
	int battlefieldHeight;

	Collider* battlefieldCol;

	Collider* battlefieldUpCol;
	Collider* battlefieldRightCol;
	Collider* battlefieldLeftCol;

	//Right Wall Positions and Colliders
	SDL_Rect rightWall;
	Vec2 rightWallPos;

	Collider* rightWallCol;

	SDL_Rect rightWallNearRect;
	Collider* rightWallNearCol;

	//Left Wall Positions and Colliders
	SDL_Rect leftWall;
	Vec2 leftWallPos;

	Collider* leftWallCol;

	SDL_Rect leftWallNearRect;
	Collider* leftWallNearCol;

	int wallWidth;
	int wallHeight;	

	bool right;
	bool left;
	bool down;
	bool up;

	bool seeCols;

private:
	SDL_Texture* img;
};

#endif // __SCENE_H__