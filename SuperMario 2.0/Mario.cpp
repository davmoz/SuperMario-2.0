#include "Mario.h"
#include <iostream>

Mario::Mario(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const float xVelocity)
	: Character(TileLocation, tilePositionInFile, position, xVelocity)
{
	this->coins = 0;
	this->marioTime = 0;
	this->boostTime = 0;
	this->boosted = false;
	this->font.loadFromFile("Fonts/Chunkfive.otf");
}

Mario::~Mario()
{

}

void Mario::drawCoinsAndTime(RenderWindow * window, const bool paused)
{
	this->timeSpent.setFont(this->font);
	this->coinsTaken.setFont(this->font);

	if (!paused)
	{
		if (clock.getElapsedTime().asSeconds() > 1.0f)
		{
			this->marioTime++;
			clock.restart();
		}
	}
	if (this->boosted)
	{
		if (this->boostTime == this->marioTime)
		{
			this->boosted = false;
			this->changeVelocityX(boosted);
		}
	}
	
	this->timeSpent.setString("TIME: " + to_string(this->marioTime));
	this->coinsTaken.setString("$: " + to_string(this->coins));
	this->coinsTaken.setPosition(this->getSprite().getPosition().x, 0);
	this->timeSpent.setPosition(this->getSprite().getPosition().x - 150, 0);
	window->draw(this->timeSpent);
	window->draw(this->coinsTaken);
}

void Mario::increaseCoins()
{
	this->coins++;
}

void Mario::changeMarioVelocityX(const bool effected)
{
	if (!this->boosted)
	{
		boostTime = marioTime + 10;
		this->boosted = true;
		this->changeVelocityX(boosted);
	}
	else
	{
		boostTime += 10;
	}
}

bool Mario::isBoosted()
{
	return this->boosted;
}
