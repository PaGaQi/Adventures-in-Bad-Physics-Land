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

#define PLAYER_GRAVITY 5

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
	gravity = PLAYER_GRAVITY;
	playerFriction = 0.0f;
	mass = 1;

	playerLose = 0;
	gameEnd = 0;

	playerPos = { 140, 0 };
	playerVel = { 0, 0 };
	playerAcc = { 0, 0 };

	playerWinScreen = app->tex->Load("Assets/Textures/RedGuyWins.png");
	enemyWinScreen = app->tex->Load("Assets/Textures/BlueGuyWins.png");

	playerRect = { (int)playerPos.x, (int)playerPos.y, 32, 32 };
	winScreenRect = {(SCREEN_WIDTH - 600) / 2, (SCREEN_HEIGHT - 400) / 2, 600, 400 };

	hit_player = app->coll->AddCollider(player, Collider::Type::PLAYER, 0, app->player);
	/*near_right = app->coll->AddCollider({ player.x + player.w, player.y, 1, player.h - 1 }, Collider::Type::NEAR, 0, app->player);
	near_left = app->coll->AddCollider({ player.x - 1, player.y, 1, player.h - 1 }, Collider::Type::NEAR, 0, app->player);
	near_down = app->coll->AddCollider({ player.x, player.y + player.w, player.w, 4 }, Collider::Type::NEAR, 0, app->player);*/

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
			playerImpulse.y = -2;
		}
		else playerImpulse.y = 0;
	}

	playerFriction = 0.5 * (playerVel.x);	
	
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

	if (gameEnd)
	{
		if (!playerLose) app->render->DrawTexture(playerWinScreen, winScreenRect.x, winScreenRect.y);
		if (playerLose) app->render->DrawTexture(enemyWinScreen, winScreenRect.x, winScreenRect.y);		
	}

	if (playerPos.y < 0 - 50|| playerPos.y > SCREEN_HEIGHT)
	{
		playerLose = 1;
		gameEnd = 1;
	}

	LOG("Player Lose = %i", playerLose);

	//LOG("Player Pos = %i", position.x);
	//if (playerVel.x != 0)LOG("Player Vel = %f", playerVel.x);
	//if (drag != 0) LOG("DRAG = %f", drag);
	//LOG("Player Acc = %i", acceleration.x);
	return true;
}

void Player::AccFromForce()
{
	playerAcc.x = playerImpulse.x / mass; //a = F / m
	playerAcc.y = (playerImpulse.y / mass); //a = F / m
}

void Player::VelFromAcc()
{	
	playerVel.x += playerAcc.x - playerFriction;
	playerVel.y += playerAcc.y - 0.5 * (playerVel.y);
}												
												
void Player::PosFromVel()	
{
	playerPos.x += (playerVel.x * app->dt) + (0.5f * playerAcc.x * sqrt(app->dt) );
	playerPos.y += (playerVel.y * app->dt) + (0.5f * (playerAcc.y) * sqrt(app->dt));

	//Apply gravity only when the player isn't on the ground
	if (playerPos.y < app->scene->battlefieldPos.y - playerRect.h || (playerPos.x < 140 || playerPos.x > 1140)) playerPos.y += (playerVel.y * app->dt) + (0.5f * (playerAcc.y + gravity) * sqrt(app->dt));
	else if (playerPos.y >= app->scene->battlefieldPos.y - playerRect.h) playerPos.y += (playerVel.y * app->dt) + (0.5f * (playerAcc.y) * sqrt(app->dt));
	//&& (playerPos.x < 140 || playerPos.x > 1140)


	//Stop player at wall
	if (playerPos.x < 50) playerPos.x = 50;
	else if (playerPos.x > 1230 - playerRect.w) playerPos.x = 1230 - playerRect.w;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL)
	{
		if (c1 == near_down)
		{
			if (playerVel.y > 0)
			{
				playerVel.y = c2->rect.y - player.h;

				playerVel.y = 0;
			}
			else
			{
				jump = true;
				down = false;
			}
		}
		else if (c1 == near_right)
		{
			if (playerVel.x > 0 && player.x < c2->rect.x)
			{
				player.x = c2->rect.x - player.w;
				playerVel.x = 0;
			}
			right = false;
		}
		else if (c1 == near_left)
		{
			if (playerVel.x < 0 && player.x > c2->rect.x)
			{
				//player.x = c2->rect.x + c2->rect.w;
				playerVel.x = 0;
			}
			left = false;
		}
	}
	/*if (c1 == near_down && c2->type == Collider::Type::PLAT)
	{
		if (momentum.y > 0)
		{
			if (player.x + player.h > c2->rect.x) player.y = c2->rect.y - player.h;
			momentum.y = 0;
		}
		can_jump = true;
		can_move_down = false;
	}*/

	/*if (c1 == hit_player && c2->type == Collider::Type::ENEMY)
	{
		die = true;
		current_animation = &dying;
		dying.Reset();
	}*/
}


void Player::Restart()
{
	gravity = PLAYER_GRAVITY;
	playerFriction = 0.0f;
	mass = 1;

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