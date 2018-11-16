#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collision.h"
using namespace sf;

class NormalEnemy
{
public:
	NormalEnemy();
	~NormalEnemy();

	void setEnemy(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	void setPosition(float posX);
	void Update(Vector2f playerPos, bool hit, float deltaTime);
	void Draw(RenderWindow &window);
	float getX() { return body.getPosition().x; }
	float getY() { return body.getPosition().y; }
	int curX() { return animation.currentImage.x; }
	void setSpeed(float speed);
	RectangleShape draw() { return body; }
	Collision Getcollision() { return Collision(body); }

private:
	RectangleShape body;
	Animation animation;
	float speed;
	bool faceLeft;
	int row;
	bool checkMovement;

};

