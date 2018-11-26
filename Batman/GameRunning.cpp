#include "GameRunning.h"


GameRunning::GameRunning(Vector2u size, std::string name)
{
	window.create(VideoMode(size.x, size.y), name, sf::Style::Close | sf::Style::Titlebar);
	viewCheck = false;
	state = 1;
	exit = 0;
	runMenu = 1;
	gameStart = 2;
	showHighscore = 3;
	playerDead = 4;

	//MainMenu
	mainMenuTexture.loadFromFile("sprite/background.png");
	mainMenuSprite.setTexture(mainMenuTexture);
	logoTexture.loadFromFile("sprite/logo.png");
	logo.setTexture(logoTexture);
	logo.setScale(0.35f, 0.35f);

	//Scene1
	scene1Texture.loadFromFile("sprite/scene1.png");
	scene1.setTexture(scene1Texture);
	scene1.setScale(Vector2f(1, 1));

	//Bar
	barTexture.loadFromFile("sprite/barTest.png");
	bar.setTexture(barTexture);

	//Player
	playerTexture.loadFromFile("sprite/batman2.png");
	player.setPlayer(&playerTexture, Vector2u(6, 11), 0.08f, 300);

	//normalEnemy
	normalEnemyTexture.loadFromFile("sprite/nV.png");
	normalEnemy.setEnemy(&normalEnemyTexture, Vector2u(4, 4), 0.08f, 150, 500);

	//bigEnemy
	bigEnemyTexture.loadFromFile("sprite/bigEnemy.png");
	bigEnemy.setEnemy(&bigEnemyTexture, Vector2u(6, 4), 0.08f, 120, 1500);

	//Batarang
	batarangTexture.loadFromFile("sprite/batarang.png");
	batarang.setBatarang(&batarangTexture, Vector2u(4, 1), 0.08f);

	//Bomb
	bombTexture.loadFromFile("sprite/bomb.png");
	bomb.setBombEffect(&bombTexture, Vector2u(6, 1), 0.12f);

	//Item
	itemTexture.loadFromFile("sprite/batItem.png");
	item.setItem(&itemTexture, 2800);
	//trap
	trapTexture.loadFromFile("sprite/trap2.png");
	trap.setItem(&trapTexture, 300);
	//mana
	redbullTexture.loadFromFile("sprite/redbull.png");
	redbull.setItem(&redbullTexture, 1500);
	//hp
	hpBotTexture.loadFromFile("sprite/hp.png");
	hpBot.setItem(&hpBotTexture, 1200);

	//font
	font.loadFromFile("font/batmfa.ttf");\
	font2.loadFromFile("font/mer.ttf");
	defaultSetting();

	loadFile.open("score.txt");
	while (!loadFile.eof()) {
		std::string tempName;
		int tempScore;
		loadFile >> tempName >> tempScore;
		scoreboard.push_back({ tempScore,tempName });
	}
	sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, std::string>>());
	loadFile.close();
	//Sound
	batFlying.openFromFile("sound/batFlying.ogg");
	batFlying.setVolume(50);
	itemCollect.openFromFile("sound/pickup.ogg");
	itemCollect.setVolume(60);
	bottleCollect.openFromFile("sound/bottle.wav");
	bottleCollect.setVolume(50);

	endTexture.loadFromFile("sprite/end.png");
	endBackground.setTexture(endTexture);
	bgSound.openFromFile("sound/bgSound.ogg");

	bgSound.setVolume(80);
	bgSound.setPlayingOffset(Time(seconds(0)));
	bgSound.play();

	GameControl();
}

GameRunning::~GameRunning()
{
}

void GameRunning::defaultSetting()
{
	//Player
	myHP = 10000;
	playerScore = 0;
	player.mana = 100000;
	player.setPlayer(&playerTexture, Vector2u(6, 11), 0.08f, 300);
	HP.setFillColor(Color::Red);
	MANA.setFillColor(Color::Blue);
	batNumber = 0;

	//clearVector
	enemyVec.clear();
    itemVec.clear();
    trapVec.clear();
	potionVec.clear();

	//time 
	time = 0;
	countTime = 0;
	n = 10;
	nTrap = 8;
	eSpeed = 80;
	msCheck = false;
	viewCheck = false;
	shoot = false;
	isFire = false;
	select = 1;
	totalTimeButton = 0;
	delayButton = 0.07;
	mCheck = false;
	msCheck = false;
	batNumber = 0;
	l = true;
	k = true;
	j = true;
	a = true;
	posibleHit = 4;
}

