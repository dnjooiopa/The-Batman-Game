#include "PlaySound.h"



PlaySound::PlaySound()
{
	//punch
	sound[1].openFromFile("sound/punch.ogg");
	sound[1].setVolume(30);
	//batarang
}


PlaySound::~PlaySound()
{
}

void PlaySound::playPunchSound()
{
	sound[1].setPlayingOffset(Time(seconds(0)));
	sound[1].play();
}
