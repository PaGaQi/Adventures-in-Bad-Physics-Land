#include "App.h"
#include "Module.h"
#include "Log.h"
#include "Time.h"
#include "SDL/include/SDL.h"

Time* Time:: sInstance = nullptr;

Time::Time()
{	
}

// Destructor
Time:: ~Time() {}

// Called before render is available
bool Time:: Start()
{
	return true;
}

void Time::Ticks()
{
	deltaTime = (SDL_GetTicks() - lastTime) * (FPS / 1000.0f);

	if (deltaTime > TARGET_DELTA_TIME) deltaTime = TARGET_DELTA_TIME;

	lastTime = SDL_GetTicks();
}

// Called before quitting
bool Time::CleanUp()
{
	return true;
}