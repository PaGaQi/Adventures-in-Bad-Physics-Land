#include "App.h"
#include "Shoot.h"
#include "Player.h"
#include "Module.h"
#include "Input.h"
#include "math.h"
#include "Log.h"
#include "SDL/include/SDL.h"

Shoot::Shoot()
{
	//shotRect;

	Reload();
}

// Destructor
Shoot:: ~Shoot() 
{
}

// Called before the first frame
//Start() Function here
/*
bool Shoot::Start()
{
	gravity = 1;
	friction = 0.0f;
	mass = 1;

	shotPos = { 0, 0 };
	shotVel = { 0, 0 };
	shotAcc = { 0, 0 };

	shotType = NOTHING;

	//shotRect = nullptr;
	//shotRect = { (int)shotPos.x, (int)shotPos.y, 16, 16 };
	return true;
}
*/
// Called each loop iteration
bool Shoot::PreUpdate()
{
	//LOG("%i", shotRect.w);
	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		if (shotType == NOTHING)
		{
			//shotRect = new SDL_Rect;
			shotRect = { (int)shotPos.x, (int)shotPos.y, 16, 16 };
			shotType = BOUNCY;
		}
		else if (shotType != NOTHING)
		{
			shotRect = { 0, 0, 0, 0 };
			shotType = NOTHING;
		}
		
	}
	
	return true;
}

bool Shoot::Update(float dt)
{
	
	if (shotPos.y < -offScreenBuffer || shotPos.y > SCREEN_HEIGHT + offScreenBuffer)
	{
		Reload();
	}

	return true;
}

bool Shoot::PostUpdate()
{
	app->render->DrawRectangle(shotRect, 0, 255, 0, 255);
	return true;
}


void Shoot::Fire(Vec2 pos)
{
	shotPos.x = pos.x;
	shotPos.y = pos.x;

	shotType = BOUNCY;
	//app->shoot->active = false; //When U Reload
}

void Shoot::Reload()
{
	shotType = NOTHING;
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