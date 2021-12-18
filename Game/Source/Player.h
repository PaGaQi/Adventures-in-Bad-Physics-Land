#include "Module.h"
#include "SDL/include/SDL.h"
#include "Defs.h"
#include "App.h"
#include "Collisions.h"
#include "Collider.h"

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

	void ImpulseToMouse(int lastMouseX, int lastMouseY);

	void OnCollision(Collider* c1, Collider* c2) override;

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

	SDL_Rect mouseRect;

	Vec2 player2Mouse;
	float player2MouseModule;
	
	bool gameEnd;
	bool playerLose;

	SDL_Rect player;

private:
	Collider* hit_player;
	Collider* near_up;
	Collider* near_down;
	Collider* near_right;
	Collider* near_left;



	bool right;
	bool left;
	bool down;
	bool jump;
};