void GameRunning::GameControl()
{
	deltaTime = 0.0;
	sf::String yourname;
	Text playerText, enterYourName;
	
	while (state != exit)
	{
		deltaTime = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (state == playerDead)
			{
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode == '\b' && yourname.getSize()) {//ถ้ากด Backspace เป็นการลบตัวอักษร
						yourname.erase(yourname.getSize() - 1, 1);
						playerText.setFont(font2);
						playerText.setString(yourname);
					}
					else {
						std::string name;
						yourname += static_cast<char>(event.text.unicode);
						name += static_cast<char>(event.text.unicode);
						if ((event.text.unicode < 128) && (yourname.getSize() < 10)) {
							playerText.setFont(font2);
							playerText.setString(yourname);
						}
					}
					playerText.setCharacterSize(60);   //เซ็ตขนาดของข้อความ
					playerText.setPosition(415, 410);  //เซ็ตขนาดของข้อความ
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Return) {
						playerText.setString(yourname);
						setScore(yourname); 
						defaultSetting();
						state = showHighscore;
						bgSound.setPlayingOffset(Time(seconds(0)));
						bgSound.play();
						break;
					}
				}
			}

			if (event.type == Event::Closed)
			{
				window.close();
				state = exit;
			}
		}
		if (state == runMenu)
		{
			window.setMouseCursorVisible(true);
			if ((Keyboard::isKeyPressed(Keyboard::Return) || (Mouse::isButtonPressed(Mouse::Left) && msCheck)))
			{
				switch (select)
				{
				case 1:
					viewCheck = true;
					state = gameStart;
					break;
				case 2:
					viewCheck = false;
					state = showHighscore;
					break;
				case 3:
					window.close();
					state = exit;
					break;
				}
			}
			drawMainMenu();
		}
		if (state == gameStart)
		{
			window.setMouseCursorVisible(false);
			time += deltaTime;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				viewCheck = false;
				state = runMenu;
			}
			if (player.checkDead())
			{
				window.setMouseCursorVisible(true);
				state = playerDead;
				viewCheck = false;
				bgSound.setVolume(40);
			}
			timeElapse(time);
			Playing();
		}
		if (state == showHighscore)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape)|| (Mouse::isButtonPressed(Mouse::Left) && mCheck))
			{
				viewCheck = false;
				state = runMenu;
			}
			drawHighscore();
		}
		if (state == playerDead)
		{
			window.clear();
			window.draw(endBackground);
			window.draw(playerText);
			window.display();
		}
		if (viewCheck)
		{
			if(player.getX() < 640)
				camera.setCenter(Vector2f(720, scene1Texture.getSize().y / 2));
			else if(player.getX() > 8888)
				camera.setCenter(Vector2f(8969, scene1Texture.getSize().y / 2));
			else
				camera.setCenter(Vector2f(player.getX() + 80, scene1Texture.getSize().y / 2));
			camera.setSize(Vector2f(1280, scene1Texture.getSize().y));
		}
		else
		{
			camera.setCenter(Vector2f(mainMenuTexture.getSize().x / 2, mainMenuTexture.getSize().y / 2));
			camera.setSize(Vector2f(mainMenuTexture.getSize()));
		}
		window.setView(camera);
	}
}

