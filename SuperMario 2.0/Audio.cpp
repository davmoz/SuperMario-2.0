#include "Audio.h"
#include <iostream>



namespace
{
	// Load a sound buffer and bind it to its voice, reporting failures.
	void loadSfx(sf::SoundBuffer& buffer, sf::Sound& sound, const char* path)
	{
		if (!buffer.loadFromFile(path))
			std::cerr << "Error: Failed to load audio from " << path << std::endl;
		else
			sound.setBuffer(buffer);
	}
}

Audio::Audio()
{
	if (!mainTheme.openFromFile("Music/maintheme.ogg"))
		std::cerr << "Error: Failed to load audio from Music/maintheme.ogg" << std::endl;
	mainTheme.setLoop(true);

	loadSfx(jumpBuffer, jumpSound, "Music/jump.wav");
	loadSfx(deadBuffer, deadSound, "Music/dead.wav");
	loadSfx(coinBuffer, coinSound, "Music/coin.wav");
	loadSfx(shroomBuffer, shroomSound, "Music/shroom.wav");
	loadSfx(stompBuffer, stompSound, "Music/stomp.wav");
	loadSfx(finishBuffer, finishSound, "Music/finish.wav");
	loadSfx(starBuffer, starSound, "Music/star.wav");
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

void Audio::starMusicPlay()
{
	starSound.play();
}
