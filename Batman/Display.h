#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Batarang.h"
#include "Batwing.h"
#include "BombEffect.h"
#include "Fire.h"
#include "Item.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
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
	void timeElapse(float timeElapse);
	void setScore(std::string name);
	void drawMainMenu();
	void buttonCheck();
	bool mouseCheck(Text *text);
	void drawHighscore();
	void setView(bool k);
	void moreStory();
	void Playing();
	void drawScene();
	void mainStory();
	void playerControl();
	void enemyAttack1();
	void enemyAttack2();
	void batarangShoot();
	void statusBar();
	bool playerisDead() {
		if (myHP == 0) return true;
		else return false;
	}
	void playMoreStory();
	void vectorUpdate1();
	void vectorUpdate2();
	void specialItem();
	void Trap();
	bool posCheck();
	int getSelect() { return select; }
	Font getFont() { return font; }
	bool msCheck;
	bool mCheck;
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

	Enemy normalEnemy;
	Texture normalEnemyTexture;

	Enemy berm;
	Texture bermTexture;

	Batarang batarang;
	Texture batarangTexture;
	Vector2f movement;
	int batNumber;

	Batwing batwing;
	Texture batwingTexture;

	BombEffect bomb;
	Texture bombTexture;
	bool bombCheck;

	Fire fire;
	Texture fireTexture;

	Item item;
	Texture itemTexture;

	Item trap;
	Texture trapTexture;

	unsigned int countTime;
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

	bool enemySpawn;
	bool spawnCheck;
	bool normalEnemyGetHit[4];
	bool normalEnemyGetBomb;
	bool bigEnemyGetHit;
	bool bigEnemyGetBomb;
	bool i;
	bool k;

	int myHP;
	RectangleShape HP;
	int damaged;
	int playerScore;
	bool getHit;
	int hit;

	vector<pair<int, string>> scoreboard;
	ifstream loadFile;

	vector<Enemy> enemyVec1;
	vector<Enemy> enemyVec2;
	vector<Item> trapVec;
	int n;

	Music batFlying;
	Music itemCollect;
};

