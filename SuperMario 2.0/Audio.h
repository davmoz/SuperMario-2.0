#pragma once
#include <SFML/Audio.hpp>

// The looping background track is streamed with sf::Music (the right tool for
// a multi-megabyte track); the short, frequently-overlapping effects are
// preloaded sf::SoundBuffer/sf::Sound pairs. The original code streamed every
// effect through sf::Music, which truncated overlapping sounds.
class Audio
{
private:
	sf::Music mainTheme;

	sf::SoundBuffer jumpBuffer;
	sf::SoundBuffer deadBuffer;
	sf::SoundBuffer coinBuffer;
	sf::SoundBuffer shroomBuffer;
	sf::SoundBuffer stompBuffer;
	sf::SoundBuffer finishBuffer;
	sf::SoundBuffer starBuffer;

	sf::Sound jumpSound;
	sf::Sound deadSound;
	sf::Sound coinSound;
	sf::Sound shroomSound;
	sf::Sound stompSound;
	sf::Sound finishSound;
	sf::Sound starSound;

public:
	Audio();
	~Audio();
	void themeMusicPlay();
	void themeMusicPause();
	void themeMusicReset();
	void jumpMusicPlay();
	void deadMusicPlay();
	void shroomMusicPlay();
	void coinMusicPlay();
	void stompMusicPlay();
	void finishMusicPlay();
	void finishMusicPause();
	void starMusicPlay();
};
