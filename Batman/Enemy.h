#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collision.h"
using namespace sf;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void setEnemy(Texture* texture, Vector2u imageCount, float switchTime, float speed,int hp);
	void setPosition(float posX);
	void Update(Vector2f playerPos, bool hit, float deltaTime);
	void Draw(RenderWindow &window);
	void setSpeed(float speed);
	float getX() { return body.getPosition().x; }
	float getY() { return body.getPosition().y; }
	int curX() { return animation.currentImage.x; }
	bool enemyDead() { return dead; }
	Vector2f getPosition() { return body.getPosition(); }
	RectangleShape draw() { return body; }
	Collision Getcollision() { return Collision(body); }

private:
	RectangleShape body;
	Animation animation;
	float speed;
	bool faceLeft;
	int row;
	bool checkMovement;
	int hp;
	bool dead;

};

