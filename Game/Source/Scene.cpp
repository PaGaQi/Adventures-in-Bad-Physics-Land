#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
	battlefield;
	wall;
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
	battlefieldWidth = 1280;
	battlefieldHeight = SCREEN_HEIGHT / 2;
	
	battlefieldPos.x = (SCREEN_WIDTH - battlefieldWidth) / 2;
	battlefieldPos.y = SCREEN_HEIGHT - 200;
	
	battlefield = { (int)battlefieldPos.x , (int)battlefieldPos.y, battlefieldWidth, battlefieldHeight };

	wallWidth = 50;
	wallHeight = SCREEN_HEIGHT / 2;

	wallPos.x = SCREEN_WIDTH - wallWidth;
	wallPos.y = 160;

	wall = { (int)wallPos.x , (int)wallPos.y, wallWidth, wallHeight };
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
	//app->render->DrawRectangle(wall, 0, 0, 255, 255);
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

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
