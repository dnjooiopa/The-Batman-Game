#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
using namespace sf;
class Item
{
public:
	Item();
	~Item();
	void setItem(Texture* texture)
	{	
		imgHeight = texture->getSize().y*0.5;
		imgWidth = texture->getSize().x*0.5f;
		body.setTexture(texture);
		body.setSize(Vector2f(imgWidth, imgHeight));
		body.setPosition(Vector2f(-500, 0));
		
		g = 3000.0f;
	}
	void setPosition(Vector2f pos){ body.setPosition(pos); }
	float getX() { return body.getPosition().x; }
	float getY() { return body.getPosition().y; }
	Collision Getcollision() { return Collision(body); }

	void Update(float deltaTime)
	{
		velocity.x = 0;
		velocity.y = sqrt(2 * g * 700);
		body.move(velocity * deltaTime);
		if (getY() >= 700 - imgHeight)
		{
			setPosition(Vector2f(getX(), 700 - imgHeight));
			velocity.y = 0;
		}
	}

	RectangleShape body;
private:

	Vector2f velocity;
	float g;
	float imgHeight;
	float imgWidth;
};

