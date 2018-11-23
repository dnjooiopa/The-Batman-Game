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

	//Item
	itemTexture.loadFromFile("sprite/batItem.png");
	item.setItem(&itemTexture, 2800);
	//trap
	trapTexture.loadFromFile("sprite/trap2.png");
	trap.setItem(&trapTexture, 1200);
	//mana
	redbullTexture.loadFromFile("sprite/redbull.png");
	redbull.setItem(&redbullTexture, 1200);

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
	batNumber = 0;
	i = true;
	k = true;
	j = true;
	a = true;
	n = 10;
	//HP
	myHP = 100000;
	playerScore = 0;
	HP.setFillColor(Color::Red);
	hit = 4;
	//mana
	MANA.setFillColor(Color::Blue);

	//HighScore
	loadFile.open("score.txt");
	while (!loadFile.eof()) {
		string tempName;
		int tempScore;
		loadFile >> tempName >> tempScore;
		scoreboard.push_back({ tempScore,tempName });
	}
	sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());
	loadFile.close();

	//Sound
	batFlying.openFromFile("sound/batFlying.ogg");
	batFlying.setVolume(50);
	itemCollect.openFromFile("sound/pickup.ogg");
	itemCollect.setVolume(60);
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

void Display::setScore(std::string name)
{

	fstream myFile;
	myFile.open("score.txt", ios::out | ios::app);
	myFile << "\n" << name << " " << playerScore;
	myFile.close(); 
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
void Display::moreStory()
{
	window->clear();
	window->draw(scene2);
	playMoreStory();
	statusBar();
	window->display();
}
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
	textName.setString("KITTISAK PHORMRAKSA  61010092");
	textName.setCharacterSize(20);
	textName.setFillColor(sf::Color::White);
	textName.setPosition(800, 20);

	
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
			textBack.setStyle(sf::Text::Bold);
		}
		else
		{
			textBack.setStyle(Text::Regular);
		}
		mCheck = mouseCheck(&textBack);
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
	//fire.setPosition(Vector2f(player.getX()-100, player.getY() - 100));
	//fire.Update(deltaTime);//fire
	//window->draw(fire.body);//fire
	window->display();
}

///////////////////Main Story////////////////////////////////////////
void Display::mainStory()
{	
	if (countTime % n == 0 && i)
	{
		int R = rand() % 3;
		if (R == 0)
		{
			int r = rand() % 2;
			if (r == 0)
				berm.setPosition(player.getX() + 800);
			else
				berm.setPosition(player.getX() - 800);
			berm.setSpeed(70 + rand() % 100);
			enemyVec2.push_back(berm);
		}
		else
		{
			int r = rand() % 2;
			if (r == 0)
				normalEnemy.setPosition(player.getX() + 800);
			else
				normalEnemy.setPosition(player.getX() - 800);
			normalEnemy.setSpeed(70 + rand() % 100);
			enemyVec1.push_back(normalEnemy);
		}
		i = false;
	}
	else if (countTime % n != 0)
	{
		i = true;
	}

	if (countTime >= 30) n = 5;
	if (countTime >= 60) n = 3;
	vectorUpdate1();
	enemyAttack1();

	vectorUpdate2();
	enemyAttack2();
	
	batarangShoot();
	playerControl();
	specialItem();
	//Trap();
}

