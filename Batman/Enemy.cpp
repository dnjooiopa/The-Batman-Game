#include "Enemy.h"
#include <iostream>

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
}

void Enemy::setEnemy(Texture * texture, Vector2u imageCount, float switchTime, float speed,int hp)
{
	animation.setAnimation(texture, imageCount, switchTime);
	this->speed = speed;
	this->hp = hp;
	faceLeft = true;
	dead = false;
	shot = false;
	body.setTexture(texture);
	body.setSize(Vector2f(1.5 * animation.uvRect.width, 1.5 * animation.uvRect.height));
}

void Enemy::setPosition(float posX)
{
	body.setPosition(posX, 700.0f - 1.5*animation.uvRect.height);
}

void Enemy::Update(Vector2f playerPos, float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);
	if (!dead)
	{
		row = 0;
		checkMovement = true;
		faceLeft = true;
		if (getX() > playerPos.x + 50)
			faceLeft = true;
		if (getX() + 50 < playerPos.x)
			faceLeft = false;
		if (getX() - playerPos.x <= 80 && getX() > playerPos.x)
		{
			row = 2;
			checkMovement = false;
			faceLeft = true;
		}
		if (playerPos.x - getX() <= 80 && getX() < playerPos.x)
		{
			row = 2;
			checkMovement = false;
			faceLeft = false;
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
	}
	//// Get Hit and Shot
	if (shot)
	{
		hp -= 400;
		shot = false;
	}
	if (hit)
	{
		hp -= 300;
		hit = false;
	}
	if (hp <= 0)
	{
		row = 3;
		dead = true;
	}

	animation.enemyUpdate(row, deltaTime, faceLeft, dead);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

	if (Keyboard::isKeyPressed(Keyboard::B))
	{
		hp = 1000;
		dead = false;
	}

}

void Enemy::getShot(bool bomb)
{
	this->shot = bomb;
}

void Enemy::getHit(bool hit)
{
	this->hit = hit;
}

void Enemy::Draw(RenderWindow &window)
{
	window.draw(body);
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}
