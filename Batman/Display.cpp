#define _CRT_SECURE_NO_WARNINGS 0
#include "Display.h"

Display::Display()
{
	//MainMenu
	mainMenuTexture.loadFromFile("sprite/background2.png");
	mainMenuSprite.setTexture(mainMenuTexture);
	//Logo
	logoTexture.loadFromFile("sprite/logo.png");
	logo.setTexture(logoTexture);
	logo.setScale(0.35f, 0.35f);

	//Scene1
	scene1Texture.loadFromFile("sprite/scene1.png");
	scene1.setTexture(scene1Texture);
	scene1.setScale(Vector2f(1.0f, 1.0f));
	//Scene2
	scene2Texture.loadFromFile("sprite/scene2.png");
	scene2.setTexture(scene2Texture);
	scene2.setScale(Vector2f(1.0f, 1.0f));

	//Bar
	barTexture.loadFromFile("sprite/barTest.png");
	bar.setTexture(barTexture);

	//Player
	playerTexture.loadFromFile("sprite/batman2.png");
	player.setPlayer(&playerTexture, Vector2u(6, 11), 0.08f, 300.0f);

	//normalEnemy
	normalEnemyTexture.loadFromFile("sprite/nV.png");
	normalEnemy.setEnemy(&normalEnemyTexture, Vector2u(4, 4), 0.08f, 150.0f, 500);

	//bigEnemy
	bermTexture.loadFromFile("sprite/bigEnemy.png");
	berm.setEnemy(&bermTexture, Vector2u(6, 4), 0.08f, 120.0f, 1500);

	//Batarang
	batarangTexture.loadFromFile("sprite/batarang.png");
	batarang.setBatarang(&batarangTexture, Vector2u(4, 1), 0.08f);

	//Batwing
	batwingTexture.loadFromFile("sprite/batwing.png");
	batwing.setBatwing(&batwingTexture, Vector2u(2, 3), 0.08f, 500.0f);

	//Bomb
	bombTexture.loadFromFile("sprite/bomb.png");
	bomb.setBombEffect(&bombTexture, Vector2u(6, 1), 0.12f);
	
	//firetest
	fireTexture.loadFromFile("sprite/fireT.png");
	fire.setFire(&fireTexture, Vector2u(4, 4), 0.07f);
	fire.setPosition(Vector2f(150.0f, 500.0f));

	//font
	font.loadFromFile("font/batmfa.ttf");

	//player
	x = 0;
	shoot = false;
	enemySpawn = false;
	spawnCheck = true;
	isFire = false;
	select = 1;
	totalTimeButton = 0;
	delayButton = 0.07;
	mCheck = false;
	msCheck = false;
	batNumber = 100;

	//enemy
	n = 5;
	for(int i=0;i<n;i++)
		normalEnemyGetHit[i]= false;
	
	normalEnemyGetBomb = false;
	bigEnemyGetHit = false;
	bigEnemyGetBomb = false;
	

	//HP
	myHP = 100000;
	playerScore = 0;
	HP.setFillColor(Color::Red);//૵��
	hit = 4;

	//HighScore
	loadFile.open("score.txt");
	while (!loadFile.eof()) {
		string tempName;
		int tempScore;
		loadFile >> tempName >> tempScore;
	//	cout << ">> \"" << tempName << "\" " << tempScore << endl;
		scoreboard.push_back({ tempScore,tempName });
	}
	sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());

	////////////
	test = true;
}

Display::~Display()
{
	
}

void Display::setWindow(RenderWindow *window)
{
	this->window = window;
}

