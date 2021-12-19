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
#include "Enemy.h"
#include "Collisions.h"

#include "SDL/include/SDL.h"
#include "Log.h"

#define ENEMY_GRAVITY 0.25f

Enemigo::Enemigo()
{
	enemyPos.x = 0;
	enemyPos.y = 0;
	direction = 0;
	enemyRect = { 0, 0, 32, 32 };
	enemyCol;

}

// Destructor
Enemigo:: ~Enemigo() {}

// Called before render is available
bool Enemigo::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Enemigo::Start()
{
	gravity = 0.5f * ENEMY_GRAVITY;
	enemyFriction = 0.0f;
	colForce = { 0, 0 };
	enemyImpulse = { 0, 0 };
	mass = 1;

	enemyLose = 0;
	gameEnd = 0;

	enemyPos = { 1100, 0 };
	enemyVel = { 0, 0 };
	enemyAcc = { 0, 0 };

	mouseRect = { 0, 0, 16, 16 };

	//playerWinScreen = app->tex->Load("Assets/Textures/RedGuyWins.png");
	//enemyWinScreen = app->tex->Load("Assets/Textures/BlueGuyWins.png");

	enemyRect = { (int)enemyPos.x, (int)enemyPos.y, 32, 32 };
	//winScreenRect = { (SCREEN_WIDTH - 600) / 2, (SCREEN_HEIGHT - 400) / 2, 600, 400 };

	enemyCol = app->coll->AddCollider(enemyRect, Collider::Type::ENEMY, 0, app->enemigo);
	/*near_right = app->coll->AddCollider({ player.x + player.w, player.y, 1, player.h - 1 }, Collider::Type::NEAR, 0, app->player);
	near_left = app->coll->AddCollider({ player.x - 1, player.y, 1, player.h - 1 }, Collider::Type::NEAR, 0, app->player);
	near_down = app->coll->AddCollider({ player.x, player.y + player.w, player.w, 4 }, Collider::Type::NEAR, 0, app->player);*/

	return true;
}

// Called each loop iteration
bool Enemigo::PreUpdate()
{
	if (!gameEnd)
	{
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			enemyImpulse.x = 0.5f;
		}
		else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			enemyImpulse.x = -0.5f;
		}

		else enemyImpulse.x = 0;

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		{
			enemyImpulse.y = -1.5f;
		}
		else enemyImpulse.y = 0;
	}

	SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) ImpulseToMouse(mouseRect.x, mouseRect.y);

	//Lower X Friction if not touching the ground
	if (enemyVel.x > 0) enemyFriction = 0.5 * enemyVel.x;
	else if (enemyVel.x < 0) enemyFriction = 0.5 * (enemyVel.x);
	else if (enemyVel.x == 0) enemyFriction = 0;

	//playerFriction = 0.1 * (playerVel.x);

	colForce = { 0, 0 };

	return true;
}

bool Enemigo::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && gameEnd)
	{
		Restart();
	}

	AccFromForce();

	VelFromAcc();

	PosFromVel();

	enemyRect.x = (int)enemyPos.x;// -(playerRect.w / 2);
	enemyRect.y = (int)enemyPos.y;// -(playerRect.h / 2);

	enemyCol->SetPos(enemyRect.x, enemyRect.y);

	//if (playerPos.y != 0) LOG("POS.y = %f", playerPos.y);
	//if (playerPos.y != 0) LOG("TER.y = %i", app->scene->battlefield.y);
	//if (playerVel.y != 0) LOG("VEL.y = %f", playerVel.y);

	if (enemyPos.x < 0 && enemyPos.x > 1200) enemyPos.x = 32;

	return true;
}

bool Enemigo::PostUpdate()
{
	app->render->DrawRectangle(enemyRect, 0, 0, 255, 255);

	app->render->DrawRectangle(enemyCol->rect, 0, 255, 0, 100);

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) app->render->DrawLine(enemyPos.x, enemyPos.y, enemyPos.x, enemyPos.y, 0, 255, 0);

	//if (playerImpulse.x != 0 || playerImpulse.y != 0)app->render->DrawLine(playerPos.x, playerPos.y, mouseRect.x, mouseRect.y, 0, 255, 0);

	/*if (gameEnd)
	{
		if (!enemyLose) app->render->DrawTexture(playerWinScreen, winScreenRect.x, winScreenRect.y);
		if (enemyLose) app->render->DrawTexture(enemyWinScreen, winScreenRect.x, winScreenRect.y);
	}*/

	if (enemyPos.y < 0 - 50 || enemyPos.y > SCREEN_HEIGHT)
	{
		enemyLose = 1;
		gameEnd = 1;
	}

	return true;
}

