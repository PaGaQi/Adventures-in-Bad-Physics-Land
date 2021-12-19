#include "App.h"
#include "Player.h"
#include "Physics.h"
#include "Render.h"
#include "Scene.h"
#include "Module.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"
#include "Textures.h"
#include "PerfTimer.h"
#include "Shoot.h"
#include "Collisions.h"

#include "SDL/include/SDL.h"
#include "Log.h"

#define ENEMY_GRAVITY 0.25f

Enemy::Enemy()
{
	enemyPos.x = 0;
	enemyPos.y = 0;
	direction = 0;
	enemyRect = { 0, 0, 32, 32 };
	enemyCol;

}

// Destructor
Enemy:: ~Enemy() {}

// Called before render is available
bool Enemy::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Enemy::Start()
{
	gravity = 0.5f * ENEMY_GRAVITY;
	enemyFriction = 0.0f;
	colForce = { 0, 0 };
	mass = 1;

	enemyLose = 0;
	gameEnd = 0;

	enemyPos = { 180, 0 };
	enemyVel = { 0, 0 };
	enemyAcc = { 0, 0 };

	mouseRect = { 0, 0, 16, 16 };

	enemyWinScreen = app->tex->Load("Assets/Textures/RedGuyWins.png");
	enemyWinScreen = app->tex->Load("Assets/Textures/BlueGuyWins.png");

	enemyRect = { (int)enemyPos.x, (int)enemyPos.y, 32, 32 };
	winScreenRect = { (SCREEN_WIDTH - 600) / 2, (SCREEN_HEIGHT - 400) / 2, 600, 400 };

	enemyCol = app->coll->AddCollider(enemyRect, Collider::Type::NONE, 0, app->enemy);
	/*near_right = app->coll->AddCollider({ player.x + player.w, player.y, 1, player.h - 1 }, Collider::Type::NEAR, 0, app->player);
	near_left = app->coll->AddCollider({ player.x - 1, player.y, 1, player.h - 1 }, Collider::Type::NEAR, 0, app->player);
	near_down = app->coll->AddCollider({ player.x, player.y + player.w, player.w, 4 }, Collider::Type::NEAR, 0, app->player);*/

	return true;
}

// Called each loop iteration
bool Enemy::PreUpdate()
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
			enemyImpulse.y = -2;
		}
		else enemyImpulse.y = 0;
	}

	SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) ImpulseToMouse(mouseRect.x, mouseRect.y);

	//Lower X Friction if not touching the ground
	if (enemyPos.y <= app->scene->battlefieldPos.y - enemyRect.h)
	{
		enemyFriction = 0.2 * (enemyVel.x);
	}
	else enemyFriction = 0.5 * (enemyVel.x);

	colForce.y = 0;

	return true;
}

bool Enemy::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && gameEnd)
	{
		Restart();
	}

	AccFromForce();

	VelFromAcc();

	PosFromVel();

	enemyRect.x = (int)enemyPos.x;
	enemyRect.y = (int)enemyPos.y;

	enemyCol->SetPos(enemyRect.x, enemyRect.y);

	if (enemyPos.y != 0) LOG("POS.y = %f", enemyPos.y);
	if (enemyVel.y != 0) LOG("VEL.y = %f", enemyVel.y);

	if (enemyPos.x < 0 && enemyPos.x > 1200) enemyPos.x = 32;

	return true;
}

bool Enemy::PostUpdate()
{
	//app->render->DrawRectangle(enemyRect, 255, 0, 0, 255);

	//app->render->DrawRectangle(enemyCol->rect, 0, 255, 0, 100);

	if (gameEnd)
	{
		if (!enemyLose) app->render->DrawTexture(enemyWinScreen, winScreenRect.x, winScreenRect.y);
		if (enemyLose) app->render->DrawTexture(enemyWinScreen, winScreenRect.x, winScreenRect.y);
	}

	if (enemyPos.y < 0 - 50 || enemyPos.y > SCREEN_HEIGHT)
	{
		enemyLose = 1;
		gameEnd = 1;
	}

	return true;
}

void Enemy::ImpulseToMouse(int lastMouseX, int lastMouseY)
{
	enemyMouse.x = mouseRect.x - enemyPos.x;
	enemyMouse.y = mouseRect.y - enemyPos.y;

	enemyMouseModule = sqrt(pow(enemyMouse.x, 2) + pow(enemyMouse.y, 2));

	enemyImpulse.x = 3 * (enemyMouse.x / enemyMouseModule);
	enemyImpulse.y = 3 * (enemyMouse.y / enemyMouseModule);

	LOG("X: %f / Y: %f / M: %f", enemyMouse.x, enemyMouse.y, enemyMouseModule);
}

void Enemy::AccFromForce()
{
	enemyAcc.x = (enemyImpulse.x + colForce.x) / mass; //a = F / m
	enemyAcc.y = (enemyImpulse.y + gravity + colForce.y) / mass; //a = F / m
}

void Enemy::VelFromAcc()
{
	enemyVel.x += enemyAcc.x - enemyFriction;
	enemyVel.y += enemyAcc.y - 0.5 * (enemyVel.y);
}

void Enemy::PosFromVel()
{
	enemyPos.x += (enemyVel.x * app->dt) + (0.5f * enemyAcc.x * sqrt(app->dt));
	enemyPos.y += (enemyVel.y * app->dt) + (0.5f * (enemyAcc.y) * sqrt(app->dt));


	enemyPos.y += (enemyVel.y * app->dt) + (0.5f * (enemyAcc.y) * sqrt(app->dt));


	//Stop player at wall
	if (enemyPos.x < 50) enemyPos.x = 50;
	else if (enemyPos.x > 1230 - enemyRect.w) enemyPos.x = 1230 - enemyRect.w;
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL)
	{


		if (enemyCol->Intersects(app->scene->battlefield))
		{
			LOG("PLAYER CLIPPING THROUGH MAP");
			colForce.y += 0.1f * (app->scene->battlefield.y - enemyRect.y - enemyRect.h) * gravity;
		}
		else colForce.y = -gravity;

		if (c1 == near_down)
		{
			if (enemyVel.y > 0)
			{
				enemyVel.y = c2->rect.y - enemyRect.h;

				enemyVel.y = 0;
			}
			else
			{
				jump = true;
				down = false;
			}
		}
		else if (c1 == near_right)
		{
			if (enemyVel.x > 0 && enemyRect.x < c2->rect.x)
			{
				enemyRect.x = c2->rect.x - enemyRect.w;
				enemyVel.x = 0;
			}
			right = false;
		}
		else if (c1 == near_left)
		{
			if (enemyVel.x < 0 && enemyRect.x > c2->rect.x)
			{
				//player.x = c2->rect.x + c2->rect.w;
				enemyVel.x = 0;
			}
			left = false;
		}
	}
}


void Enemy::Restart()
{
	gravity = 0.5f * ENEMY_GRAVITY;
	enemyFriction = 0.0f;
	mass = 1;

	enemyLose = 0;
	gameEnd = 0;

	enemyPos = { 180, 0 };
	enemyVel = { 0, 0 };
	enemyAcc = { 0, 0 };

	enemyRect = { (int)enemyPos.x, (int)enemyPos.y, 32, 32 };
}

// Called before quitting
bool Enemy::CleanUp()
{

	return true;
}