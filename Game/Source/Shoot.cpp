#include "App.h"
#include "Shoot.h"
#include "Player.h"
#include "Module.h"
#include "Log.h"
#include "SDL/include/SDL.h"

Shoot::Shoot()
{
}

// Destructor
Shoot:: ~Shoot() {}

// Called before the first frame
bool Shoot::Start()
{
	gravity = 1;
	friction = 0.0f;
	mass = 3;

	shotPos = { 0, 0 };
	shotVel = { 0, 0 };
	shotAcc = { 0, 0 };

	shotRect = { (int)shotPos.x, (int)shotPos.y, 16, 16 };
	return true;
}

// Called each loop iteration
bool Shoot::PreUpdate()
{
	return true;
}

bool Shoot::Update(float dt)
{
	return true;
}

bool Shoot::PostUpdate()
{
	return true;
}

void Shoot::VelFromAcc(Vec2* acc, Vec2* vel)
{
	shotVel.x += shotAcc.x - friction;
	shotVel.y += shotAcc.y;
}

void Shoot::PosFromVel(Vec2* vel, Vec2* pos)
{
	shotPos.x += shotVel.x;
	shotPos.y += shotVel.y;

	if (shotPos.x < 0) shotPos.x = 0;
	else if (shotPos.x > 1248) shotPos.x = 1248;
}

// Called before quitting
bool Shoot::CleanUp()
{
	return true;
}