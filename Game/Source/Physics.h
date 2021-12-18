#include "Module.h"
#include "SDL/include/SDL.h"

class Physics : public Module
{
public:

	Physics();

	// Destructor
	virtual ~Physics();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	//Forces
	int Gravity();
	int Restitution();



	// Called before quitting
	bool CleanUp();


};