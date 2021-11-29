#include "App.h"
#include "Player.h"
#include "Physics.h"
#include "Module.h"
#include "SDL/include/SDL.h"

Player::Player()
{
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
	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{
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