void Display::setDT(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void Display::timeElapse(float timeElapse)
{
	this->countTime = int(timeElapse);
}

void Display::setView(bool k)
{
	if (k)
	{
		camera.setCenter(Vector2f(player.getX(), scene1Texture.getSize().y / 2.0f));
		camera.setSize(Vector2f(1280.0f, scene1Texture.getSize().y));
	}
	else
	{
		camera.setCenter(Vector2f(mainMenuTexture.getSize().x / 2.0f, mainMenuTexture.getSize().y / 2.0f));
		camera.setSize(Vector2f(mainMenuTexture.getSize()));
	}
	
	window->setView(camera);
}
void Display::moreStory()
{
	window->clear();
	window->draw(scene2);
	playMoreStory();
	statusBar();
	window->display();
}
///////////////////////////////////MainMenu//////////////////////////////////
void Display::drawMainMenu()
{
	Text textPlaygame, textExit, textScore, textName;
	textPlaygame.setFont(font);//Play Game
	textPlaygame.setString("PLAY GAME");
	textPlaygame.setCharacterSize(40);
	textPlaygame.setFillColor(sf::Color::White);
	textPlaygame.setPosition(900, 200);
	textScore.setFont(font);//Score
	textScore.setString("Score");
	textScore.setCharacterSize(40);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(895, 300);
	textExit.setFont(font);//Exit
	textExit.setString("Exit");
	textExit.setCharacterSize(40);
	textExit.setFillColor(sf::Color::White);
	textExit.setPosition(895, 400);
	textName.setFont(font);//Name
	textName.setString("KITTISAK PHORMRAKSA\n\n61010092");
	textName.setCharacterSize(20);
	textName.setFillColor(sf::Color::White);
	textName.setPosition(950, 20);

	
	if (select == 1 || mouseCheck(&textPlaygame))
	{
		select = 1;
		textPlaygame.setStyle(sf::Text::Bold);
		logo.setPosition(770, 200);
		msCheck = mouseCheck(&textPlaygame);
	}
	else
	{
		textPlaygame.setStyle(Text::Regular);
	}

	if (select == 2 || mouseCheck(&textScore))
	{	
		select = 2;
		textScore.setStyle(sf::Text::Bold);
		logo.setPosition(770, 300);
		msCheck = mouseCheck(&textScore);
	}
	else
	{
		textScore.setStyle(Text::Regular);
	}

	if (select == 3 || mouseCheck(&textExit))
	{
		select = 3;
		textExit.setStyle(sf::Text::Bold);
		logo.setPosition(770, 400);
		msCheck = mouseCheck(&textExit);
	}
	else
	{
		textExit.setStyle(Text::Regular);
	}
	buttonCheck();
	window->clear();
	window->draw(mainMenuSprite);
	window->draw(logo);
	window->draw(textPlaygame);
	window->draw(textScore);
	window->draw(textExit);
	window->draw(textName);
	window->display();
}
void Display::buttonCheck()
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		totalTimeButton += deltaTime;
		if (totalTimeButton >= delayButton)
		{
			totalTimeButton -= delayButton;
			select--;
		}
		if (select == 0)
			select = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		totalTimeButton += deltaTime;
		if (totalTimeButton >= delayButton)
		{
			
			totalTimeButton -= delayButton;
			select++;
		}
		if (select == 4)
			select = 1;
	}
	else totalTimeButton = 0;
	
}
bool Display::mouseCheck(Text *text)
{
	Vector2f mousePos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
	if (text->getGlobalBounds().contains(mousePos))
		return true;
	else 
		return false;
}
void Display::drawHighscore()
{
	int cnt = 0;  //��С�ȵ�ǹѺ
	window->clear();
	for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i)
	{
		++cnt;
		if (cnt > 5) break;                       //����͵�ǹѺ�Թ 5 ��騺��÷ӧҹ
		Text a, b, highScore,textBack;                     //��С�� Text
		a.setString(to_string(i->first));         //���ͧ�ҡ��Ҥ�ṹ�� integer �֧��ͧ�ӡ���ŧ�� string ��͹�����ʴ��� (first ���pair ��Ƿ��˹�� =>int)
		a.setFont(font);                          //��õ�駤�� Font ��ṹ
		a.setCharacterSize(40);                   //��駤�Ң�Ҵ Font ��ṹ
		a.setFillColor(Color::White);
		a.setPosition(720, 80 + (80 * cnt));      //��駤�ҵ��˹��ʴ��Ţͧ��ṹ ���������ҵ��˹����ŧ�ҵ���� 80 ˹���
		window->draw(a);                           //�ʴ��Ť�ṹ
		b.setString(i->second);					 // (second ���pair ��Ƿ���ͧ =>string) 
		b.setFont(font);                        //��õ�駤�� Font ���ͼ�����
		b.setCharacterSize(40);                   //��駤�Ң�Ҵ Font ���ͼ�����
		b.setFillColor(Color::White);
		b.setPosition(320, 80 + (80 * cnt));      //��駤�ҵ��˹��ʴ��Ţͧ���ͼ����� ���������ҵ��˹����ŧ�ҵ���� 80 ˹���
		window->draw(b);                           //�ʴ��Ū��ͼ�����
		highScore.setFont(font);
		highScore.setString("HIGH SCORE");
		highScore.setCharacterSize(50);
		highScore.setFillColor(sf::Color::White);
		highScore.setPosition(455, 30);
		window->draw(highScore);
		textBack.setFont(font);
		textBack.setString("BACK");
		textBack.setCharacterSize(35);
		textBack.setFillColor(sf::Color::White);
		textBack.setPosition(40, 25);
		if (mouseCheck(&textBack))
		{
			mCheck = true;
			textBack.setStyle(sf::Text::Bold);
		}
		else
		{
			textBack.setStyle(Text::Regular);
			mCheck = false;
		}
		window->draw(textBack);
	}
	window->display();
}

