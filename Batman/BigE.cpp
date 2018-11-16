#include "BigE.h"
#include <iostream>

BigE::BigE()
{
}

BigE::~BigE()
{
}

void BigE::setBigE(Texture * texture, Vector2u imageCount, float switchTime, float speed)
{
	animation.setAnimation(texture, imageCount, switchTime);
	this->speed = speed;
	faceLeft = true;
	totalTime = 0;

	body.setTexture(texture);
	body.setSize(Vector2f(1.5 * animation.uvRect.width, 1.5 * animation.uvRect.height));

}

void BigE::setPosition(float posX)
{
	body.setPosition(posX, 700.0f - 1.5*animation.uvRect.height);
}


void BigE::Update(Vector2f playerPos, bool hit, float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);
	row = 0;
	checkMovement = true;
	faceLeft = true;
	if (getX() > playerPos.x + 50)
		faceLeft = true;
	if (getX() + 50 < playerPos.x)
		faceLeft = false;
	if (getX() - playerPos.x <= 100 && getX() > playerPos.x)
	{
		checkMovement = false;
		faceLeft = true;
		row = 2;
	}
	if (playerPos.x - getX() <= 100 && getX() < playerPos.x)
	{
		checkMovement = false;
		faceLeft = false;
		row = 2;
	}

	if (checkMovement && faceLeft)
	{
		movement.x -= speed * deltaTime;
	}
	else if (checkMovement && !faceLeft)
	{
		movement.x += speed * deltaTime;
	}

	if (movement.x == 0.0f)
	{
		if (row == 2)
			row = 2;
		else
			row = 1;
	}
	else
	{

		if (movement.x < 0.0f)
			faceLeft = true;
		else
			faceLeft = false;
	}
	//// Get Hit
	if (hit) row = 3;

	animation.enemyUpdate(row, deltaTime, faceLeft);
	body.setTextureRect(animation.uvRect);
	body.move(movement);


}

void BigE::Draw(RenderWindow &window)
{
	window.draw(body);
}