#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
using namespace sf;
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
	Mario(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const float xVelocity);
	virtual ~Mario();
	void drawCoinsAndTime(RenderWindow *window, const bool paused);
	void increaseCoins();
	void changeMarioVelocityX(const bool effected = false);
	bool isBoosted();
};