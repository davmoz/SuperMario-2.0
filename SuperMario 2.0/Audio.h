#pragma once
#include <SFML/Audio.hpp>

class Audio
{
private:
	sf::Music jumpSound;
	sf::Music deadSound;
	sf::Music coinSound;
	sf::Music shroomSound;
	sf::Music stompSound;
	sf::Music mainTheme;
	sf::Music finishSound;
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
};
