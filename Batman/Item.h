#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
using namespace sf;
class Item
{
public:
	Item();
	~Item();
	void setItem(Texture* texture, float g)
	{	
		imgHeight = texture->getSize().y;
		imgWidth = texture->getSize().x;
		body.setTexture(texture);
		body.setSize(Vector2f(imgWidth, imgHeight));
		body.setPosition(Vector2f(-500, 0));
		
		this->g = g;
	}
	Vector2f getPosition() { return body.getPosition(); }
	void setPosition(Vector2f pos){
		if (pos.x < 50)
			body.setPosition(Vector2f(pos.x + 1500, pos.y));
		else if (pos.x > 9000)
			body.setPosition(Vector2f(pos.x - 1500, pos.y));
		else
			body.setPosition(pos);
	}
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
	float g;
private:

	Vector2f velocity;
	float imgHeight;
	float imgWidth;
};