/////////////////////////////////Display////////////////////////////////////
void Display::Playing()
{   
	window->clear();
	drawScene();
	mainStory();
	//batwing.Update(deltaTime);
	//window->draw(batwing.body);
	statusBar();
	fire.setPosition(Vector2f(player.getX()-100, player.getY() - 100));
	//fire.Update(deltaTime);//fire
	//window->draw(fire.draw());//fire
	window->display();


}

/////////////Camera
void Display::drawScene()
{
	if (player.getX() >= 640 && player.getX() < scene1Texture.getSize().x - 680)
	{
		x = 100;
		camera.move((Vector2f(player.getX() + x, 0.0f) - Vector2f(camera.getCenter().x, 0.0f)) * deltaTime * 5.0f);
	}
	else
	{
		x = 0;
	}
	window->setView(camera);
	window->draw(scene1);
}

///////////////////Main Story////////////////////////////////////////
void Display::mainStory()
{
	//////////////// Normal Enemy Fighting Check
	if (player.getX() >= 1 && spawnCheck)
	{
		enemySpawn = true;
		//normalEnemy.setPosition(player.getX()+500.0f);
     	//berm.setPosition(player.getX() + 1000.0f);
		spawnCheck = false;
		vectorSet();
	}
	if (enemySpawn)
	{
		vectorUpdate();
		enemyAttack();
	}
	batarangShoot();
	playerControl();
	
}

void Display::playerControl()
{
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (enemyVec[i].Getcollision().CheckCollision(player.Getcollision()) && player.checkPunch() && (player.faceRight == enemyVec[i].faceLeft))
		{
			if (!enemyVec[i].checkDead())
			{
				enemyVec[i].getPunch(true);
				playerScore += 100;
			}
		}
	}

	//if ((countTime/1000)%10==0)
	//{
	//	normalEnemy.setSpeed(50 + rand() % 100);
	//	normalEnemy.setPosition((player.getX() - 300) + (rand() % 600));
	//	enemyVec.push_back(normalEnemy);
	//}


	if (Keyboard::isKeyPressed(Keyboard::G))
	{
		totalTimeButton += deltaTime;
		if (totalTimeButton >= 0.15)
		{
			totalTimeButton -= 0.15;
			normalEnemy.setSpeed(50 + rand() % 100);
			normalEnemy.setPosition((player.getX() - 300) + (rand() % 600));
			enemyVec.push_back(normalEnemy);
		}
	}
	else
		totalTimeButton = 0;

	player.Update(deltaTime, getHit, shoot);
	window->draw(player.body);
}

////////////////////Normal Enemy
void Display::enemyAttack()
{
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (enemyVec[i].Getcollision().CheckCollision(player.Getcollision()) && !enemyVec[i].checkDead())
		{
			if (enemyVec[i].curX() == 2)
			{
				damaged = rand() % 300;

				if (damaged == 10)
				{
				    if (myHP > 0) myHP -= 2000;
					if (myHP <= 0) myHP = 0;
				}
			}
		}
	}
	
}

////////////////////Big Enemy
void Display::bermAI()
{
	if (berm.Getcollision().CheckCollision(player.Getcollision()) && !berm.checkDead())
	{
		if (berm.curX() == 2)
		{
			damaged = rand() % 100;

			if (damaged == 10 )
			{
				getHit = true;
				myHP -= 5000;
				//std::cout << damaged << endl;
				if (myHP <= 0) myHP = 0;
			}
			else getHit = false;
		}
	}

	berm.Update(player.getPosition(), deltaTime);
	window->draw(berm.draw());
}

