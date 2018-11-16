#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class NormalEnemyAnimation
{
public:
	NormalEnemyAnimation();
	~NormalEnemyAnimation();

	void setAnimation(Texture* texture, Vector2u imageCount, float switchTime);
	void Update(int row, float deltaTime, bool faceRight);
	IntRect uvRect;

private:
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	int row;

};



