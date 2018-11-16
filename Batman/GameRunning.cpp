#include "GameRunning.h"


GameRunning::GameRunning(Vector2u size, std::string name)
{
	window.create(VideoMode(size.x, size.y), name, sf::Style::Close | sf::Style::Titlebar);
	display.setWindow(&window);
	select = 1;
	display.setView(false);
	runMenu = true;
	gameStart = false;
	showHighscore = false;
	MainMenu();
	m = false;
}

GameRunning::~GameRunning()
{
}

void GameRunning::MainMenu()
{

	float deltaTime = 0.0;
	while (runMenu)
	{
		deltaTime = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Return) || Mouse::isButtonPressed(Mouse::Left))
		{
			switch (display.getSelect())
			{
			case 1:
				runMenu = false;
				showHighscore = false;
				gameStart = true;
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
	 
	while (gameStart) {
		deltaTime = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
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

		/////////////////Secret Scene
		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			m = true;
			display.setView(false);
		}
		if (m)
		{
			display.setDT(deltaTime);
			display.moreStory();
			display.playMoreStory();
		}////////////////////////////
		else
		{
			display.setDT(deltaTime);
			display.Playing();
		}
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

