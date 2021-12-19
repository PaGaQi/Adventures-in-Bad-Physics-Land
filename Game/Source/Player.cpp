#include "App.h"
#include "Player.h"
#include "Physics.h"
#include "Render.h"
#include "Scene.h"
#include "Module.h"
#include "Input.h"
#include "Timer.h"
#include "Textures.h"
#include "PerfTimer.h"
#include "Shoot.h"
#include "Collisions.h"

#include "SDL/include/SDL.h"
#include "Log.h"

#define PLAYER_GRAVITY 0.25f

Player::Player()
{
	playerPos.x = 0;
	playerPos.y = 0;
	direction = 0;
	playerRect = { 0, 0, 32, 32 };
	playerCol;
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
	gravity = 0.5f * PLAYER_GRAVITY;
	playerFriction = 0.0f;
	colForce = { 0, 0 };
	playerImpulse = { 0, 0 };
	mass = 1;

	playerLose = 0;
	gameEnd = 0;

	playerPos = { 140, 0 };
	playerVel = { 0, 0 };
	playerAcc = { 0, 0 };

	mouseRect = { 0, 0, 16, 16 };

	playerWinScreen = app->tex->Load("Assets/Textures/RedGuyWins.png");
	enemyWinScreen = app->tex->Load("Assets/Textures/BlueGuyWins.png");

	playerRect = { (int)playerPos.x, (int)playerPos.y, 32, 32 };
	winScreenRect = {(SCREEN_WIDTH - 600) / 2, (SCREEN_HEIGHT - 400) / 2, 600, 400 };

	playerCol = app->coll->AddCollider(playerRect, Collider::Type::PLAYER, 0, app->player);
	
	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (!gameEnd)
	{
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			playerImpulse.x = 0.5f;
		}
		else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			playerImpulse.x = -0.5f;
		}
		else if (app->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
		{
			playerImpulse.x = 5;
		}
		else playerImpulse.x = 0;

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			playerImpulse.y = -1.5f;
		}
		else playerImpulse.y = 0;
	}

	SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) ImpulseToMouse(mouseRect.x, mouseRect.y);

	//Lower X Friction if not touching the ground
	if (playerVel.x > 0) playerFriction = 0.5 * playerVel.x;
	else if (playerVel.x < 0) playerFriction = 0.5 * (playerVel.x);
	else if (playerVel.x == 0) playerFriction = 0;
	
	//playerFriction = 0.1 * (playerVel.x);

	colForce = {0, 0};

	return true;
}

bool Player::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && gameEnd)
	{
		Restart();
	}

	AccFromForce();

	VelFromAcc();

	PosFromVel();

	playerRect.x = (int)playerPos.x;// -(playerRect.w / 2);
	playerRect.y = (int)playerPos.y;// -(playerRect.h / 2);

	playerCol->SetPos(playerRect.x, playerRect.y);

	//if (playerPos.y != 0) LOG("POS.y = %f", playerPos.y);
	//if (playerPos.y != 0) LOG("TER.y = %i", app->scene->battlefield.y);
	//if (playerVel.y != 0) LOG("VEL.y = %f", playerVel.y);

	if (playerPos.x < 0 && playerPos.x > 1200) playerPos.x = 32;

	return true;
}

bool Player::PostUpdate()
{
	app->render->DrawRectangle(playerRect, 255, 0, 0, 255);

	app->render->DrawRectangle(playerCol->rect, 0, 255, 0, 100);

	if (app->input->GetKey(SDL_SCANCODE_0) == KEY_REPEAT) app->render->DrawLine(playerPos.x, playerPos.y, playerPos.x, playerPos.y, 0, 255, 0);
	
	//if (playerImpulse.x != 0 || playerImpulse.y != 0)app->render->DrawLine(playerPos.x, playerPos.y, mouseRect.x, mouseRect.y, 0, 255, 0);

	if (gameEnd||app->enemigo->gameEnd)
	{
		if (!playerLose) app->render->DrawTexture(playerWinScreen, winScreenRect.x, winScreenRect.y);
		if (playerLose) app->render->DrawTexture(enemyWinScreen, winScreenRect.x, winScreenRect.y);		
	}

	if (playerPos.y < 0 - 50|| playerPos.y > SCREEN_HEIGHT)
	{
		playerLose = 1;
		gameEnd = 1;
	}

	return true;
}

void Player::ImpulseToMouse(int lastMouseX, int lastMouseY)
{
	player2Mouse.x = mouseRect.x - playerPos.x - (playerRect.w / 2);
	player2Mouse.y = mouseRect.y - playerPos.y + (playerRect.h / 2);

	player2MouseModule = sqrt(pow(player2Mouse.x, 2) + pow(player2Mouse.y, 2));

	playerImpulse.x = 3 * (player2Mouse.x / player2MouseModule);
	playerImpulse.y = 3 * (player2Mouse.y / player2MouseModule);

	LOG("X: %f / Y: %f / M: %f", player2Mouse.x, player2Mouse.y, player2MouseModule);
}