void GameRunning::timeElapse(float timeElapse)
{
	this->countTime = int(timeElapse);
}
void GameRunning::drawMainMenu()
{
	Text textPlaygame, textExit, textScore, textName;
	textPlaygame.setFont(font);//Play Game
	if(time == 0)
		textPlaygame.setString("PLAY GAME");
	else
		textPlaygame.setString("RESUME");
	textPlaygame.setCharacterSize(40);
	textPlaygame.setFillColor(sf::Color(166, 166, 166));
	textPlaygame.setPosition(900, 200);
	textScore.setFont(font);//Score
	textScore.setString("Score");
	textScore.setCharacterSize(40);
	textScore.setFillColor(sf::Color(166, 166, 166));
	textScore.setPosition(895, 300);
	textExit.setFont(font);//Exit
	textExit.setString("Exit");
	textExit.setCharacterSize(40);
	textExit.setFillColor(sf::Color(166, 166, 166));
	textExit.setPosition(895, 400);
	textName.setFont(font);//Name
	textName.setString("KITTISAK PHORMRAKSA  61010092");
	textName.setCharacterSize(20);
	textName.setFillColor(sf::Color::White);
	textName.setPosition(800, 20);

	if (select == 1 || mouseCheck(&textPlaygame))
	{
		select = 1;
		textPlaygame.setFillColor(sf::Color::White);
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
		textScore.setFillColor(sf::Color::White);
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
		textExit.setFillColor(sf::Color::White);
		textExit.setStyle(sf::Text::Bold);
		logo.setPosition(770, 400);
		msCheck = mouseCheck(&textExit);
	}
	else
	{
		textExit.setStyle(Text::Regular);
	}
	buttonCheck();
	window.clear();
    window.draw(mainMenuSprite);
	window.draw(logo);
	window.draw(textPlaygame);
	window.draw(textScore);
	window.draw(textExit);
	window.draw(textName);
	window.display();
}
void GameRunning::buttonCheck()
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
bool GameRunning::mouseCheck(Text *text)
{
	Vector2f mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (text->getGlobalBounds().contains(mousePos))
		return true;
	else
		return false;
}
void GameRunning::setScore(std::string name)
{
	myFile.open("score.txt", ios::out | ios::app);
	myFile << "\n" << name << " " << playerScore;
	myFile.close();
	scoreboard.push_back({ playerScore,name });
	sort(scoreboard.begin(), scoreboard.end(), greater < pair<int, std::string >> ());
}
void GameRunning::drawHighscore()
{
	int cnt = 0;  //ประกาศตัวนับ
	window.clear();
	for (vector<pair<int, std::string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i)
	{
		++cnt;
		if (cnt > 5) break;                       //เมื่อตัวนับเกิน 5 ให้จบการทำงาน
		Text a, b, highScore, textBack;                     //ประกาศ Text
		a.setString(to_string(i->first));         //เนื่องจากค่าคะแนนเป็น integer จึงต้องทำการแปลงเป็น string ก่อนนำมาแสดงผล (first คือpair ตัวที่หนึ่ง =>int)
		a.setFont(font2);                          //การตั้งค่า Font คะแนน
		a.setCharacterSize(40);                   //ตั้งค่าขนาด Font คะแนน
		a.setFillColor(Color::White);
		a.setPosition(720, 80 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของคะแนน และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
		window.draw(a);                           //แสดงผลคะแนน
		b.setString(i->second);					 // (second คือpair ตัวที่สอง =>string) 
		b.setFont(font2);                        //การตั้งค่า Font ชื่อผู้เล่น
		b.setCharacterSize(40);                   //ตั้งค่าขนาด Font ชื่อผู้เล่น
		b.setStyle(Text::Bold);
		b.setFillColor(Color::White);
		b.setPosition(320, 80 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของชื่อผู้เล่น และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
		window.draw(b);                           //แสดงผลชื่อผู้เล่น
		highScore.setFont(font2);
		highScore.setString("HIGH SCORE");
		highScore.setCharacterSize(50);
		highScore.setFillColor(sf::Color::White);
		highScore.setPosition(455, 30);
		window.draw(highScore);
		textBack.setFont(font);
		textBack.setString("BACK");
		textBack.setCharacterSize(35);
		textBack.setFillColor(sf::Color(166,166,166));
		textBack.setPosition(40, 25);
		if (mouseCheck(&textBack))
		{
			textBack.setFillColor(sf::Color::White);
			textBack.setStyle(Text::Bold);
		}
		else
		{
			textBack.setStyle(Text::Regular);
		}
		mCheck = mouseCheck(&textBack);
		window.draw(textBack);
	}
	window.display();
}

/////////////////////////////////GameRunning////////////////////////////////////
void GameRunning::Playing()
{
	window.clear();
	window.draw(scene1);
	mainStory();
	statusBar();
	window.display();
}

///////////////////Main Story////////////////////////////////////////
void GameRunning::mainStory()
{
	if (countTime % n == 0 && l)
	{
		int R = rand() % 2;
		if (R == 0)
			bigEnemy.setPosition(player.getX() + 800);
		else
			bigEnemy.setPosition(player.getX() - 800);
		bigEnemy.setSpeed(eSpeed + rand() % 100);

		int r = rand() % 2;
		if (r == 0)
			normalEnemy.setPosition(player.getX() + 800);
		else
			normalEnemy.setPosition(player.getX() - 800);
		normalEnemy.setSpeed(eSpeed + rand() % 100);

		int q = rand() % 3;
		if(q==1)
			enemyVec.push_back(bigEnemy);
		else
			enemyVec.push_back(normalEnemy);

		l = false;
	}
	else if (countTime % n != 0)
	{
		l = true;
	}

	if (countTime >= 30)
	{
		n = 5;
		nTrap = 6;
		eSpeed = 90;
	}
	if (countTime >= 60)
	{
		n = 3;
		nTrap = 4;
		eSpeed = 120;
	}
	enemyVectorUpdate();
	enemyAttack();
	batarangShoot();
	playerControl();
	if (countTime >= 10)
	{
		specialItem();
		Trap();
	}
}

void GameRunning::playerControl()
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

	player.Update(deltaTime, myHP, shoot);
	window.draw(player.body);

}

////////////////////Normal Enemy
void GameRunning::enemyAttack()
{
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (enemyVec[i].Getcollision().CheckCollision(player.Getcollision()) && !enemyVec[i].checkDead())
		{
			if (enemyVec[i].curX() == 2)
			{
				damaged = rand() % 100;

				if (damaged == 10)
				{
					if(enemyVec[i].getSpeed()==normalEnemy.getSpeed())
						myHP -= 300;
					if (enemyVec[i].getSpeed() == bigEnemy.getSpeed())
						myHP -= 700;
					if (myHP <= 0) myHP = 0;
				}
			}
		}
	}
}

