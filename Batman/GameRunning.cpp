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
	endTexture.loadFromFile("sprite/end.png");
	endBackground.setTexture(endTexture);
	bgSound.openFromFile("sound/bgSound.ogg");
	bgSound.setVolume(80);
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
	String yourname;
	Text player,enterYourName;
	Font font;
	font.loadFromFile("font/mer.ttf");
	enterYourName.setFont(font);
	enterYourName.setString("         YOU DIED\nPlease Enter Your Name");
	enterYourName.setCharacterSize(50);
	enterYourName.setPosition(400, 100);
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
					if (event.text.unicode == '\b' && yourname.getSize()) {//ถ้ากด Backspace เป็นการลบตัวอักษร
						yourname.erase(yourname.getSize() - 1, 1);
						player.setFont(font);
						player.setString(yourname);
					}
					else {
						string name;
						yourname += static_cast<char>(event.text.unicode);
						name += static_cast<char>(event.text.unicode);
						if ((event.text.unicode < 128) && (yourname.getSize() < 10)) {
							player.setFont(font);
							player.setString(yourname);
						}
					}
					player.setCharacterSize(60);   //เซ็ตขนาดของข้อความ
					player.setPosition(415.0f, 410.0f);  //เซ็ตขนาดของข้อความ
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Return) {
						player.setString(yourname);
						display.setScore(yourname);
						window.close();
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
			if (Keyboard::isKeyPressed(Keyboard::Return) || (Mouse::isButtonPressed(Mouse::Left) && display.msCheck))
			{
				switch (display.getSelect())
				{
				case 1:

					display.setView(true);
					state = gameStart;
					bgSound.setVolume(80);
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
			window.setMouseCursorVisible(false);
			time = clock2.getElapsedTime();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				display.setView(false);
				state = runMenu;
			}
			if (display.playerisDead())
			{
				Sleep(1000);
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
			window.draw(endBackground);
			window.draw(player);
			window.display();
		}
		
	}
}