void Player::AccFromForce()
{
	playerAcc.x = (playerImpulse.x + colForce.x - playerFriction)/ mass; //a = F / m
	playerAcc.y = (playerImpulse.y + gravity + colForce.y) / mass;		//a = F / m
}

void Player::VelFromAcc()
{	
	playerVel.x += playerAcc.x;
	playerVel.y += playerAcc.y - 0.5 * (playerVel.y);
}												
												
void Player::PosFromVel()	
{
	playerPos.x += (playerVel.x * app->dt) + (0.5f * playerAcc.x * sqrt(app->dt) );
	playerPos.y += (playerVel.y * app->dt) + (0.5f * (playerAcc.y) * sqrt(app->dt));

	
	playerPos.y += (playerVel.y * app->dt) + (0.5f * (playerAcc.y) * sqrt(app->dt));

	//Stop player at wall
	//if (playerPos.x < 50) playerPos.x = 50;
	//else if (playerPos.x > 1230 - playerRect.w) playerPos.x = 1230 - playerRect.w;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{	
	if (c2->type == Collider::Type::WALL)
	{		
		//BATTLEFIELD COLLISIONS-------------------------------------------------------------------------------
		if (playerCol->Intersects(app->scene->battlefieldUp))				
		{
			colForce.y = -gravity;		
			if (playerImpulse.y > 0) playerImpulse.y = 0;
		}

		else if (playerCol->Intersects(app->scene->battlefieldRight))
		{
			if (playerImpulse.x < 0)
			{
				playerImpulse.x = 0;
				playerPos.x = app->scene->battlefield.x + app->scene->battlefield.w;
			}
		}	
		else if (playerCol->Intersects(app->scene->battlefieldLeft))
		{
			if (playerImpulse.x > 0 )//&& playerPos.x == app->scene->battlefieldLeft.x)
			{
				playerImpulse.x = 0;
				playerPos.x = app->scene->battlefield.x - playerRect.w;
			}
		}

		if (playerCol->Intersects(app->scene->battlefield))
		{
			if (!playerCol->Intersects(app->scene->battlefieldLeft) && !playerCol->Intersects(app->scene->battlefieldRight))
			{
				colForce.y += 0.1f * (app->scene->battlefield.y - playerRect.y - playerRect.h) * gravity;
				if (playerImpulse.y > 0) playerImpulse.y = -0;

				playerPos.y = app->scene->battlefield.y - playerRect.h;
			}

			if (playerCol->Intersects(app->scene->battlefieldLeft))
			{
				playerPos.x = app->scene->battlefield.x - playerRect.w;
			}

			else if (playerCol->Intersects(app->scene->battlefieldRight))
			{
				playerPos.x = app->scene->battlefield.x + app->scene->battlefield.w;
			}
		
		}
		
		//WALL COLLISIONS------------------------------------------------------------------------------------------
		if (playerCol->Intersects(app->scene->leftWallNearRect))
		{
			if (playerImpulse.x < 0)
			{
				playerImpulse.x = 0;
				playerPos.x = app->scene->wallWidth;
			}
		}

		else if (playerCol->Intersects(app->scene->rightWallNearRect))
		{
			if (playerImpulse.x > 0 && playerPos.x >= app->scene->rightWallNearRect.x)
			{
				playerImpulse.x = 0;
				playerPos.x = SCREEN_WIDTH - app->scene->wallWidth - playerRect.w;
			}
		}

		if (playerCol->Intersects(app->scene->rightWall))
		{
			if (!playerCol->Intersects(app->scene->rightWallNearRect))
			{
				colForce.x -= 0.2f * (app->scene->rightWall.w + playerRect.x + playerRect.w);
				if (playerImpulse.x > 0) playerImpulse.x = 0;

				playerPos.y = app->scene->battlefield.y - playerRect.h;
			}

			else if (playerCol->Intersects(app->scene->rightWallNearRect))
			{
				playerPos.x = SCREEN_WIDTH - app->scene->rightWall.w - 32;
			}
		}

		if (playerCol->Intersects(app->scene->leftWall))
		{
			if (!playerCol->Intersects(app->scene->leftWallNearRect))
			{
				colForce.x += 0.2f * (app->scene->leftWall.w + playerRect.x + playerRect.w);
				if (playerImpulse.x > 0) playerImpulse.x = 0;

				playerPos.x = app->scene->leftWall.w + playerRect.w;
			}

			else if (playerCol->Intersects(app->scene->leftWallNearRect))
			{
				playerPos.x = app->scene->leftWall.x + app->scene->leftWall.w;
			}
		}
	}

}


void Player::Restart()
{
	gravity = 0.5f * PLAYER_GRAVITY;
	playerFriction = 0.0f;
	mass = 1;

	colForce = { 0, 0 };
	playerImpulse = { 0,0 };

	playerLose = 0;
	gameEnd = 0;

	playerPos = { 140, 0 };
	playerVel = { 0, 0 };
	playerAcc = { 0, 0 };

	playerRect = { (int)playerPos.x, (int)playerPos.y, 32, 32 };
}

// Called before quitting
bool Player::CleanUp()
{
	
	return true;
}