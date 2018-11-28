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

	void setEnemy(Texture* texture, Vector2u imageCount, float switchTime, float speed,int hp, int type);
	void setPosition(float posX);
	void Update(Vector2f playerPos, float deltaTime);
	void getShot(bool shot);
	void getPunch(bool hit);
	bool getHit() { return hit; }
	void setSpeed(float speed);
	void hpBar();
	int getHP() { return hp; }
	float getSpeed() { return speed; }
	float getX() { return body.getPosition().x; }
	float getY() { return body.getPosition().y; }
	int curX() { return animation.currentImage.x; }
	bool checkDead() { return animation.j; }
	int getRow() { return row; }
	int getType() { return type; }
	Vector2f getPosition() { return body.getPosition(); }
	Collision Getcollision() { return Collision(body); }	
	RectangleShape body;
	RectangleShape HP;
	bool faceLeft;
	bool punchCheck;
private:
	Animation animation;
	float speed;
	int row;
	bool checkMovement;
	int hp;
	int fullHP;
	int type;
	bool dead;
	bool shot;
	bool hit;
	
};

