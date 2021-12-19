#include "Module.h"
#include "Render.h"
#include "Textures.h"
#include "math.h"
#include "Defs.h"

struct SDL_Texture;

enum type
	{
		CUM, 
		BOUNCY,	
		NOTHING
	};

class Shoot : public Module
{
public:
	Shoot();

	// Destructor
	virtual ~Shoot();
	
	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);
	
	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void VelFromAcc(Vec2* acc, Vec2* vel);
	void PosFromVel(Vec2* vel, Vec2* pos);

	//Create a shot
	void Fire(Vec2 pos);
	void Reload();

	// Position of the shot in the map
	Vec2 shotPos;
	Vec2 shotVel;
	Vec2 shotAcc;

	//Type of Shot you fire
	type shotType;

	//Direction, 1 right, 0 left;	
	bool direction;
	int mass;

	SDL_Rect shotRect;

	//Forces
	float gravity;
	float friction;
private:

	const int offScreenBuffer = 10;


};