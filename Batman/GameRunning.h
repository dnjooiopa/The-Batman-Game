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
#include <Windows.h>
using namespace sf;
using namespace std;

class GameRunning
{
public:
	GameRunning(Vector2u size,std::string name);
	~GameRunning();
	void gameReset();
	void MainMenu();
	void timeElapse(float timeElapse);
	void setScore(std::string name);
	void drawMainMenu();
	void buttonCheck();
	bool mouseCheck(Text *text);
	void sortHighscore();
	void drawHighscore();
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
	void vectorUpdate1();
	void vectorUpdate2();
	void specialItem();
	void Trap();
	

private:
	RenderWindow window;
	Clock clock1;
	Clock clock2;
	bool running;
	int state;
	int exit;
	int runMenu;
	int gameStart;
	int showHighscore;
	int playerDead;
	Music bgSound;
	Texture endTexture;
	Sprite endBackground;
	/////////////////////////////
	View camera;
	Texture mainMenuTexture;
	Sprite mainMenuSprite;
	Texture scene1Texture;
	Sprite scene1;
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

	Item redbull;
	Texture redbullTexture;

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
	bool msCheck;
	bool mCheck;

	bool viewCheck;
	bool enemySpawn;
	bool spawnCheck;
	bool normalEnemyGetHit[4];
	bool normalEnemyGetBomb;
	bool bigEnemyGetHit;
	bool bigEnemyGetBomb;
	bool i;
	bool k;
	bool j;
	bool a;
	bool gameEnd;

	int myHP;
	RectangleShape HP;
	int damaged;
	int playerScore;
	bool getHit;
	int hit;

	RectangleShape MANA;

	vector<pair<int, string>> scoreboard;
	ifstream loadFile;

	vector<Enemy> enemyVec1;
	vector<Enemy> enemyVec2;
	vector<Item> itemVec;
	vector<Item> trapVec;
	vector<Item> redbullVec;

	int n;

	Music batFlying;
	Music itemCollect;
	Music bottleCollect;
};

