#include "Audio.h"



Audio::Audio()
{
	this->jumpSound.openFromFile("Music/jump.wav");
	this->deadSound.openFromFile("Music/dead.wav");
	this->coinSound.openFromFile("Music/coin.wav");
	this->shroomSound.openFromFile("Music/shroom.wav");
	this->mainTheme.openFromFile("Music/maintheme.ogg");
}


Audio::~Audio()
{

}

void Audio::themeMusicPlay()
{
	this->mainTheme.play();
}

void Audio::themeMusicPause()
{
	this->mainTheme.pause();
}

void Audio::themeMusicReset()
{
	this->mainTheme.stop();
}

void Audio::jumpMusicPlay()
{
	this->jumpSound.play();
}

void Audio::deadMusicPlay()
{
	this->deadSound.play();
}

void Audio::shroomMusicPlay()
{
	this->shroomSound.play();
}

void Audio::coinMusicPlay()
{
	this->coinSound.play();
}
