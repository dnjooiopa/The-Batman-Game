#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Batarang.h"
#include "Collision.h"
using namespace sf;

class Player
{
public:
	Player();
	~Player();

	void setPlayer(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	void Update(float deltaTime, int hp, bool flying);
	void collide();
	bool checkPunch() { return cPunch; }
	Vector2f getPosition() { return Vector2f(body.getPosition()); }
	float getX() {return body.getPosition().x;}
	float getY() {return body.getPosition().y;}
	int curX() { return animation.currentImage.x; }
	int getMana() { return stamina; }
	bool checkDead() { return animation.j; }
	Vector2f Getposition() { return body.getPosition(); }
	Collision Getcollision() { return Collision(body); }
    RectangleShape body;
	bool faceRight;
	bool cShoot;
	int stamina;
private:
	Animation animation;
	bool crouchCheck;
	bool punchCheck;
	unsigned int row;
	float speed;
	float yVel;
	bool jump;
	bool punch;
	bool sPunch;
	bool cPunch;
	bool shoot;
	
	bool sShoot;
	bool canJump;
	float jumpHeight;
	float g;
	float defaultPosY;
	float totalTime;
	float totalTimeB;
	float delayButton;
	float totalTimeC;
	bool dead;

	Vector2f velocity;
	Vector2f pos;
	Music punchSound;
};

