#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Batarang.h"
#include "BombEffect.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace sf;
using namespace std;

class GameRunning
{
public:
	GameRunning(Vector2u size,std::string name);
	~GameRunning();
	void defaultSetting();
	void GameControl();
	void timeElapse(float timeElapse);
	void setScore(std::string name);
	void drawMainMenu();
	void buttonCheck();
	bool mouseCheck(Text *text);
	void drawHighscore();
	void Playing();
	void mainStory();
	void playerControl();
	void enemyAttack();
	void batarangShoot();
	void statusBar();
	void enemyVectorUpdate();
	void specialItem();
	void Trap();

private:
	RenderWindow window;
	//game state
	int state;
	int exit;
	int runMenu;
	int gameStart;
	int showHighscore;
	int playerDead;
	bool viewCheck;
	bool gameEnd;
	//Sound
	Music bgSound;
	Music batFlying;
	Music itemCollect;
	Music bottleCollect;
	//texture display background
	Texture mainMenuTexture;
	sf:: Texture endTexture;
	Texture scene1Texture;
	Texture barTexture;
	Texture logoTexture;
	Sprite mainMenuSprite;
	Sprite endBackground;
	Sprite scene1;
	Sprite bar;
	Sprite logo;
	View camera;
	//Font
	Font font;
	Font font2;
	//Character Class
	Player player;
	Texture playerTexture;
	int playerScore;
	float d;
	int myHP;
	RectangleShape MANA;
	RectangleShape HP;
	int damaged;
	int posibleHit;

	Enemy normalEnemy;
	Texture normalEnemyTexture;
	Enemy bigEnemy;
	Texture bigEnemyTexture;
	float eSpeed;

	BombEffect bomb;
	Texture bombTexture;
	bool bombCheck;
	//Item Class
    Batarang batarang;
	Texture batarangTexture;
	Vector2f movement;
	int batNumber;
	bool shoot;
	bool isFire;

	Item item;
	Texture itemTexture;
	Item trap;
	Texture trapTexture;
	Item redbull;
	Texture redbullTexture;
	Item hpBot;
	Texture hpBotTexture;
	//Time and delay
	Clock clock;
	float time;
	unsigned int countTime;
	float deltaTime;
	float totalTimeButton;
	float delayButton;
	int select;
	bool msCheck;
	bool mCheck;

	//High Score 
	vector<pair<int, string>> scoreboard;
	ifstream loadFile;
	fstream myFile;

	//Class Vector
	vector<Enemy> enemyVec;
	vector<Item> itemVec;
	vector<Item> trapVec;
	vector<Item> potionVec;
	bool l;
	bool k;
	bool j;
	bool a;
	int n;
	int nTrap;
};

