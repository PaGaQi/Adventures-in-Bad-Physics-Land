/*#include "Collider.h"
#include "App.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) : rect(rectangle), type(type)
{
	listeners[0] = listener;
}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// L6: DONE 1: Check if there is an overlap
	// between argument "r" and property "rect"
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

void Collider::AddListener(Module* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)
	{
		if (listeners[i] == nullptr)
		{
			listeners[i] = listener;
			break;
		}

		// Simple security check to avoid adding the same listener twice
		else if (listeners[i] == listener) break;
	}
}*/

/*#include "Collider.h"

Collider::Collider(ColliderType type)
	: mType(type)
{
	mDebugTexture = nullptr;
}

Collider::~Collider() {

	if (mDebugTexture) {

		delete mDebugTexture;
		mDebugTexture = nullptr;
	}
}

void Collider::SetDebugTexture(Textures* texture) {

	delete mDebugTexture;
	mDebugTexture = texture;
	mDebugTexture->Update(this);
}

Collider::ColliderType Collider::GetType() {

	return mType;
}

void Collider::Render() {

	if (DEBUG_COLLIDERS) {

		mDebugTexture->GetSize();
	}
}*/
/*#include "Collider.h"

PhysicBody::PhysicBody()
{

}

PhysicBody::~PhysicBody()
{
}

PhysicBody::PhysicBody(fPoint pos, float width, float height, BodyType type)
{
	this->position = pos;
	this->type = type;
	this->width = width;
	this->height = height;
	this->shape = ShapeType::RECTANGLE;
}

PhysicBody::PhysicBody(fPoint pos, float radius, BodyType type)
{
	this->position = pos;
	this->type = type;
	this->radius = radius;
	this->shape = ShapeType::CIRCLE;
}

PhysicBody::PhysicBody(PhysicBody& cp)
{
	this->position = cp.position;
	this->type = cp.type;
	this->width = cp.width;
	this->height = cp.height;
	this->radius = cp.radius;
	this->shape = cp.shape;
	
}

void PhysicBody::OnCollision(PhysicBody* col)
{
}

void PhysicBody::OnCollisionTouch(PhysicBody* col)
{
}

void PhysicBody::OnCollisionLeave(PhysicBody* col)
{
}*/
#include "Collider.h"
#include "Module.h"
//#include "Enemy.h"

#include "SDL/include/SDL.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) : rect(rectangle), type(type)
{
	listeners[0] = listener;
}

Collider::Collider(SDL_Rect rectangle, Type type, Enemy* point_, Module* listener) : rect(rectangle), type(type)
{
	listeners[0] = listener;
	point = point_;
}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

void Collider::AddListener(Module* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)
	{
		if (listeners[i] == nullptr)
		{
			listeners[i] = listener;
			break;
		}

		//Simple security check to avoid adding the same listener twice
		else if (listeners[i] == listener)
			break;
	}
}

