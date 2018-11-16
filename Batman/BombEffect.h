#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
using namespace sf;

class BombEffect
{
public:
	BombEffect() {}
	~BombEffect() {}
	void setBombEffect(Texture* texture, Vector2u imageCount, float switchTime)
	{
		animation.setAnimation(texture, imageCount, switchTime);
		row = 0;
		body.setSize(Vector2f(150.0f, 150.0f));
		body.setTexture(texture);
	}
	void setPosition(Vector2f getPosition)
	{
		body.setPosition(getPosition);
	}
	void Update(float deltaTime, bool bombCheck) 
	{
		animation.bombUpdate(deltaTime, bombCheck);
		body.setTextureRect(animation.uvRect);
	}
	RectangleShape Draw()
	{
		return body;
	}
	int curX() { return animation.currentImage.x;}

private:
	RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceLeft;

};
