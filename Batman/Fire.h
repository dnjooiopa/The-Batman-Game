#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Fire
{
public:
	Fire();
	~Fire();
	void setFire(Texture* texture, Vector2u imageCount, float switchTime)
	{
		this->imageCount = imageCount;
		this->switchTime = switchTime;
		totalTime = 0.0f;
		currentImage.x = 0;
		row = 0;
		uvRect.width = texture->getSize().x / float(imageCount.x);
		uvRect.height = texture->getSize().y / float(imageCount.y);

		body.setTexture(texture);
		body.setSize(Vector2f(uvRect.width,uvRect.height));
	}
	void fireAnimation(float deltaTime)
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
				row++;
				if (row > imageCount.y-1) row = 0;
			}
		}

		uvRect.top = currentImage.y * uvRect.height;
		uvRect.left = currentImage.x * uvRect.width;
	}
	void Update(float deltaTime)
	{
		fireAnimation(deltaTime);
		body.setTextureRect(uvRect);
	}
	
	RectangleShape draw() { return body; }

	void setPosition(Vector2f pos)
	{
		body.setPosition(Vector2f(pos.x, pos.y-200.0f));
	}


private:
	RectangleShape body;
	IntRect uvRect;
	Vector2u currentImage;
	Vector2u imageCount;
	float totalTime;
	float switchTime;
	int row;

};

