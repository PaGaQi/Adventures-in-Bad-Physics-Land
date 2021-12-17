#pragma once
#include "Module.h"
#include "SDL/include/SDL.h"
#include "Defs.h"

class Time : public Module
{
public:

	Time();

	// Destructor
	virtual ~Time();

	// Called before render is available
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
};