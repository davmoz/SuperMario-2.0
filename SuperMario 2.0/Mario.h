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
	bool boosted;
	int boostTime;
	Font font;
	Text coinsTaken, timeSpent;
	Clock clock;
public:
	Mario(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight);
	virtual ~Mario();
	void drawCoinsAndTime(RenderWindow *window, const bool paused);
	void increaseCoins();
	void changeMarioVelocityX(const bool effected = false);
	bool isBoosted();
	void exportScoreToFile(const string HighScoreFileLocation, const string name);
	void sortScoreList(string names[], int times[], int coins[], int coinsPerSecond[], int nrOfScores);
};