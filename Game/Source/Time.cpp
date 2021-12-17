#include "App.h"
#include "Player.h"
#include "Module.h"
#include "Log.h"
#include "Time.h"

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

// Called each loop iteration
bool Time::PreUpdate()
{
	return true;
}
bool Time::Update(float dt)
{
	return true;
}
bool Time::PostUpdate()
{
	return true;
}

// Called before quitting
bool Time::CleanUp()
{
	return true;
}