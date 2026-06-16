#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Character.h"

// Run totals that persist across levels (carried from one level to the next).
struct PlayerStats
{
	int coins = 0;
	int time = 0;
	int enemies = 0;
};

class Mario : public Character
{
private:
	int coins;
	int marioTime;
	int enemies;
	bool boosted;
	int boostTime;
	bool big = false;            // grew via a grow mushroom; absorbs one hit
	bool starActive = false;     // star invincibility
	int starEndTime = 0;         // marioTime (seconds) at which the star ends
	bool invulnerable = false;   // brief grace period after taking a hit
	sf::Clock marioClock;
	sf::Clock hitClock;          // measures the post-hit grace period

public:
	Mario(const sf::Texture &texture, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const sf::Vector2f velocity, const float gravity, const float jumpheight);
	~Mario();
	void updateTimers();
	void increaseCoins();
	void increaseEnemiesKilled();
	void changeMarioVelocityX();
	bool isBoosted();

	// Power-ups and damage.
	void grow();
	void activateStar();
	bool isStarActive() const;
	bool isInvulnerable() const; // post-hit grace frames
	bool absorbHit();            // true if Mario died, false if he only shrank
	PlayerStats getStats() const;
	void applyStats(const PlayerStats &stats);
	void exportScoreToFile(const std::string HighScoreFileLocation, const std::string name);
	void sortScoreList(std::string names[], int times[], int coins[], int coinsPerSecond[], int nrOfScores);
};