void Enemigo::ImpulseToMouse(int lastMouseX, int lastMouseY)
{
	enemyMouse.x = mouseRect.x - enemyPos.x - (enemyRect.w / 2);
	enemyMouse.y = mouseRect.y - enemyPos.y + (enemyRect.h / 2);

	enemyMouseModule = sqrt(pow(enemyMouse.x, 2) + pow(enemyMouse.y, 2));

	enemyImpulse.x = 3 * (enemyMouse.x / enemyMouseModule);
	enemyImpulse.y = 3 * (enemyMouse.y / enemyMouseModule);

	LOG("X: %f / Y: %f / M: %f", enemyMouse.x, enemyMouse.y, enemyMouseModule);
}

void Enemigo::AccFromForce()
{
	enemyAcc.x = (enemyImpulse.x + colForce.x - enemyFriction) / mass; //a = F / m
	enemyAcc.y = (enemyImpulse.y + gravity + colForce.y) / mass; //a = F / m
}

void Enemigo::VelFromAcc()
{
	enemyVel.x += enemyAcc.x;
	enemyVel.y += enemyAcc.y - 0.5 * (enemyVel.y);
}

void Enemigo::PosFromVel()
{
	enemyPos.x += (enemyVel.x * app->dt) + (0.5f * enemyAcc.x * sqrt(app->dt));
	enemyPos.y += (enemyVel.y * app->dt) + (0.5f * (enemyAcc.y) * sqrt(app->dt));


	enemyPos.y += (enemyVel.y * app->dt) + (0.5f * (enemyAcc.y) * sqrt(app->dt));


	//Stop player at wall
	if (enemyPos.x < 50) enemyPos.x = 50;
	else if (enemyPos.x > 1230 - enemyRect.w) enemyPos.x = 1230 - enemyRect.w;
}

void Enemigo::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL)
	{
		//If the player is clipping through the floor, bring him up		
		//if (playerImpulse.y > 0) colForce.y -= playerImpulse.y;

		if (enemyCol->Intersects(app->scene->battlefieldUp))
		{
			colForce.y = -gravity;
			if (enemyImpulse.y > 0) enemyImpulse.y = 0;
		}

		if (enemyCol->Intersects(app->scene->battlefieldRight))
		{
			if (enemyImpulse.x < 0)
			{
				enemyImpulse.x = 0;
				enemyPos.x = app->scene->battlefield.x + app->scene->battlefield.w;
			}
		}
		if (enemyCol->Intersects(app->scene->battlefieldLeft))
		{
			if (enemyImpulse.x > 0)
			{
				enemyImpulse.x = 0;
				enemyPos.x = app->scene->battlefield.x - enemyRect.h;
			}
		}

		if (enemyCol->Intersects(app->scene->battlefield) && !enemyCol->Intersects(app->scene->battlefieldLeft) && !enemyCol->Intersects(app->scene->battlefieldRight))
		{
			colForce.y += 0.1f * (app->scene->battlefield.y - enemyRect.y - enemyRect.h) * gravity;
			if (enemyImpulse.y > 0) enemyImpulse.y = -0;

			enemyPos.y = app->scene->battlefield.y - enemyRect.h;
		}


	}

	if (c2->type == Collider::Type::NEAR)
	{


	}
}


void Enemigo::Restart()
{
	gravity = 0.5f * ENEMY_GRAVITY;
	enemyFriction = 0.0f;
	mass = 1;

	colForce = { 0, 0 };
	enemyImpulse = { 0,0 };

	enemyLose = 0;
	gameEnd = 0;

	enemyPos = { 140, 0 };
	enemyVel = { 0, 0 };
	enemyAcc = { 0, 0 };

	enemyRect = { (int)enemyPos.x, (int)enemyPos.y, 32, 32 };
}

// Called before quitting
bool Enemigo::CleanUp()
{

	return true;
}