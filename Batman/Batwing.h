#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
using namespace sf;

class Batwing
{
public:
	Batwing();
	~Batwing();
	void setBatwing(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	void Update(float deltaTime);
	void setPosition(Vector2f pos);
	float getX();
	float getY();
	Sprite body;

private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};
