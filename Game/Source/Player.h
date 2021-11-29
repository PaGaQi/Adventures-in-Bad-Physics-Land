#include "Module.h"
#include "SDL/include/SDL.h"

struct Vec2
	{
		int x, y;
	};

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

	// Position of the player in the map
	Vec2 position;


	//bool isMoving;	
	int direction;
	

	SDL_Rect playerRect;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* playerSprites = nullptr;




	// Called before quitting
	bool CleanUp();
};