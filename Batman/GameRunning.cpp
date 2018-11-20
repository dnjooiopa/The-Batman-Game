#include "GameRunning.h"


GameRunning::GameRunning(Vector2u size, std::string name)
{
	window.create(VideoMode(size.x, size.y), name, sf::Style::Close | sf::Style::Titlebar);
	display.setWindow(&window);
	display.setView(false);
	state = 1;
	runMenu = 1;
	gameStart = 2;
	showHighscore = 3;
	m = false;
	dsSound.openFromFile("sound/darksoul.ogg");
	MainMenu();
}

GameRunning::~GameRunning()
{
}

void GameRunning::MainMenu()
{
	float deltaTime = 0.0;
	while (window.isOpen())
	{
		deltaTime = clock1.restart().asSeconds();
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				state = 0;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Return) || (Mouse::isButtonPressed(Mouse::Left)&&display.msCheck))
		{
			switch (display.getSelect())
			{
			case 1:
				
				display.setView(true);
				GameStart();
				break;
			case 2:
				runMenu = false;
				showHighscore = true;
				gameStart = false;
				display.setView(false);
				Highscore();
				break;
			case 3:
				window.close();
				runMenu = false;
				break;
			}
		}
		display.setDT(deltaTime);
		display.drawMainMenu();
	}
}

void GameRunning::GameStart()
{
	float deltaTime = 0.0;
	Time time;
	while (gameStart) {
		deltaTime = clock1.restart().asSeconds();
		time = clock2.getElapsedTime();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
				gameStart = false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			runMenu = true;
			gameStart = false;
			display.setView(false);
			m = false;
			MainMenu();
		}
		display.setDT(deltaTime);
		display.timeElapse(time.asSeconds());
		display.Playing();
	}
}

void GameRunning::Highscore()
{
	while (showHighscore) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
				showHighscore = false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape) )
		{
			runMenu = true;
			showHighscore = false;
			gameStart = false;
			display.setView(false);
			MainMenu();
		}
		display.drawHighscore();
	}

}

