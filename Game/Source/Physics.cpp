#include "App.h"
#include "Physics.h"
#include "Module.h"
#include "SDL/include/SDL.h"

Physics::Physics()
{
}

// Destructor
Physics:: ~Physics() {}

// Called before render is available
bool Physics::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Physics::Start() 
{
	return true;
}

// Called each loop iteration
bool Physics::PreUpdate() 
{
	return true;
}

bool Physics::Update(float dt) 
{
	return true;
}

bool Physics::PostUpdate() 
{
	return true;
}

int Physics::Gravity()
{
	return 0;
}

int Physics::Restitution()
{
	return 0;
}

// Called before quitting
bool Physics:: CleanUp() 
{
	return true;
}