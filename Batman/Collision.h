#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Collision
{
public:
	Collision(RectangleShape& body);
	~Collision();
	bool CheckCollision(Collision other);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
private:
	RectangleShape& body;
};

