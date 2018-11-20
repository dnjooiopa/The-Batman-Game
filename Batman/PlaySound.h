#pragma once
#include <SFML/Audio.hpp>
using namespace sf;

class PlaySound
{
public:
	PlaySound();
	~PlaySound();

	void playPunchSound();


private:
	Music sound[10];

};
