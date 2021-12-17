#include "Module.h"
#include "SDL/include/SDL.h"
#include "Defs.h"

class Player : public Module
{
public:

	Player();

	// Destructor
	virtual ~Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Physic Functions
	void VelFromAcc(Vec2* acc, Vec2* vel);
	void PosFromVel(Vec2* vel, Vec2* pos);

	// Position of the player in the map
	Vec2 playerPos;
	Vec2 playerVel;
	Vec2 playerAcc;

	//Direction, 1 right, 0 left;	
	bool direction;
	int mass;

	SDL_Rect playerRect;
	

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* playerSprites = nullptr;

	//Forces
	int gravity;
	float drag;
	
};