void Display::playerControl()
{
	for (int i = 0; i < enemyVec1.size(); i++)
	{
		if (enemyVec1[i].Getcollision().CheckCollision(player.Getcollision()) && player.checkPunch() && (player.faceRight == enemyVec1[i].faceLeft))
		{
			if (!enemyVec1[i].checkDead())
			{
				enemyVec1[i].getPunch(true);
				playerScore += 100;
			}
		}
	}

	for (int i = 0; i < enemyVec2.size(); i++)
	{
		if (enemyVec2[i].Getcollision().CheckCollision(player.Getcollision()) && player.checkPunch() && (player.faceRight == enemyVec2[i].faceLeft))
		{
			if (!enemyVec2[i].checkDead())
			{
				enemyVec2[i].getPunch(true);
				playerScore += 100;
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Y))
	{
		trap.setPosition(Vector2f(player.getX() + 300, 0));
	}

	player.Update(deltaTime, getHit, shoot);
	window->draw(player.body);

}

////////////////////Normal Enemy
void Display::enemyAttack1()
{
	for (int i = 0; i < enemyVec1.size(); i++)
	{
		if (enemyVec1[i].Getcollision().CheckCollision(player.Getcollision()) && !enemyVec1[i].checkDead())
		{
			if (enemyVec1[i].curX() == 2)
			{
				damaged = rand() % 200;

				if (damaged == 10)
				{
				    if (myHP > 0) myHP -= 3000;
					if (myHP <= 0) myHP = 0;
				}
			}
		}
	}
	
}

////////////////////Big Enemy
void Display::enemyAttack2()
{
	for (int i = 0; i < enemyVec2.size(); i++)
	{
		if (enemyVec2[i].Getcollision().CheckCollision(player.Getcollision()) && !enemyVec2[i].checkDead())
		{
			if (enemyVec2[i].curX() == 2)
			{
				damaged = rand() % 200;

				if (damaged == 10)
				{
					if (myHP > 0) myHP -= 5000;
					if (myHP <= 0) myHP = 0;
				}
			}
		}
	}
}

///////////////////////////Batarang
void Display::batarangShoot()
{
	Vector2f flySpeed(1.5f, 0.0f);
	if (!shoot && player.cShoot && batNumber != 0)
	{
		if (player.faceRight)
			d = 110.0f;
		else
			d = 0;
		batarang.setPosition(Vector2f(player.getX() + d, player.getY() + 25.0f));
		shoot = true;
		player.cShoot = false;
		batFlying.setPlayingOffset(Time(seconds(0)));
		batFlying.play();
	}
	if (batNumber == 0)
		player.cShoot = false;
	
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
	for (int i = 0; i < enemyVec1.size(); i++)
	{
		if (isFire && ((enemyVec1[i].Getcollision().CheckCollision(batarang.Getcollision()) && !enemyVec1[i].checkDead()) || batarang.getX() >= camera.getCenter().x + 640 || batarang.getX() <= camera.getCenter().x - 670 ))
		{
			if (enemyVec1[i].Getcollision().CheckCollision(batarang.Getcollision()) && !enemyVec1[i].checkDead())
			{
				enemyVec1[i].getShot(true);
				playerScore += 200;
			}
			shoot = false;
			isFire = false;
		}
	}
	for (int i = 0; i < enemyVec2.size(); i++)
	{
		if (isFire && ((enemyVec2[i].Getcollision().CheckCollision(batarang.Getcollision()) && !enemyVec2[i].checkDead()) || batarang.getX() >= camera.getCenter().x + 640 || batarang.getX() <= camera.getCenter().x - 670 ))
		{
			if (enemyVec2[i].Getcollision().CheckCollision(batarang.Getcollision()) && !enemyVec2[i].checkDead())
			{
				enemyVec2[i].getShot(true);
				playerScore += 200;
			}
			shoot = false;
			isFire = false;
		}
	}
	
}

void Display::playMoreStory()
{
	batarangShoot();
	player.Update(deltaTime, getHit, shoot);
	window->draw(player.body);
}

void Display::vectorUpdate1()
{
	for (int i = 0; i < enemyVec1.size(); i++)
	{
		if (!enemyVec1[i].checkDead())
		{
			enemyVec1[i].Update(player.getPosition(), deltaTime);
			window->draw(enemyVec1[i].body);
		}
		else
		{
			enemyVec1.erase(enemyVec1.begin() + i);
		}
	}
}

void Display::vectorUpdate2()
{
	for (int i = 0; i < enemyVec2.size(); i++)
	{
		if (!enemyVec2[i].checkDead())
		{
			enemyVec2[i].Update(player.getPosition(), deltaTime);
			window->draw(enemyVec2[i].body);
		}
		else
		{
			enemyVec2.erase(enemyVec2.begin() + i);
		}
	}
}

void Display::specialItem()
{
	// batarang
	if (countTime % 20 == 0 && a && itemVec.size() < 3)
	{
		itemVec.push_back(item);
		int i = rand() % 2;
		if (i == 0)
			item.setPosition(Vector2f(player.getX() + 1000, 0));
		else
			item.setPosition(Vector2f(player.getX() - 1000, 0));
		a = false;
	}
	else if (countTime % 10 != 0)
	{
		a = true;
	}
	for (int i = 0; i < itemVec.size(); i++)
	{
		if (itemVec[i].Getcollision().CheckCollision(player.Getcollision()))
		{
			itemCollect.setPlayingOffset(Time(seconds(0)));
			itemCollect.play();
			batNumber += 10;
			itemVec.erase(itemVec.begin() + i);
		}
	}

	for (int i = 0; i < itemVec.size(); i++)
	{
		itemVec[i].Update(deltaTime);
		window->draw(itemVec[i].body);
	}

	//mana potion
	if (countTime % 10 == 0 && j && redbullVec.size()<3)
	{
		redbullVec.push_back(redbull);
		redbullVec.back().setPosition(Vector2f(player.getX() - 1000 + (rand() % 2000), 0));
		j = false;
	}
	else if (countTime % 10 != 0)
	{
		j = true;
	}
	for (int i = 0; i < redbullVec.size(); i++)
	{
		if (redbullVec[i].Getcollision().CheckCollision(player.Getcollision()))
		{
			player.mana += 30000;
			redbullVec.erase(redbullVec.begin() + i);
		}
	}

	for (int i = 0; i < redbullVec.size(); i++)
	{
		redbullVec[i].Update(deltaTime);
		window->draw(redbullVec[i].body);
	}
}

void Display::Trap()
{	
	if (countTime % 5 == 0 && k)
	{
		trapVec.push_back(trap);
		trapVec.back().setPosition(Vector2f(player.getX() - 400 + (rand() % 800), 0));
		k = false;
	}
	else if (countTime % 5 != 0)
	{
		k = true;
	}
	for (int i = 0; i < trapVec.size(); i++)
	{
		if (trapVec[i].Getcollision().CheckCollision(player.Getcollision()))
		{
			bomb.setPosition(Vector2f(trapVec[i].getX(), trapVec[i].getY() - 25));
			bomb.setBomb(true);
			trapVec.erase(trapVec.begin() + i);
			if (myHP > 0) myHP -= 10000;
			if (myHP <= 0) myHP = 0;
		}
	}
	bomb.Update(deltaTime);
	if (bomb.showBomb())
	{
		window->draw(bomb.body);
	}

	for (int i = 0; i < trapVec.size(); i++)
	{
		trapVec[i].Update(deltaTime);
		window->draw(trapVec[i].body);
	}

}

bool Display::posCheck()
{
	for (int i = 0; i < enemyVec1.size(); i++)
	{
		if (!enemyVec1[i].checkDead() && abs(enemyVec1[i].getX() - player.getX()) <= 200)
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
	HP.setSize(Vector2f(myHP / 362, 25));
	window->draw(HP);
	std::string sTest = to_string(myHP);
	hpNumber.setFont(font);
	hpNumber.setString("HP:" + sTest);
	hpNumber.setCharacterSize(40);
	hpNumber.setFillColor(sf::Color::Green);
	hpNumber.setOutlineColor(sf::Color::Black);
	hpNumber.setPosition(Vector2f(camera.getCenter().x - 570.0f, camera.getCenter().y - 315.0f));
	//window->draw(hpNumber);

	//Mana
	MANA.setPosition(Vector2f(camera.getCenter().x - 583.0f, camera.getCenter().y - 280.0f));
	MANA.setSize(Vector2f(player.getMana() / 362, 25));
	window->draw(MANA);

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




