#include "App.h"
#include "Player.h"
#include "Physics.h"
#include "Render.h"
#include "Scene.h"
#include "Module.h"
#include "Input.h"
#include "Timer.h"
#include "Shoot.h"
#include "SDL/include/SDL.h"
#include "Log.h"

Player::Player()
{
	playerPos.x = 0;
	playerPos.y = 0;
	direction = 0;
	playerRect = { 0, 0, 32, 32 };
}

// Destructor
Player:: ~Player() {}

// Called before render is available
bool Player::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Player::Start()
{
	gravity = 20;
	drag = 0.0f;
	mass = 3;

	playerPos = { 0, 0 };
	playerVel = { 0, 0 };
	playerAcc = { 0, 0 };

	playerRect = { (int)playerPos.x, (int)playerPos.y, 32, 32 };

	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (playerPos.y < app->scene->battlefieldPos.y - playerRect.h) playerPos.y += gravity;
	else if (playerPos.y > app->scene->battlefieldPos.y - playerRect.h) playerPos.y = app->scene->battlefieldPos.y - playerRect.h;
	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		playerAcc.x = 10;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerAcc.x = -10;
	}
	else if (app->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
	{
		playerAcc.x = 20;
	}
	else playerAcc.x = 0;
	
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		playerVel.y = -40;
	}
	else playerVel.y = 0;
		
	

	drag = 0.5 * (playerVel.x);
	
	
	return true;
}

bool Player::Update(float dt)
{
	VelFromAcc(&playerAcc, &playerVel);

	PosFromVel(&playerVel, &playerPos);

	playerRect.x = (int)playerPos.x;
	playerRect.y = (int)playerPos.y;

	if (playerVel.x != 0) LOG("VEL = %f", playerVel.x);
	//if (drag != 0.0f) LOG("DRAG = %f", drag);

	if (playerPos.x < 0 && playerPos.x > 1200) playerPos.x = 32;

	return true;
}

bool Player::PostUpdate()
{
	app->render->DrawRectangle(playerRect, 255, 0, 0, 255);

	//LOG("Player Pos = %i", position.x);
	//if (playerVel.x != 0)LOG("Player Vel = %f", playerVel.x);
	//if (drag != 0) LOG("DRAG = %f", drag);
	//LOG("Player Acc = %i", acceleration.x);
	return true;
}

void Player::VelFromAcc(Vec2* acc, Vec2* vel)
{	
	playerVel.x += playerAcc.x - drag;
	playerVel.y += playerAcc.y;	
}

void Player::PosFromVel(Vec2* vel, Vec2* pos)
{
	playerPos.x += playerVel.x;
	playerPos.y += playerVel.y;

	if (playerPos.x < 0) playerPos.x = 0;
	else if (playerPos.x > 1248) playerPos.x = 1248;
}

// Called before quitting
bool Player::CleanUp()
{
	
	return true;
}