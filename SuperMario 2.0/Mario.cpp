#include "Mario.h"
#include <iostream>

Mario::Mario(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity)
	: Character(TileLocation, tilePositionInFile, position, velocity)
{
	this->coins = 0;
	this->marioTime = 0;
	this->boostTime = 0;
	this->boosted = false;
	this->font.loadFromFile("Fonts/Super Mario Bros.ttf");
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
			this->doubleVelocityX(boosted);
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
		this->doubleVelocityX(boosted);
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

void Mario::exportScoreToFile(const string name)
{
	int nrOfScores;
	string check;
	bool empty = false;

	string *names = nullptr;
	int *times = nullptr;
	int *coins = nullptr;
	double *coinsPerSecond = nullptr;
	/*
	READ FROM FILE
	#####################################################################################################
	Opening file to READ if any scores are registered. If there are scores registered, 4 array are dynamically 
	allocated with the size of [registered scores + 1] for the new score to be registered. If the file is 
	empty, the first score will be added in the WRITE TO FILE section below.
	#####################################################################################################
	*/
	ifstream fromFile;
	fromFile.open("Score/scores.txt");
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

			names = new string[nrOfScores + 1];
			times = new int[nrOfScores + 1];
			coins = new int[nrOfScores + 1];
			coinsPerSecond = new double[nrOfScores + 1];

			for (int i = 0; i < nrOfScores; i++)
			{
				fromFile >> names[i];
				fromFile >> times[i];
				fromFile >> coins[i];
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
	toFile.open("Score/scores.txt");
	if (toFile.is_open())
	{
		if (empty)
		{
			toFile << 1 << endl;
			toFile << name << endl;
			toFile << this->marioTime << endl;
			toFile << this->coins << endl;
			toFile << this->coins / (double)this->marioTime;
		}
		else
		{
			names[nrOfScores] = name;
			times[nrOfScores] = this->marioTime;
			coins[nrOfScores] = this->coins;
			coinsPerSecond[nrOfScores] = this->coins / (double)this->marioTime;
			// Sortera

			// Skriv till fil
			toFile << nrOfScores + 1 << endl;
			for (int i = 0; i < nrOfScores + 1; i++)
			{
				toFile << names[i] << endl;
				toFile << times[i] << endl;
				toFile << coins[i] << endl;
				toFile << coinsPerSecond[i] << endl;
			}
		}
	}
	toFile.close();
	delete[] names;
	delete[] coins;
	delete[] times;
	delete[] coinsPerSecond;
}
