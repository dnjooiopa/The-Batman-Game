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
	void enemyUpdate(int row, float deltaTime, bool faceLeft);
	void bigUpdate(int row, float deltaTime, bool faceLeft);
	void batarangUpdate(float deltaTime);
	void batwingUpdate(int row, float deltaTime, bool faceRight);
	
	IntRect uvRect;

	Vector2u imageCount;
	Vector2u currentImage;


private:
	bool i;
	float totalTime;
	float switchTime;
	int row;

};

