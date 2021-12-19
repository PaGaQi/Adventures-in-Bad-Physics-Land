#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Collisions.h"
#include "Player.h"
#include "Collider.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
	battlefield;
	rightWall;
	leftWall;
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	battlefieldWidth = 1000;
	battlefieldHeight = SCREEN_HEIGHT / 2;
	
	battlefieldPos.x = (SCREEN_WIDTH - battlefieldWidth) / 2;
	battlefieldPos.y = SCREEN_HEIGHT - 200;
	
	battlefield = { (int)battlefieldPos.x , (int)battlefieldPos.y, battlefieldWidth, battlefieldHeight };
	battlefieldUp = { (int)battlefieldPos.x , (int)battlefieldPos.y - 3, battlefieldWidth, 3 };
	battlefieldRight = { (int)battlefieldPos.x + battlefieldWidth, (int)battlefieldPos.y + 16, 32, battlefieldHeight };
	battlefieldLeft = { (int)battlefieldPos.x - 16, (int)battlefieldPos.y + 16, 32, battlefieldHeight };

	wallWidth = 50;
	wallHeight = SCREEN_HEIGHT;

	leftWallPos.x = 0;
	leftWallPos.y = 0;

	leftWall = { (int)leftWallPos.x , (int)leftWallPos.y, wallWidth, wallHeight };
	leftWallNearRect = { (int)leftWallPos.x + wallWidth - 24, (int)leftWallPos.y, 32, wallHeight };

	rightWallPos.x = SCREEN_WIDTH - wallWidth;
	rightWallPos.y = 0;
	
	rightWall = { (int)rightWallPos.x , (int)rightWallPos.y, wallWidth, wallHeight };
	rightWallNearRect = { (int)rightWallPos.x - 8, (int)rightWallPos.y, 32, wallHeight };

	seeCols = 1;

	battlefieldCol = app->coll->AddCollider(battlefield, Collider::Type::WALL, 0, app->scene);
	battlefieldUpCol = app->coll->AddCollider(battlefieldUp, Collider::Type::WALL, 0, app->scene);
	battlefieldRightCol = app->coll->AddCollider(battlefieldRight, Collider::Type::WALL, 0, app->scene);
	battlefieldLeftCol = app->coll->AddCollider(battlefieldLeft, Collider::Type::WALL, 0, app->scene);

	leftWallNearCol = app->coll->AddCollider(leftWallNearRect, Collider::Type::WALL, 0, app->scene);
	rightWallNearCol = app->coll->AddCollider(rightWallNearRect, Collider::Type::WALL, 0, app->scene);

	leftWallCol = app->coll->AddCollider(leftWall, Collider::Type::WALL, 0, app->scene);
	rightWallCol = app->coll->AddCollider(rightWall, Collider::Type::WALL, 0, app->scene);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) seeCols = !seeCols;
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	app->render->DrawRectangle(battlefield, 255, 255, 0, 255);
	app->render->DrawRectangle(rightWall, 0, 0, 255, 255);
	app->render->DrawRectangle(leftWall, 0, 0, 255, 255);
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (seeCols)
	{
		app->render->DrawRectangle(battlefieldUp, 0, 255, 255, 100);
		app->render->DrawRectangle(battlefieldRight, 0, 255, 255, 100);
		app->render->DrawRectangle(battlefieldLeft, 0, 255, 255, 100);

		app->render->DrawRectangle(leftWallNearRect, 0, 255, 255, 100);
		app->render->DrawRectangle(rightWallNearRect, 0, 255, 255, 100);
	}

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
