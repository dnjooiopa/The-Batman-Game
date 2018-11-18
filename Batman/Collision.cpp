#include "Collision.h"


Collision::Collision(RectangleShape& body) :
	body(body)
{

}

Collision::~Collision()
{
}

bool Collision::CheckCollision(Collision other)
{
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
	
	if (intersectX < -60 && intersectY < -40)
	{
		return true;
	}
	return false;
}