///////////////////////////Batarang
void GameRunning::batarangShoot()
{
	Vector2f flySpeed(window.getSize().x*1.5/1280, 0);
	if (!shoot && player.cShoot && batNumber != 0)
	{
		if (player.faceRight)
			d = 110;
		else
			d = 0;
		batarang.setPosition(Vector2f(player.getX() + d, player.getY() + 25));
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
		window.draw(batarang.body);
		if (!isFire)
		{
			if (player.faceRight)
				movement = flySpeed;
			if (!player.faceRight)
				movement = -flySpeed;
			isFire = true;
			if (batNumber > 0)
				batNumber--;
		}
		batarang.body.move(movement);
	}
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (isFire && ((enemyVec[i].Getcollision().CheckCollision(batarang.Getcollision()) && enemyVec[i].getHP() > 0) || batarang.getX() >= camera.getCenter().x + 640 || batarang.getX() <= camera.getCenter().x - 640))
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

void GameRunning::enemyVectorUpdate()
{
	for (int i = 0; i < enemyVec.size(); i++)
	{
		if (!enemyVec[i].checkDead())
		{
			enemyVec[i].Update(player.getPosition(), deltaTime);
			window.draw(enemyVec[i].HP);
			window.draw(enemyVec[i].body);
		}
		else
		{
			enemyVec.erase(enemyVec.begin() + i);
		}
	}
}

void GameRunning::specialItem()
{
	// batarang
	if (countTime % 14 == 0 && a && itemVec.size() < 3)
	{
		itemVec.push_back(item);
		int i = rand() % 2;
		if (i == 0)
			itemVec.back().setPosition(Vector2f(player.getX() + 500, 0));
		else
			itemVec.back().setPosition(Vector2f(player.getX() - 500, 0));
		a = false;
	}
	else if (countTime % 14 != 0)
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
		window.draw(itemVec[i].body);
	}

	//potion
	if (countTime % 10 == 0 && j && potionVec.size() < 4)
	{
		int ps = rand() % 5;
		if (ps == 4)
			potionVec.push_back(hpBot);
		else
			potionVec.push_back(redbull);
		potionVec.back().setPosition(Vector2f(player.getX() - 1000 + (rand() % 2000), 0));
		j = false;
	}
	else if (countTime % 10 != 0)
	{
		j = true;
	}
	for (int i = 0; i < potionVec.size(); i++)
	{
		if (potionVec[i].Getcollision().CheckCollision(player.Getcollision()))
		{
			bottleCollect.setPlayingOffset(Time(seconds(0)));
			bottleCollect.play();
			if (potionVec[i].g == redbull.g)
				player.mana += 3000;
			else
				myHP += 3000;
			if (myHP > 10000) myHP = 10000;
			potionVec.erase(potionVec.begin() + i);
		}
	}

	for (int i = 0; i < potionVec.size(); i++)
	{
		potionVec[i].Update(deltaTime);
		window.draw(potionVec[i].body);
	}
}

