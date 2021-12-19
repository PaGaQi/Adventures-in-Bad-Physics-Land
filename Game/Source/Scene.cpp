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
	wallRight;
	wallLeft;
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
	battlefieldRight = { (int)battlefieldPos.x + battlefieldWidth, (int)battlefieldPos.y, 32, battlefieldHeight };
	battlefieldLeft = { (int)battlefieldPos.x - 32, (int)battlefieldPos.y, 32, battlefieldHeight };

	wallWidth = 50;
	wallHeight = SCREEN_HEIGHT - 160;

	wallRightPos.x = SCREEN_WIDTH - wallWidth;
	wallRightPos.y = 160;

	wallLeftPos.x = 0;
	wallLeftPos.y = 160;

	wallRight = { (int)wallRightPos.x , (int)wallRightPos.y, wallWidth, wallHeight };
	wallLeft = { (int)wallLeftPos.x , (int)wallLeftPos.y, wallWidth, wallHeight };

	battlefieldCol = app->coll->AddCollider(battlefield, Collider::Type::WALL, 0, app->scene);
	battlefieldUpCol = app->coll->AddCollider(battlefieldUp, Collider::Type::WALL, 0, app->scene);
	battlefieldRightCol = app->coll->AddCollider(battlefieldRight, Collider::Type::WALL, 0, app->scene);
	battlefieldLeftCol = app->coll->AddCollider(battlefieldLeft, Collider::Type::WALL, 0, app->scene);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	app->render->DrawRectangle(battlefield, 255, 255, 0, 255);
	app->render->DrawRectangle(wallRight, 0, 0, 255, 255);
	app->render->DrawRectangle(wallLeft, 0, 0, 255, 255);
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	app->render->DrawRectangle(battlefieldUp, 0, 255, 255, 100);
	app->render->DrawRectangle(battlefieldRight, 0, 255, 255, 100);
	app->render->DrawRectangle(battlefieldLeft, 0, 255, 255, 100);

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
