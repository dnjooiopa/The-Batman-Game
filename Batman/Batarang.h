#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collision.h"
using namespace sf;

class Batarang
{
public:
	Batarang();
	~Batarang();
	void setBatarang(Texture* texture, Vector2u imageCount, float switchTime);
	void Update(float deltaTime);
	void setPosition(Vector2f pos);
	float getX();
	float getY();
	RectangleShape body;
	Vector2f Getposition() { return body.getPosition(); }
	Collision Getcollision() { return Collision(body); }
private:
	Animation animation;
};

