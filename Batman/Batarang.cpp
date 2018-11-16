#include "Batarang.h"

Batarang::Batarang()
{
}
Batarang::~Batarang()
{
}

void Batarang::setBatarang(Texture * texture, Vector2u imageCount, float switchTime)
{
	animation.setAnimation(texture, imageCount, switchTime);
	body.setTexture(texture);
	body.setSize(Vector2f(0.5 * animation.uvRect.width, 0.5 * animation.uvRect.height));
}

void Batarang::Update(float deltaTime)
{
	animation.batarangUpdate(deltaTime);
	body.setTextureRect(animation.uvRect);
}

void Batarang::setPosition(Vector2f getPosition)
{
	body.setPosition(getPosition);
}

float Batarang::getX()
{
	return body.getPosition().x;
}

float Batarang::getY()
{
	return body.getPosition().y;
}
