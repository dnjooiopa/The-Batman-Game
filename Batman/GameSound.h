#pragma once
#include <SFML/Audio.hpp>
using namespace sf;

class GameSound
{
public:
	GameSound() 
	{
		//punch
		sound[1].openFromFile("sound/punch.ogg");
		sound[1].setVolume(30);
		//batarang

	}
	~GameSound();

	void playPunchSound()
	{
		sound[1].setPlayingOffset(Time(seconds(0)));
		sound[1].play();
	}


private:
	Music sound[10];

};

