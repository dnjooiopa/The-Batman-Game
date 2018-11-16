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
	Clock clock;
	bool running;
	int select;
	bool runMenu;
	bool gameStart;
	bool showHighscore;
	bool m;
	Music dsSound;
};

