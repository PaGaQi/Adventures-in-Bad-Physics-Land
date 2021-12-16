#include "App.h"
#include "Player.h"
#include "Physics.h"
#include "Render.h"
#include "Scene.h"
#include "Module.h"
#include "Input.h"
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
	gravity = 1;
	position = { 0, 0 };
	playerRect = { position.x, position.y, 32, 32 };

	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (position.y < SCREEN_HEIGHT - playerRect.h - 200) position.y = position.y + gravity;
	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x++;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x--;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= 2;
	}

	return true;
}

bool Player::Update(float dt)
{
	playerRect.x = position.x;
	playerRect.y = position.y;
	return true;
}

bool Player::PostUpdate()
{
	app->render->DrawRectangle(playerRect, 255, 0, 0, 255);
	return true;
}

// Called before quitting
bool Player::CleanUp()
{
	return true;
}