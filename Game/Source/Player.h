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

	void Restart();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Physic Functions
	void AccFromForce();
	void VelFromAcc();
	void PosFromVel();

	// Position of the player in the map
	Vec2 playerPos;
	Vec2 playerVel;
	Vec2 playerAcc;

	//Direction, 1 right, 0 left;	
	bool direction;
	int mass;

	SDL_Rect playerRect;
	
	
	// The player spritesheet loaded into an SDL_Texture
	SDL_Rect winScreenRect;
	SDL_Texture* playerWinScreen;

	//TEMPORARY WHILE WE DON'T HAVE ENEMY MODULE
	SDL_Texture* enemyWinScreen;

	//Forces
	float gravity;
	float playerFriction;
	Vec2 playerImpulse;
	
	bool gameEnd;
	bool playerLose;
};