#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation
{
public:
	Animation();
	~Animation();
	void setAnimation(Texture* texture, Vector2u imageCount, float switchTime);
	void playerUpdate(int row, float deltaTime, bool faceRight, bool punch, bool jump, bool shoot, float posY);
	void enemyUpdate(int row, float deltaTime, bool faceLeft, bool dead);
	void batarangUpdate(float deltaTime);
	void batwingUpdate(int row, float deltaTime, bool faceRight);
	void bombUpdate(float deltaTime, bool bombCheck);
	IntRect uvRect;
	Vector2u currentImage;

private:
	Vector2u imageCount;
	bool i;
	bool j;
	float totalTime;
	float switchTime;
	int row;
};

