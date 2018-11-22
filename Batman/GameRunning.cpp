#include "GameRunning.h"


GameRunning::GameRunning(Vector2u size, std::string name)
{
	window.create(VideoMode(size.x, size.y), name, sf::Style::Close | sf::Style::Resize);
	display.setWindow(&window);
	display.setView(false);
	state = 1;
	exit = 0;
	runMenu = 1;
	gameStart = 2;
	showHighscore = 3;
	playerDead = 4;
	bgSound.openFromFile("sound/bgSound.ogg");
	bgSound.setVolume(50);
	bgSound.setPlayingOffset(Time(seconds(0)));
	bgSound.play();
	MainMenu();
}

GameRunning::~GameRunning()
{
}

void GameRunning::MainMenu()
{
	float deltaTime = 0.0;
	window.setMouseCursorVisible(true);
	String yourname;
	Text player,enterYourName;
	Font font;
	font.loadFromFile("font/mer.ttf");
	enterYourName.setFont(font);
	enterYourName.setString("Please Enter Your Name");
	enterYourName.setCharacterSize(50);
	enterYourName.setPosition(250, 100);
	Time time;
	while (window.isOpen())
	{
		deltaTime = clock1.restart().asSeconds();
		
		Event event;
		while (window.pollEvent(event))
		{
			if (state == playerDead)
			{
				
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode == '\b') {//ถ้ากด Backspace เป็นการลบตัวอักษร
						yourname.erase(yourname.getSize() - 1, 1);
						player.setFont(font);
						player.setString(yourname);
					}
					else {
						string name;
						yourname += static_cast<char>(event.text.unicode);
						name += static_cast<char>(event.text.unicode);
						if ((event.text.unicode < 128) && (yourname.getSize() < 15)) {
							player.setFont(font);
							player.setString(yourname);
						}
					}
					player.setCharacterSize(60);   //เซ็ตขนาดของข้อความ
					player.setPosition(250.0f, 200.0f);  //เซ็ตขนาดของข้อความ
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Return) {
						player.setString(yourname);
						player.setPosition(250, 300);
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
			if (Keyboard::isKeyPressed(Keyboard::Return) || (Mouse::isButtonPressed(Mouse::Left) && display.msCheck))
			{
				switch (display.getSelect())
				{
				case 1:

					display.setView(true);
					state = gameStart;
					bgSound.setVolume(30);
					break;
				case 2:
					display.setView(false);
					state = showHighscore;
					break;
				case 3:
					window.close();
					state = exit;
					break;
				}
			}
			display.setDT(deltaTime);
			display.drawMainMenu();
		}

		if (state == gameStart)
		{
			time = clock2.getElapsedTime();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				display.setView(false);
				state = runMenu;
			}
			if (display.playerisDead())
			{
				state = playerDead;
				display.setView(false);
				bgSound.stop();
			}
			display.setDT(deltaTime);
			display.timeElapse(time.asSeconds());
			display.Playing();
		}
		if (state == showHighscore)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				display.setView(false);
				state = runMenu;
			}
			display.drawHighscore();
		}
		if (state == playerDead)
		{
			window.clear();
			window.draw(enterYourName);
			window.draw(player);
			window.display();
		}
		
	}
}
