#include "Player.h"
#include <iostream>

Player::Player()
{
}

Player::~Player()
{
}

void Player::setPlayer(Texture *texture, Vector2u imageCount, float switchTime, float speed)
{
	animation.setAnimation(texture, imageCount, switchTime);
	this->speed = speed;
	row = 0;
	crouchCheck = false;
	punchCheck = false;
	faceRight = true;
	punch = false;
	cPunch = false;
	sPunch = true;
	jump = false;
	shoot = false;
	cShoot = false;
	sShoot = false;
	canJump = true;
	dead = false;
	jumpHeight = 350.0f;
	g = 2800.0f;
	defaultPosY = 700.0f - (1.5 * animation.uvRect.height);
	punchSound.openFromFile("sound/punch2.ogg");
	punchSound.setVolume(20);
	totalTime = 0;
	totalTimeB = 0;
	totalTimeC = 0;
	delayButton = 0.05f;
	body.setTexture(texture);
	body.setSize(Vector2f(1.5 * animation.uvRect.width, 1.5 * animation.uvRect.height));
	body.setPosition(640.0f, defaultPosY);
	stamina = 10000;
}

void Player::Update(float deltaTime, int hp, bool flying)
{
    velocity.x = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::A) && !crouchCheck && !punchCheck && !shoot && getX()>125)
	{
		row = 0;
		velocity.x -= speed;
		shoot = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && !crouchCheck && !punchCheck && !shoot && getX() < 9480)
	{
		row = 0;
		velocity.x += speed;
		shoot = false;
	}

	//Player Punch
	if ((Keyboard::isKeyPressed(Keyboard::K)|| Mouse::isButtonPressed(Mouse::Left)) && !jump && !Keyboard::isKeyPressed(Keyboard::LShift))
	{
		totalTime += deltaTime;
		if (totalTime >= delayButton)
		{
			totalTime -= delayButton;
			punch = true;
		    punchCheck = true;
			row = 3;
		}
		
	}
	else {
		punchCheck = false;
		totalTime = 0;
	}

	//Player Jump
	if (Keyboard::isKeyPressed(Keyboard::W) && canJump)
	{
		canJump = false;
		jump = true;
		velocity.y = -sqrtf(2.0f * g * jumpHeight);
	}

	//Player Crouch
	if (Keyboard::isKeyPressed(Keyboard::S) && !jump)
	{
		shoot = false;
		crouchCheck = true;
		row = 4;
		
	}
	else
	{
		crouchCheck = false;
	}

	//////Throw batarang
	if ((Keyboard::isKeyPressed(Keyboard::J)|| Mouse::isButtonPressed(Mouse::Right)) && !Keyboard::isKeyPressed(Keyboard::LShift) && !shoot && !crouchCheck && !flying )
	{
		totalTimeB += deltaTime;

		if (totalTimeB >= delayButton)
		{
			totalTimeB -= delayButton;
			shoot = true;
			sShoot = true;
			row = 7;
		}
	}
	else {
		totalTimeB = 0;
	}

	////////////////////////////////////////////////////
	if (velocity.x == 0.0f)
	{
		row = 1;
		if (punch)
		{
			row = 3;
			if (animation.currentImage.x == 2 && sPunch)
			{	
				cPunch = true;
				punchSound.setPlayingOffset(Time(seconds(0)));
				punchSound.play();
				sPunch = false;
			}
			else
			{
				cPunch = false;
			}
			
			if (animation.currentImage.x >= 5)
			{
				sPunch = true;
				punch = false;
			}
		}
		if (jump)
		{
			if (velocity.y < 0)
				row = 2;
			else
				row = 8;
		}
		if (shoot)
		{
			row = 7;

			if (animation.currentImage.x == 3 && sShoot)
			{
				cShoot = true;
				sShoot = false;
			}

			if (animation.currentImage.x >= 5)
			{
				shoot = false;
			}

		}
		if (crouchCheck)
		{
			row = 4;
			if (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::K)|| Mouse::isButtonPressed(Mouse::Left)))
			{
				punch = true;
				punchCheck = true;
				row = 6;
			}
			else
			{
				punchCheck = false;
			}
			if (punch)
			{
				row = 6;

				if (animation.currentImage.x >= 5)
				{
					punch = false;

				}
			}
		}
	}
	else
	{
		if (jump) { 
			if (velocity.y < 0)
				row = 2;
			else
				row = 8;
		}
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	if (stamina > 10000) stamina = 10000;
	if ((Keyboard::isKeyPressed(Keyboard::A)|| Keyboard::isKeyPressed(Keyboard::D)) && Keyboard::isKeyPressed(Keyboard::LShift) && stamina>0 && !crouchCheck && !(Keyboard::isKeyPressed(Keyboard::K)))
	{
		totalTimeC += deltaTime;
		if (totalTimeC >= delayButton)
		{
			totalTimeC -= delayButton;
			if(stamina>0) stamina-=100;
		}

		if (faceRight)
			velocity.x = 800;
		else
			velocity.x = -800;
	}
	
	if (getY() < 700.0f - (1.5 * animation.uvRect.height))	velocity.y += g * deltaTime;
	if (getX() < 50) body.setPosition(Vector2f(50, getY()));
	if (getX() > 9450) body.setPosition(Vector2f(9450, getY()));
	if (hp == 0)
	{
		velocity.x = 0;
		velocity.y = 0;
		dead = true;
		row = 10;
	}

	animation.playerUpdate(row, deltaTime, faceRight, punch, jump, shoot, getY(), dead);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	collide();
}

void Player::collide()
{
	if (getY() >= defaultPosY)
	{
		velocity.y = 0.0f;
		canJump = true;
		jump = false;
		body.setPosition(Vector2f(getX(), defaultPosY));
	}
}