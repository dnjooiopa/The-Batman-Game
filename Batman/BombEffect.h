#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>
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
		body.setPosition(Vector2f(-200, 0));
		bombSound.openFromFile("sound/bomb.ogg");
		bombSound.setVolume(35);
		sbomb = false;
	}
	void setBomb(bool bombCheck)
	{
		this->bombCheck = bombCheck; 
	}
	void setPosition(Vector2f getPosition)
	{
		body.setPosition(getPosition);
	}
	void Update(float deltaTime) 
	{
		animation.bombUpdate(deltaTime, bombCheck);
		if (bombCheck)
		{
			bombSound.setPlayingOffset(Time(seconds(0)));
			bombSound.play();
			bombCheck = false;
		}
		
		body.setTextureRect(animation.uvRect);
	}
	int curX() { return animation.currentImage.x;}
	bool showBomb() { return !animation.i; }
	RectangleShape body;
private:

	Animation animation;
	unsigned int row;
	float speed;
	bool faceLeft;
	bool sbomb;
	bool bombCheck;
	Music bombSound;

};
