/*#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		BULLET,
		


		MAX
	};

	// Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//iPoint GetPos() { return iPoint{ rect.x,rect.y }; }


	void AddListener(Module* listener);

	// Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__*/

/*#ifndef _COLLIDER_H
#define _COLLIDER_H
#include "Textures.h"
#include "Player.h"



class Collider : public Player {

public:

	enum class ColliderType {

		Box,
		Circle
	};

protected:

	ColliderType mType;

	static const bool DEBUG_COLLIDERS = true;
	Textures* mDebugTexture;

public:

	Collider(ColliderType type);
	virtual ~Collider();

	

	ColliderType GetType();

	virtual void Render();

protected:

	void SetDebugTexture(Textures* texture);
};

#endif // _COLLIDER_H*/

/*#pragma once
#include "Point.h"
#include "List.h"

enum class ShapeType
{
	CIRCLE,
	RECTANGLE,
};

enum BodyType
{
	STATIC,
	DYNAMIC,
	KINEMATIC,
};

class PhysicBody
{
private:
	fPoint position = { 0.0, 0.0 };
	fPoint lastPosition = { 0.0,0.0 };


	
	float width = 1.0f;
	float height = 1.0f;
	float radius = 1.0f;

	ShapeType shape = ShapeType::RECTANGLE;
	BodyType type = STATIC;

	

	

	List<PhysicBody*> collisionList;
public:
	PhysicBody();

	~PhysicBody();

	PhysicBody(fPoint pos, float width, float height, BodyType type);

	PhysicBody(fPoint pos, float radius, BodyType type);

	PhysicBody(PhysicBody& copy);

	void OnCollision(PhysicBody* col);

	void OnCollisionTouch(PhysicBody* col);

	void OnCollisionLeave(PhysicBody* col);

	fPoint GetPosition()
	{
		return position;
	}
	void SetPosition(fPoint pos)
	{
		this->position = pos;
	}
	int GetRadius()
	{
		return radius;
	}

	bool Contains(fPoint pos)
	{
		if (shape == ShapeType::RECTANGLE)
		{
			if (pos.x >= position.x - width / 2 && pos.x <= position.x + width / 2 &&
				pos.y >= position.y - height / 2 && pos.y <= position.y + height / 2)
			{
				return true;
			}
		}
		else
		{
			if (sqrt(pow(position.x - pos.x, 2) + pow(position.y - pos.y, 2)) <= radius)
			{
				return true;
			}
		}

		return false;
	}

private:

	
};*/

#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 8

class Enemy;
class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		WALL,
		ENEMY,
		NEAR,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);
	Collider(SDL_Rect rectangle, Type type, Enemy* point_, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
	Enemy* point;
};


#endif // !__COLLIDER_H__
