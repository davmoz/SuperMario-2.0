#include "Audio.h"
#include <iostream>



Audio::Audio()
{
	if (!jumpSound.openFromFile("Music/jump.wav"))
		std::cerr << "Error: Failed to load audio from Music/jump.wav" << std::endl;
	if (!deadSound.openFromFile("Music/dead.wav"))
		std::cerr << "Error: Failed to load audio from Music/dead.wav" << std::endl;
	if (!coinSound.openFromFile("Music/coin.wav"))
		std::cerr << "Error: Failed to load audio from Music/coin.wav" << std::endl;
	if (!shroomSound.openFromFile("Music/shroom.wav"))
		std::cerr << "Error: Failed to load audio from Music/shroom.wav" << std::endl;
	if (!stompSound.openFromFile("Music/stomp.wav"))
		std::cerr << "Error: Failed to load audio from Music/stomp.wav" << std::endl;
	if (!mainTheme.openFromFile("Music/maintheme.ogg"))
		std::cerr << "Error: Failed to load audio from Music/maintheme.ogg" << std::endl;
	if (!finishSound.openFromFile("Music/finish.wav"))
		std::cerr << "Error: Failed to load audio from Music/finish.wav" << std::endl;
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

void Audio::finishMusicPlay()
{
	finishSound.play();
}

void Audio::finishMusicPause()
{
	finishSound.pause();
}
