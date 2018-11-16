#include "Batwing.h"

Batwing::Batwing()
{
}

Batwing::~Batwing()
{
}

void Batwing::setBatwing(Texture* texture, Vector2u imageCount, float switchTime, float speed)
{
	animation.setAnimation(texture, imageCount, switchTime);
	this->speed = speed;
	row = 0;
	faceRight = true;
	body.setScale(Vector2f(1.5f, 1.5f));
	body.setPosition(500.0f, 300.0f);
	body.setTexture(*texture);
}


void Batwing::Update(float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		row = 0;
		movement.x -= speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		row = 0;
		movement.x += speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		row = 2;
		movement.y -= speed * deltaTime;;
		if (faceRight)
			movement.x += 0.001f;
		else
			movement.x -= 0.001f;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{

		row = 1;
		movement.y += speed * deltaTime;;
		if (faceRight)
			movement.x += 0.001f;
		else
			movement.x -= 0.001f;
	}

	if (movement.x == 0.0f && movement.y == 0)
	{
		row = 0;
	}
	else
	{
		if (movement.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.batwingUpdate(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Batwing::setPosition(Vector2f pos)
{
}

float Batwing::getX()
{
	return 0.0f;
}

float Batwing::getY()
{
	return 0.0f;
}
