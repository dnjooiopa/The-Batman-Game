#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "NormalEnemy.h"
#include "BigE.h"
#include "Batarang.h"
#include "Batwing.h"
#include "BombEffect.h"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace sf;
using namespace std;

class Display
{
public:
	Display();
	~Display();
	void setWindow(RenderWindow *window);
	void setDT(float deltaTime);
	void drawMainMenu();
	void buttonCheck();
	bool mouseCheck(Text *text);
	void drawHighscore();
	void setView(bool k);
	void moreStory();
	void Playing();
	void drawScene();
	void mainStory();
	void enemyAI();
	void bermAI();
	void batarangShoot();
	void statusBar();
	void playerDead();
	void playMoreStory();
	bool getMouseCheck() { return mCheck; }
	int getSelect() { return select; }
	

private:
	View camera;
	RenderWindow *window;
	Texture mainMenuTexture;
	Sprite mainMenuSprite;
	Texture scene1Texture;
	Sprite scene1;
	Texture scene2Texture;
	Sprite scene2;
	Texture barTexture;
	Sprite bar;
	Texture logoTexture;
	Sprite logo;
	Font font;

	Player player;
	Texture playerTexture;

	NormalEnemy normalEnemy;
	Texture normalEnemyTexture;

	BigE berm;
	Texture bermTexture;

	Batarang batarang;
	Texture batarangTexture;
	Vector2f movement;

	Batwing batwing;
	Texture batwingTexture;

	BombEffect bomb;
	Texture bombTexture;
	bool bombCheck;

	float deltaTime;
	float totalTime;
	float d;
	int x;
	bool shoot;
	bool isFire;
	float dethatimebullet;
	int select;
	float totalTimeButton;
	float delayButton;
	bool mCheck;

	bool enemySpawn;
	bool spawnCheck;
	bool normalEnemyGetHit;
	bool bigEnemyGetHit;

	int myHP;
	RectangleShape HP;
	int damaged;
	int playerScore;
	bool getHit;
	int hit;

	vector<pair<int, string>> scoreboard;
	ifstream loadFile;

};

