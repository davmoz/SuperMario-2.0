#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Character.h"
using namespace sf;
using namespace std;
class Mario : public Character
{
private:
	int coins;
	int marioTime;
	int enemies;
	bool boosted;
	int boostTime;
	Font font;
	Text coinsTaken, timeSpent, enemiesKilled;
	Clock marioClock;

public:
	Mario(const string TileLocation, const IntRect tilePositionInFile, const string fontFileLocation, const Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight);
	~Mario();
	void updateAndDrawCoinsAndTime(RenderWindow *window, const bool paused);
	void increaseCoins();
	void increaseEnemiesKilled();
	void changeMarioVelocityX(const bool effected = false);
	bool isBoosted();
	void exportScoreToFile(const string HighScoreFileLocation, const string name);
	void sortScoreList(string names[], int times[], int coins[], int coinsPerSecond[], int nrOfScores);
};