///////////////////////////Batarang
void Display::batarangShoot()
{
	Vector2f flySpeed(1.2f, 0.0f);
	if (!shoot && player.cShoot && batNumber != 0)
	{
		if (player.faceRight)
			d = 110.0f;
		else
			d = 0;
		batarang.setPosition(Vector2f(player.getX() + d, player.getY() + 25.0f));
		shoot = true;
		player.cShoot = false;
	}

	if (shoot)
	{
		batarang.Update();
		window->draw(batarang.body);
		if (!isFire)
		{
			if (player.faceRight)
				movement = flySpeed;
			if (!player.faceRight)
				movement = -flySpeed;
			isFire = true;
			if(batNumber > 0)
				batNumber--;
		}
		batarang.body.move(movement);
	}
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (isFire && ((enemyVec[i].Getcollision().CheckCollision(batarang.Getcollision()) && !enemyVec[i].checkDead()) || batarang.getX() >= camera.getCenter().x + 640 || batarang.getX() <= camera.getCenter().x - 670))
		{
			if (enemyVec[i].Getcollision().CheckCollision(batarang.Getcollision()) && !enemyVec[i].checkDead())
			{
				enemyVec[i].getShot(true);
				playerScore += 200;
			}
			shoot = false;
			isFire = false;
		}
	}
	
}

void Display::playerDead()
{
	player.Update(deltaTime, false, false);
	window->draw(player.body);
}

void Display::playMoreStory()
{
	batarangShoot();
	player.Update(deltaTime, getHit, shoot);
	window->draw(player.body);
}

void Display::vectorSet()
{
	for (int i = 0; i < n; i++)
	{
		normalEnemy.setSpeed(50 + rand() % 100);
		normalEnemy.setPosition((player.getX()-300) + (rand() % 600));
		enemyVec.push_back(normalEnemy);
	}
}

void Display::vectorUpdate()
{
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (!enemyVec[i].checkDead())
		{
			enemyVec[i].Update(player.getPosition(), deltaTime);
			window->draw(enemyVec[i].draw());
		}
	}
}

bool Display::posCheck()
{
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (!enemyVec[i].checkDead() && abs(enemyVec[i].getX() - player.getX()) <= 200)
		{
			return false;
		}
		else
			return true;
	}
	
}

void Display::statusBar()
{
	//Bar
	bar.setPosition(Vector2f(camera.getCenter().x - 640.0f, camera.getCenter().y - 360.0f));
	window->draw(bar);

	Text hpNumber, times, textScore, textBat;
	//Time
	string dt = to_string(countTime);
	times.setFont(font);
	times.setString(dt);
	times.setCharacterSize(40);
	times.setFillColor(sf::Color::Red);
	times.setPosition(Vector2f(camera.getCenter().x + 250.0f, camera.getCenter().y - 310.0f));
	window->draw(times);

	//HP
	HP.setPosition(Vector2f(camera.getCenter().x - 583.0f, camera.getCenter().y - 310.0f));
	HP.setSize(Vector2f(myHP / 362, 55));
	window->draw(HP);
	std::string sTest = to_string(myHP);
	hpNumber.setFont(font);
	hpNumber.setString("HP:" + sTest);
	hpNumber.setCharacterSize(40);
	hpNumber.setFillColor(sf::Color::Green);
	hpNumber.setOutlineColor(sf::Color::Black);
	hpNumber.setPosition(Vector2f(camera.getCenter().x - 570.0f, camera.getCenter().y - 315.0f));
	window->draw(hpNumber);

	//score
	string score = to_string(playerScore);
	textScore.setFont(font);
	textScore.setString(score);
	textScore.setCharacterSize(50);
	textScore.setFillColor(sf::Color::Yellow);
	textScore.setOutlineColor(sf::Color::Black);
	textScore.setPosition(Vector2f(camera.getCenter().x - 238.0f, camera.getCenter().y - 330.0f));
	window->draw(textScore);

	string bn = to_string(batNumber);
	textBat.setFont(font);
	textBat.setString(bn);
	textBat.setCharacterSize(40);
	textBat.setFillColor(sf::Color::White);
	textBat.setPosition(Vector2f(camera.getCenter().x + 480.0f, camera.getCenter().y - 310.0f));
	window->draw(textBat);
}




