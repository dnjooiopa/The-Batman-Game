#include "GameRunning.h"


GameRunning::GameRunning(Vector2u size, std::string name)
{
	window.create(VideoMode(size.x, size.y), name, sf::Style::Close | sf::Style::Titlebar);
	display.setWindow(&window);
	display.setView(false);
	state = 1;
	exit = 0;
	runMenu = 1;
	gameStart = 2;
	showHighscore = 3;
	lastTime = 0;
	dsSound.openFromFile("sound/darksoul.ogg");
	GameOpen();
}

GameRunning::~GameRunning()
{
}

void GameRunning::GameOpen()
{
	float deltaTime = 0.0;
	Time time;
	while (window.isOpen())
	{
		deltaTime = clock1.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				state = exit;
			}
		}
		///////Menu/////////
		if (state == runMenu)
		{
			if (Keyboard::isKeyPressed(Keyboard::Return) || (Mouse::isButtonPressed(Mouse::Left) && display.msCheck))
			{
				switch (display.getSelect())
				{
				case 1:
					display.setView(true);
					state = gameStart;
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
		//////Play Game///////
		if (state == gameStart)
		{	
			time = clock2.getElapsedTime();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				display.setView(false);
				state = runMenu;
			}
			display.setDT(deltaTime);
			display.timeElapse(time.asSeconds());
			display.Playing();
		}

		///////Show High Score/////
		if (state == showHighscore)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape) || (Mouse::isButtonPressed(Mouse::Left) && display.mCheck))
			{
				display.setView(false);
				state = runMenu;
			}
			display.drawHighscore();
		}
	}
}
