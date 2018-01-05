#include "Audio.h"



Audio::Audio()
{
	jumpSound.openFromFile("Music/jump.wav");
	deadSound.openFromFile("Music/dead.wav");
	coinSound.openFromFile("Music/coin.wav");
	shroomSound.openFromFile("Music/shroom.wav");
	stompSound.openFromFile("Music/stomp.wav");
	mainTheme.openFromFile("Music/maintheme.ogg");
}


Audio::~Audio()
{

}

void Audio::themeMusicPlay()
{
	mainTheme.play();
}

void Audio::themeMusicPause()
{
	mainTheme.pause();
}

void Audio::themeMusicReset()
{
	mainTheme.stop();
}

void Audio::jumpMusicPlay()
{
	jumpSound.play();
}

void Audio::deadMusicPlay()
{
	deadSound.play();
}

void Audio::shroomMusicPlay()
{
	shroomSound.play();
}

void Audio::coinMusicPlay()
{
	coinSound.play();
}

void Audio::stompMusicPlay()
{
	stompSound.play();
}
