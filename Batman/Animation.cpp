#include "Animation.h"
#include "iostream"
using namespace std;

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::setAnimation(Texture *texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	row = 0;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
	i = true;

}

////////////////////////Update//////////////
/////Player
void Animation::playerUpdate(int row, float deltaTime, bool faceRight, bool punch, bool jump, bool shoot, float posY)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if ((punch&&i) || (jump&&i) || (shoot&&i))
	{
		currentImage.x = 0;
		i = false;
	}

	if (posY < 400 && row == 2) currentImage.x = 3;//jump up
	
	if (row == 10)
		switchTime = 0.25;
	else if (row == 8)
		switchTime = 0.2;
	else
		switchTime = 0.08;
	
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
			i = true;
		}
	}
	

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
//////Enemy
void Animation::enemyUpdate(int row, float deltaTime, bool faceLeft)
{
	
	if (row == 2)
		switchTime = 0.2;
	else
		switchTime = 0.08;
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceLeft)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
void Animation::bigUpdate(int row, float deltaTime, bool faceLeft)
{
	if (row == 2)
		switchTime = 0.2;
	else
		switchTime = 0.08;
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceLeft)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
/////batarang
void Animation::batarangUpdate(float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;
	uvRect.left = currentImage.x * uvRect.width;
}

void Animation::batwingUpdate(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;


	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
