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
	void batarangUpdate(float posX);
	void batwingUpdate(int row, float deltaTime, bool faceRight);
	void bombUpdate(float deltaTime, bool bombCheck);
	IntRect uvRect;
	Vector2u currentImage;
	bool j;
private:
	Vector2u imageCount;
	bool i;
	float totalTime;
	float switchTime;
	int row;
};