void GameRunning::Trap()
{
	if (countTime % nTrap == 0 && k)
	{
		trapVec.push_back(trap);
		int i = rand() % 2;
		trapVec.back().setPosition(Vector2f(player.getX() - 400 + (rand() % 800), 0));
		k = false;
	}
	else if (countTime % nTrap != 0)
	{
		k = true;
	}
	for (int i = 0; i < trapVec.size(); i++)
	{
		if (trapVec[i].Getcollision().CheckCollision(player.Getcollision()))
		{
			if(trapVec[i].getY() < player.getY()) bomb.setPosition(Vector2f(trapVec[i].getX(), trapVec[i].getY() + 50));
			else bomb.setPosition(Vector2f(trapVec[i].getX(), trapVec[i].getY() - 25));
			bomb.setBomb(true);
			trapVec.erase(trapVec.begin() + i);
			if (myHP > 0) myHP -= 1500;
			if (myHP <= 0) myHP = 0;
		}
	}
	bomb.Update(deltaTime);
	if (bomb.showBomb())
	{
		window.draw(bomb.body);
	}

	for (int i = 0; i < trapVec.size(); i++)
	{
		trapVec[i].Update(deltaTime);
		window.draw(trapVec[i].body);
	}
}

void GameRunning::statusBar()
{
	//Bar
	bar.setPosition(Vector2f(camera.getCenter().x - 640, camera.getCenter().y - 360));
	window.draw(bar);

	Text times, textScore, textBat;
	//Time
	std::string dt = to_string(countTime);
	times.setFont(font);
	times.setString(dt);
	times.setCharacterSize(40);
	times.setFillColor(sf::Color::Red);
	times.setPosition(Vector2f(camera.getCenter().x + 275, camera.getCenter().y - 310));
	window.draw(times);

	//HP
	HP.setPosition(Vector2f(camera.getCenter().x - 583, camera.getCenter().y - 310));
	HP.setSize(Vector2f(myHP / 36.2, 25));
	window.draw(HP);

	//Mana
	MANA.setPosition(Vector2f(camera.getCenter().x - 583, camera.getCenter().y - 280));
	MANA.setSize(Vector2f(player.getMana() / 36.2, 25));
	window.draw(MANA);

	//score
	std::string score = to_string(playerScore);
	textScore.setFont(font);
	textScore.setString(score);
	textScore.setCharacterSize(50);
	textScore.setFillColor(sf::Color::Yellow);
	textScore.setOutlineColor(sf::Color::Black);
	textScore.setPosition(Vector2f(camera.getCenter().x - 238, camera.getCenter().y - 330));
	window.draw(textScore);

	std::string bn = to_string(batNumber);
	textBat.setFont(font);
	textBat.setString(bn);
	textBat.setCharacterSize(40);
	textBat.setFillColor(sf::Color::White);
	textBat.setPosition(Vector2f(camera.getCenter().x + 480, camera.getCenter().y - 310));
	window.draw(textBat);
}