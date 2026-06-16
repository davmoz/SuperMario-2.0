#include "Mario.h"
#include "Constants.h"
#include <iostream>

using namespace std;
using namespace sf;

Mario::Mario(const Texture &texture, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight)
	: Character(texture, tilePositionInFile, position, velocity, gravity, jumpheight)
{
	coins = 0;
	marioTime = 0;
	boostTime = 0;
	enemies = 0;
	boosted = false;
}

Mario::~Mario()
{

}

// Advance the in-level timers once per gameplay frame: the survival clock and
// the expiry of the temporary speed boost. The HUD itself is drawn by Hud.
void Mario::updateTimers()
{
	if (marioClock.getElapsedTime().asSeconds() > 1.0f)
	{
		marioTime++;
		marioClock.restart();
	}
	if (boosted && marioTime >= boostTime)
	{
		boosted = false;
		doubleVelocityX(boosted);
	}
	if (starActive && marioTime >= starEndTime)
		starActive = false;
	if (invulnerable && hitClock.getElapsedTime().asSeconds() > IFRAME_SECONDS)
		invulnerable = false;

	// Tint reflects the current power state (star wins, then big, then small).
	if (starActive)
		setAppearanceColor(sf::Color(255, 240, 80));
	else if (big)
		setAppearanceColor(sf::Color(140, 255, 140));
	else
		setAppearanceColor(sf::Color::White);
}

void Mario::grow()
{
	big = true;
}

void Mario::activateStar()
{
	starActive = true;
	starEndTime = marioTime + STAR_DURATION;
}

bool Mario::isStarActive() const
{
	return starActive;
}

bool Mario::isInvulnerable() const
{
	return invulnerable;
}

bool Mario::absorbHit()
{
	if (big)
	{
		big = false;
		invulnerable = true;
		hitClock.restart();
		return false; // survived, shrank to small
	}
	return true; // was small: Mario dies
}

void Mario::increaseCoins()
{
	coins++;
}

void Mario::increaseEnemiesKilled()
{
	enemies++;
}

void Mario::changeMarioVelocityX()
{
	if (!boosted)
	{
		boostTime = marioTime + BOOST_DURATION;
		boosted = true;
		doubleVelocityX(boosted);
	}
	else
	{
		boostTime += BOOST_DURATION;
	}
}

bool Mario::isBoosted()
{
	return boosted;
}

PlayerStats Mario::getStats() const
{
	return { coins, marioTime, enemies };
}

void Mario::applyStats(const PlayerStats &stats)
{
	coins = stats.coins;
	marioTime = stats.time;
	enemies = stats.enemies;
}

void Mario::exportScoreToFile(const string HighScoreFileLocation, const string name)
{
	int nrOfScores;
	string check;
	bool empty = false;

	string *playerNames = nullptr;
	int *playerTimes = nullptr;
	int *playerCoins = nullptr;
	int *enemiesKilled = nullptr;
	/*
	READ FROM FILE
	#####################################################################################################
	Opening file to READ if any scores are registered. If there are scores registered, 4 array are dynamically 
	allocated with the size of [registered scores + 1] for the new score to be registered. If the file is 
	empty, the first score will be added in the WRITE TO FILE section below.
	#####################################################################################################
	*/
	ifstream fromFile;
	fromFile.open(HighScoreFileLocation);
	if (fromFile.is_open())
	{
		getline(fromFile, check);
		if (check == "")
		{
			empty = true;
		}
		else
		{
			empty = false;
			nrOfScores = stoi(check);

			playerNames = new string[nrOfScores + 1];
			playerTimes = new int[nrOfScores + 1];
			playerCoins = new int[nrOfScores + 1];
			enemiesKilled = new int[nrOfScores + 1];

			for (int i = 0; i < nrOfScores; i++)
			{
				fromFile >> playerNames[i];
				fromFile >> playerTimes[i];
				fromFile >> playerCoins[i];
				fromFile >> enemiesKilled[i];
			}
		}
		fromFile.close();
	}

	/*
	WRITE TO FILE
	#####################################################################################################
	Re-opens the file to to add either the first score ever or to append the new score to 
	the score-arrays previously created and filled.
	#####################################################################################################
	*/
	ofstream toFile;
	toFile.open(HighScoreFileLocation);
	if (toFile.is_open())
	{
		if (empty)
		{
			toFile << 1 << endl;
			toFile << name << endl;
			toFile << marioTime << endl;
			toFile << coins << endl;
			toFile << enemies;
		}
		else
		{
			playerNames[nrOfScores] = name;
			playerTimes[nrOfScores] = marioTime;
			playerCoins[nrOfScores] = coins;
			enemiesKilled[nrOfScores] = enemies;
			// Sorting the list before writing to file
			sortScoreList(playerNames, playerTimes, playerCoins, enemiesKilled, nrOfScores + 1);
			
			toFile << nrOfScores + 1 << endl;
			for (int i = 0; i < nrOfScores + 1; i++)
			{
				toFile << playerNames[i] << endl;
				toFile << playerTimes[i] << endl;
				toFile << playerCoins[i] << endl;
				toFile << enemiesKilled[i] << endl;
			}
		}
	}
	toFile.close();
	delete[] playerNames;
	delete[] playerCoins;
	delete[] playerTimes;
	delete[] enemiesKilled;
}

void Mario::sortScoreList(string playerNames[], int times[], int coins[], int enemiesKilled[], int nrOfScores)
{
	
	int posOfBest = 0;
	string tempName;
	int tempCoin;
	int tempTime;
	int tempenemiesKilled;

	for (int i = 0; i < nrOfScores; i++)
	{
		posOfBest = i;
		for (int k = i + 1; k < nrOfScores; k++)
		{
			if ((enemiesKilled[k] + coins[k]) > (enemiesKilled[posOfBest] + coins[posOfBest]))
			{
				posOfBest = k;
			}
		}
		tempName = playerNames[i];
		tempTime = times[i];
		tempCoin = coins[i];
		tempenemiesKilled = enemiesKilled[i];

		playerNames[i] = playerNames[posOfBest];
		times[i] = times[posOfBest];
		coins[i] = coins[posOfBest];
		enemiesKilled[i] = enemiesKilled[posOfBest];

		playerNames[posOfBest] = tempName;
		times[posOfBest] = tempTime;
		coins[posOfBest] = tempCoin;
		enemiesKilled[posOfBest] = tempenemiesKilled;
	}
}
