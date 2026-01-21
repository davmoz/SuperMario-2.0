#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Character.h"

class Mario : public Character
{
private:
	int coins;
	int marioTime;
	int enemies;
	bool boosted;
	int boostTime;
	sf::Font font;
	sf::Text coinsTaken, timeSpent, enemiesKilled;
	sf::Clock marioClock;

public:
	Mario(const std::string TileLocation, const sf::IntRect tilePositionInFile, const std::string fontFileLocation, const sf::Vector2f position, const sf::Vector2f velocity, const float gravity, const float jumpheight);
	~Mario();
	void updateAndDrawCoinsAndTime(sf::RenderWindow *window, const bool paused);
	void increaseCoins();
	void increaseEnemiesKilled();
	void changeMarioVelocityX();
	bool isBoosted();
	void exportScoreToFile(const std::string HighScoreFileLocation, const std::string name);
	void sortScoreList(std::string names[], int times[], int coins[], int coinsPerSecond[], int nrOfScores);
};
