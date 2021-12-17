#pragma once
#include "Module.h"
#include "SDL/include/SDL.h"
#include "Defs.h"

//FPS == 60 (As defined in Defs.h)
const float TARGET_DELTA_TIME = 1.5f;

class Time : public Module
{
public:

	Time();
	// Destructor
	virtual ~Time();

	void Ticks();

	inline static Time* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new Time(); }
	inline float GetDeltaTime() { return deltaTime; };

	// Called before render is available
	bool Start();

	// Called each loop iteration
	//bool PreUpdate();
	//bool Update(float dt);
	//bool PostUpdate();
	// Called before quitting
	bool CleanUp();

public:

private:
	static Time* sInstance;
	float deltaTime;
	float lastTime;


};