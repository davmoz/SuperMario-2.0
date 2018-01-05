#include "Game.h"
#include <iostream>

Game::Game(RenderWindow *window)
{
	collision = new Collision;
	
	menuFont.loadFromFile("Fonts/Super Mario Bros.ttf");
	gamePaused = false;
	gameOver = false;
	viewingScores = false;
	viewingRegistrationPage = false;
	selectedMenu = 0;
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setFont(menuFont);
		menu[i].setString(menuOptions[i]);
	}
	menu[0].setFillColor(Color(Color::Red));
}

Game::Game()
{

}

Game::~Game()
{
	delete collision;
}

void Game::runGame(RenderWindow *window, Clock *clock)
{
	audio.themeMusicPlay();
	float totaltime = 0.0f;

	while (window->isOpen())
	{
		totaltime += clock->restart().asSeconds(); 
		
		window->setFramerateLimit(90);
		
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
			if (viewingRegistrationPage)
			{
				registerPlayerName();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) && event.key.code == Keyboard::Escape && !gameOver)
			{
				if (!gamePaused)
				{
					audio.themeMusicPause();
					gamePaused = true;
				}
				else
				{
					audio.themeMusicPlay();
					gamePaused = false;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space) && event.key.code == Keyboard::Space)
			{
				collision->jump();
				audio.jumpMusicPlay();
			}
		}
		if (!gamePaused)	
		{
			update(totaltime);
			collision->updateCharacter(totaltime);
			collision->moveEnemy();
			collision->checkMarioCoinCollision();
			collision->checkMarioShroomCollision();
			if (collision->checkMarioEnemyCollision())
			{
				audio.themeMusicPause();
				audio.deadMusicPlay();
				gameOver = true;
				gamePaused = true;
				viewingRegistrationPage = true;
				selectedMenu = 2;
			}
			window->clear();
			draw(window);
			window->display();
		}
		else
		{
			window->setFramerateLimit(10);
			window->clear();
			draw(window);
			window->display();
		}
	}
}

void Game::update(float &totaltime)
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		collision->MarioMoveRight();
		collision->moveViewRight();
		collision->updateCharTexture(totaltime, 0, 32, 3, 16);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		collision->MarioMoveLeft();
		collision->moveViewLeft();
		collision->updateCharTexture(totaltime, 0, 32, 3, 16);
	}
}

void Game::loadMainMenu(RenderWindow *window)
{
	if (gameOver && !viewingScores && !viewingRegistrationPage)
	{
		menuOptions[0] = "New Game";
		menu[0].setString(menuOptions[0]);

		for (int i = 1; i < nrOfMenuOptions; i++)
		{
			menu[i].setString(menuOptions[i]);
		}
	}
	else if(!gameOver && !viewingScores && !viewingRegistrationPage)
	{
		menuOptions[0] = "Resume";
		menu[0].setString(menuOptions[0]);

		for (int i = 1; i < nrOfMenuOptions; i++)
		{
			menu[i].setString(menuOptions[i]);
		}
	}
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setPosition(Vector2f(window->getView().getCenter().x, window->getView().getCenter().y / 2.5f * (i + 1)));
		menu[i].setOrigin(menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.0f, menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.0f);
	}
}

void Game::draw(RenderWindow * window)
{
	if (gamePaused)
	{
		drawMenu(window);
		handleMenuInput(window);
	}
	else
	{
		collision->draw(window, gamePaused);
	}
}

void Game::drawMenu(RenderWindow * window)
{
	if (!viewingScores)
	{
		loadMainMenu(window);
	}
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		window->draw(menu[i]);
	}
}

void Game::handleMenuInput(RenderWindow * window)
{
	if (Keyboard::isKeyPressed(Keyboard::Up) && event.text.unicode == Keyboard::Up)
	{
		if (selectedMenu - 1 >= 0)
		{
			menu[selectedMenu].setFillColor(Color(Color::White));
			selectedMenu--;
			menu[selectedMenu].setFillColor(Color(Color::Red));
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && event.text.unicode == Keyboard::Down)
	{
		if (selectedMenu + 1 < nrOfMenuOptions)
		{
			menu[selectedMenu].setFillColor(Color(Color::White));
			selectedMenu++;
			menu[selectedMenu].setFillColor(Color(Color::Red));
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Return) || event.text.unicode == Keyboard::Return)
	{
		switch (selectedMenu)
		{
		case 0: {
			if (gameOver && !viewingScores && !viewingRegistrationPage) // New Game
			{
				delete collision;
				collision = new Collision;
				gameOver = false;
				gamePaused = false;
				audio.themeMusicReset();
				audio.themeMusicPlay();
			}
			else if (!gameOver && !viewingScores && !viewingRegistrationPage) // Resume Game
			{
				audio.themeMusicPlay();
				gamePaused = false;
			}
			break;
		}
		case 1: {
			// Restart Game
			if (!viewingScores && !viewingRegistrationPage)
			{
				delete collision;
				collision = new Collision;
				gameOver = false;
				gamePaused = false;
				audio.themeMusicReset();
				audio.themeMusicPlay();
			}
			break;
		}
		case 2: {
			if (!viewingRegistrationPage)
			{
				viewingScores = true;
				importHighScores("Score/scores.txt", 3);
				loadMainMenu(window);
			}
			break;
		}
		case 3: {
			cout << "times entered " << endl;
			if (viewingScores)
			{
				viewingScores = false;
			}
			else if (viewingRegistrationPage)
			{
				viewingRegistrationPage = false;
			}
			else
			{
				// Quit Game
				window->close();
			}

			break;
		}
		default:
			break;
		}
	}
}

void Game::importHighScores(const string fileLocation, int NrOfScoresToView)
{
	ifstream fromFile;
	fromFile.open(fileLocation);
	if (fromFile.is_open())
	{
		int nrOfScores;
		string name;
		int time = 0;
		int coins = 0;
		int coinsPerSecond = 0;
		fromFile >> nrOfScores;
		
		for (int i = 0; i < NrOfScoresToView; i++)
		{
			fromFile >> name;
			fromFile >> time;
			fromFile.ignore();
			fromFile >> coins;
			fromFile.ignore();
			fromFile >> coinsPerSecond;
			fromFile.ignore();
			containerString = to_string(i + 1) + ". Name: " + name + " Coins: " + to_string(coins) + " time: " + to_string(time) + " Coins/Sec: " + to_string(coinsPerSecond);
			menu[i].setString(containerString);
		}
		containerString = "Back";
		menu[NrOfScoresToView].setString(containerString);
	}
	fromFile.close();
}

void Game::registerPlayerName()
{
	menu[0].setString("");
	menu[1].setString("Name:");
	menu[3].setString("Enter");
	if (Event::TextEntered)
	{
		if (event.text.unicode == 32)
		{

		}
		else if (event.text.unicode == Keyboard::BackSpace)
		{
			containerString = containerString.substr(0, containerString.length() - 1);
			menu[2].setString(containerString);
		}
		else if (event.text.unicode == Keyboard::Up || event.text.unicode == Keyboard::Down || event.text.unicode == Keyboard::Left || event.text.unicode == Keyboard::Right)
		{

		}
		else if ((event.text.unicode >= 48 && event.text.unicode <= 57 && event.text.unicode != Keyboard::Space) || (event.text.unicode >= 65 && event.text.unicode <= 122))
		{
			containerString += (char)(event.text.unicode);
			menu[2].setString(containerString);
		}
		else if (event.text.unicode == Keyboard::Return && Keyboard::isKeyPressed(Keyboard::Return))
		{
			collision->saveMarioStats(containerString);
		}
	}
}
