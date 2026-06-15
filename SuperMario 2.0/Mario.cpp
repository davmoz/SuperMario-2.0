#include "Mario.h"
#include "Constants.h"
#include <iostream>

using namespace std;
using namespace sf;

Mario::Mario(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight)
	: Character(TileLocation, tilePositionInFile, position, velocity, gravity, jumpheight)
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
