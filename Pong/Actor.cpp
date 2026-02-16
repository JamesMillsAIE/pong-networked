#include "Actor.h"

Actor::Actor(const Vector2 location, const Vector2 size, const float rotation, const Color tint)
	: location{ location }, size{ size }, rotation{ rotation }, tint{ tint }
{}

Actor::~Actor() = default;

void Actor::BeginPlay()
{}

void Actor::Tick(float dt)
{}

void Actor::Render()
{}

void Actor::EndPlay()
{}

Rectangle Actor::Bounds() const
{
	return
	{
		location.x,
		location.y,
		size.x,
		size.y
	};
}
