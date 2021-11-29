#include "App.h"
#include "Player.h"
#include "Physics.h"
#include "Render.h"
#include "Module.h"
#include "SDL/include/SDL.h"

Player::Player()
{
	position.x = 0;
	position.y = 0;
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
	playerRect = { 0, 0, 32, 32 };

	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{

	return true;
}

bool Player::Update(float dt)
{
	app->render->DrawRectangle(playerRect, 255, 0, 0, 255);
	return true;
}

bool Player::PostUpdate()
{
	return true;
}

// Called before quitting
bool Player::CleanUp()
{
	return true;
}