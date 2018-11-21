#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Display.h"
#include <iostream>

using namespace sf;

class GameRunning
{
public:
	GameRunning(Vector2u size,std::string name);
	~GameRunning();

	void GameStart();
	void MainMenu();
	void Highscore();

private:
	RenderWindow window;
	Display display;
	Clock clock1;
	Clock clock2;
	bool running;
	int state;
	int exit;
	int runMenu;
	int gameStart;
	int showHighscore;
	Music dsSound;
};

