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
		if(bombCheck) sbomb = true;
		if (curX() == 1 && sbomb)
		{
			bombSound.setPlayingOffset(Time(seconds(0)));
			bombSound.play();
			sbomb = false;
			std::cout << curX() << std::endl;
		}
		//std::cout << animation.currentImage.x << std::endl;
		animation.bombUpdate(deltaTime, !sbomb);
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
	bool sbomb;
	bool bombCheck;
	Music bombSound;

};
