#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
class Audio
{
private:
	Music jumpSound;
	Music deadSound;
	Music coinSound;
	Music shroomSound;
	Music mainTheme;
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
};

