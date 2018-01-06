#include "Mario.h"
#include <iostream>

Mario::Mario(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight)
	: Character(TileLocation, tilePositionInFile, position, velocity, gravity, jumpheight)
{
	coins = 0;
	marioTime = 0;
	boostTime = 0;
	boosted = false;
	font.loadFromFile("Fonts/Super Mario Bros.ttf");
}

Mario::~Mario()
{

}

void Mario::drawCoinsAndTime(RenderWindow * window, const bool paused)
{
	timeSpent.setFont(font);
	coinsTaken.setFont(font);

	if (!paused)
	{
		if (clock.getElapsedTime().asSeconds() > 1.0f)
		{
			marioTime++;
			clock.restart();
		}
	}
	if (boosted)
	{
		if (boostTime == marioTime)
		{
			boosted = false;
			doubleVelocityX(boosted);
		}
	}
	
	timeSpent.setString("TIME: " + to_string(marioTime));
	coinsTaken.setString("$: " + to_string(coins));
	coinsTaken.setPosition(getPosition().x, 0);
	timeSpent.setPosition(getPosition().x - 150, 0);
	window->draw(timeSpent);
	window->draw(coinsTaken);
}

void Mario::increaseCoins()
{
	coins++;
}

void Mario::changeMarioVelocityX(const bool effected)
{
	if (!boosted)
	{
		boostTime = marioTime + 10;
		boosted = true;
		doubleVelocityX(boosted);
	}
	else
	{
		boostTime += 10;
	}
}

bool Mario::isBoosted()
{
	return boosted;
}

void Mario::exportScoreToFile(const string HighScoreFileLocation, const string name)
{
	int nrOfScores;
	string check;
	bool empty = false;

	string *playerNames = nullptr;
	int *playerTimes = nullptr;
	int *playerCoins = nullptr;
	int *coinsPerSecond = nullptr;
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
			coinsPerSecond = new int[nrOfScores + 1];

			for (int i = 0; i < nrOfScores; i++)
			{
				fromFile >> playerNames[i];
				fromFile >> playerTimes[i];
				fromFile >> playerCoins[i];
				fromFile >> coinsPerSecond[i];
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
			toFile << coins / (double)marioTime;
		}
		else
		{
			playerNames[nrOfScores] = name;
			playerTimes[nrOfScores] = marioTime;
			playerCoins[nrOfScores] = coins;
			coinsPerSecond[nrOfScores] = coins / (double)marioTime;
			// Sorting the list before writing to file
			sortScoreList(playerNames, playerTimes, playerCoins, coinsPerSecond, nrOfScores + 1);
			
			toFile << nrOfScores + 1 << endl;
			for (int i = 0; i < nrOfScores + 1; i++)
			{
				toFile << playerNames[i] << endl;
				toFile << playerTimes[i] << endl;
				toFile << playerCoins[i] << endl;
				toFile << coinsPerSecond[i] << endl;
			}
		}
	}
	toFile.close();
	delete[] playerNames;
	delete[] playerCoins;
	delete[] playerTimes;
	delete[] coinsPerSecond;
}

void Mario::sortScoreList(string playerNames[], int times[], int coins[], int coinsPerSecond[], int nrOfScores)
{
	int greatestCoinPerSecond = 0;

	string tempName;
	int tempCoin;
	int tempTime;
	int tempCoinsPerSecond;

	for (int i = 0; i < nrOfScores; i++)
	{
		for (int k = i + 1; k < nrOfScores; k++)
		{
			if (coinsPerSecond[k] > coinsPerSecond[i])
			{
				greatestCoinPerSecond = k;
			}
		}
		tempName = playerNames[i];
		tempTime = times[i];
		tempCoin = coins[i];
		tempCoinsPerSecond = coinsPerSecond[i];

		playerNames[i] = playerNames[greatestCoinPerSecond];
		times[i] = times[greatestCoinPerSecond];
		coins[i] = coins[greatestCoinPerSecond];
		coinsPerSecond[i] = coinsPerSecond[greatestCoinPerSecond];

		playerNames[greatestCoinPerSecond] = tempName;
		times[greatestCoinPerSecond] = tempTime;
		coins[greatestCoinPerSecond] = tempCoin;
		coinsPerSecond[greatestCoinPerSecond] = tempCoinsPerSecond;
	}
}
