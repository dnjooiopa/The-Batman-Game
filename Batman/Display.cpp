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
	bombCheck = false;

	//enemy
	for(int i=0;i<4;i++)
		normalEnemyGetHit[i]= false;
	normalEnemyGetBomb = false;
	bigEnemyGetHit = false;
	bigEnemyGetBomb = false;
	

	//HP
	myHP = 100000;
	playerScore = 1000000;
	HP.setFillColor(Color::Red);//เซตสี
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
	int cnt = 0;  //ประกาศตัวนับ
	window->clear();
	for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i)
	{
		++cnt;
		if (cnt > 5) break;                       //เมื่อตัวนับเกิน 5 ให้จบการทำงาน
		Text a, b, highScore,textBack;                     //ประกาศ Text
		a.setString(to_string(i->first));         //เนื่องจากค่าคะแนนเป็น integer จึงต้องทำการแปลงเป็น string ก่อนนำมาแสดงผล (first คือpair ตัวที่หนึ่ง =>int)
		a.setFont(font);                          //การตั้งค่า Font คะแนน
		a.setCharacterSize(40);                   //ตั้งค่าขนาด Font คะแนน
		a.setFillColor(Color::White);
		a.setPosition(720, 80 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของคะแนน และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
		window->draw(a);                           //แสดงผลคะแนน
		b.setString(i->second);					 // (second คือpair ตัวที่สอง =>string) 
		b.setFont(font);                        //การตั้งค่า Font ชื่อผู้เล่น
		b.setCharacterSize(40);                   //ตั้งค่าขนาด Font ชื่อผู้เล่น
		b.setFillColor(Color::White);
		b.setPosition(320, 80 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของชื่อผู้เล่น และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
		window->draw(b);                           //แสดงผลชื่อผู้เล่น
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
		//enemyAI();
		//bermAI();
		
	}vectorUpdate();
	//batarangShoot();
	playerControl();
	
	///////Bomb effect
	bomb.Update(deltaTime);
	if (bombCheck)
	{
		window->draw(bomb.Draw());
		if (bomb.curX() >= 5)
		{
			bombCheck = false;
		}
	}
}

void Display::playerControl()
{
	for (int i = 0; i < 4; i++)
	{
		if (enemyVec[i].Getcollision().CheckCollision(player.Getcollision()) && player.checkPunch())
			normalEnemyGetHit[i] = true;
		else
			normalEnemyGetHit[i] = false;
	}

	//if (berm.Getcollision().CheckCollision(player.Getcollision()) && player.checkPunch())
	//	bigEnemyGetHit = true;
	//else
	//	bigEnemyGetHit = false;

	player.Update(deltaTime, getHit, shoot);
	window->draw(player.body);
}

////////////////////Normal Enemy
void Display::enemyAI()
{
	if (normalEnemy.Getcollision().CheckCollision(player.Getcollision()) && !normalEnemy.checkDead())
	{
		if (normalEnemy.curX() == 2)
		{
			damaged = rand() % 100;
			
			if (damaged == 10)
			{
				//getHit = true;
				myHP -= 3000;
				if (myHP <= 0) myHP = 0;
			}
			else getHit = false;
		}
	}
	
	normalEnemy.Update(player.getPosition(), normalEnemyGetHit,deltaTime);
	window->draw(normalEnemy.draw());
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

	berm.Update(player.getPosition(), bigEnemyGetHit, deltaTime);
	window->draw(berm.draw());
}

///////////////////////////Batarang
void Display::batarangShoot()
{
	Vector2f flySpeed(1.2f, 0.0f);
	if (player.curX() == 3 && !shoot && player.checkShoot())
	{
		if (player.faceRight)
			d = 110.0f;
		else
			d = 0;
		batarang.setPosition(Vector2f(player.getX() + d, player.getY() + 25.0f));
		shoot = true;
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
		}
	}
	if (isFire && ((normalEnemy.Getcollision().CheckCollision(batarang.Getcollision())&&!normalEnemy.checkDead()) || (berm.Getcollision().CheckCollision(batarang.Getcollision())&&!berm.checkDead()) || batarang.getX() >= camera.getCenter().x + 550 || batarang.getX() <= camera.getCenter().x - 670) )
	{
		if (normalEnemy.Getcollision().CheckCollision(batarang.Getcollision()) && !normalEnemy.checkDead()) normalEnemy.getBomb(true);
		if (berm.Getcollision().CheckCollision(batarang.Getcollision()) && !berm.checkDead()) berm.getBomb(true);
		bomb.setBomb(true);
		bomb.setPosition(Vector2f(batarang.getX(),batarang.getY()-50.0f));
		bombCheck = true;
		shoot = false;
		isFire = false;
	}
	else
	{
		bomb.setBomb(false);
	}
	batarang.body.move(movement);
}

void Display::statusBar()
{
	//Bar
	bar.setPosition(Vector2f(camera.getCenter().x-640.0f, camera.getCenter().y - 360.0f));
	window->draw(bar);

	Text test,times,textScore;
	//Time
	/*time_t now = time(0);
	char* dt = ctime(&now);
	times.setFont(font);
	times.setString(dt);
	times.setCharacterSize(30);
	times.setFillColor(sf::Color::Magenta);
	times.setOutlineColor(sf::Color::White);
	times.setPosition(Vector2f(camera.getCenter().x + 100.0f, camera.getCenter().y - 350.0f));
	window->draw(times);*/

	//HP
	HP.setPosition(Vector2f(camera.getCenter().x - 583.0f, camera.getCenter().y - 310.0f));
	HP.setSize(Vector2f(myHP / 362, 55));
	window->draw(HP);
	std::string sTest = to_string(myHP);
	test.setFont(font);
	test.setString("HP:"+sTest);
	test.setCharacterSize(40);
	test.setFillColor(sf::Color::Green);
	test.setOutlineColor(sf::Color::Black);
	test.setPosition(Vector2f(camera.getCenter().x - 570.0f, camera.getCenter().y -315.0f));
	window->draw(test);	

	//score
	std::string score = to_string(playerScore);
	textScore.setFont(font);
	textScore.setString(score);
	textScore.setCharacterSize(50);
	textScore.setFillColor(sf::Color::Yellow);
	textScore.setOutlineColor(sf::Color::Black);
	textScore.setPosition(Vector2f(camera.getCenter().x - 238.0f, camera.getCenter().y - 330.0f));
	window->draw(textScore);
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
	for (int i = 0; i < 4; i++)
	{
		normalEnemy.setSpeed(50 + rand() % 100);
		normalEnemy.setPosition(player.getX() + (100 + rand() % 100));
		enemyVec.push_back(normalEnemy);
	}
	
}

void Display::vectorUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		enemyVec[i].Update(player.getPosition(), normalEnemyGetHit[i], deltaTime);
		window->draw(enemyVec[i].draw());
	}
}




