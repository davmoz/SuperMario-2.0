#include "Game.h"
#include <iostream>

Game::Game(RenderWindow *window)
{
	this->window = window;
	collision = new Collision(HIGHSCOREFILE, TILEFILE, FONTFILE, COORDFILE);
	if (!menuFont.loadFromFile(FONTFILE))
		std::cerr << "Error: Failed to load font from " << FONTFILE << std::endl;
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

void Game::runGame()
{
	srand(time(0));
	audio.themeMusicPlay();
	while (window->isOpen())
	{
		
		window->setFramerateLimit(90);
		
		while (window->pollEvent(event))
		{
			
			if (viewingRegistrationPage)
			{
				registerPlayerName();
			}
			if (gamePaused)
			{
				drawMenu();
			}
			if (event.type == Event::Closed)
				window->close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && !gameOver)
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
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && !gamePaused)
			{
				collision->jump();
				audio.jumpMusicPlay();
			}
		}
		if (!gamePaused)	
		{
			update();
			collision->updateCharacter();
			collision->moveEnemy();
			collision->checkMarioLootCollision();
			if (collision->checkMarioHostileCollision())
			{
				audio.themeMusicPause();
				audio.deadMusicPlay();
				viewingRegistrationPage = true;
				gameOver = true;
				gamePaused = true;
			}
			else if (collision->checkMarioFinishCollision())
			{
				audio.themeMusicPause();
				audio.finishMusicPlay();
				viewingRegistrationPage = true;
				gameOver = true;
				gamePaused = true;
			}
			window->clear();
			collision->draw(window, gamePaused);
			window->display();
		}
	}
}

void Game::update()
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		collision->MarioMoveRight();
		collision->moveViewRight();
		collision->updateCharTexture(3);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		collision->MarioMoveLeft();
		collision->moveViewLeft();
		collision->updateCharTexture(3);
	}
}

void Game::loadMainMenu()
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

void Game::drawMenu()
{
	window->clear();
	if (!viewingScores)
	{
		loadMainMenu();
	}
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		window->draw(menu[i]);
	}
	window->display();
	handleMenuInput();
}

void Game::handleMenuInput()
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
	{
		if (selectedMenu - 1 >= 0)
		{
			menu[selectedMenu].setFillColor(Color(Color::White));
			selectedMenu--;
			menu[selectedMenu].setFillColor(Color(Color::Red));
		}
	}
	else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
	{
		if (selectedMenu + 1 < nrOfMenuOptions)
		{
			menu[selectedMenu].setFillColor(Color(Color::White));
			selectedMenu++;
			menu[selectedMenu].setFillColor(Color(Color::Red));
		}
	}
	else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
	{
		switch (selectedMenu)
		{
		case 0: {
			// New Game
			if (gameOver && !viewingScores && !viewingRegistrationPage) 
			{
				delete collision;
				collision = new Collision(HIGHSCOREFILE, TILEFILE, FONTFILE, COORDFILE);
				gameOver = false;
				gamePaused = false;
				audio.themeMusicReset();
				audio.themeMusicPlay();
			}
			// Resume Game
			else if (!gameOver && !viewingScores && !viewingRegistrationPage)
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
				collision = new Collision(HIGHSCOREFILE, TILEFILE, FONTFILE, COORDFILE);
				gameOver = false;
				gamePaused = false;
				audio.themeMusicReset();
				audio.themeMusicPlay();
			}
			break;
		}
		case 2: {
			// View Highscore
			if (!viewingRegistrationPage)
			{
				viewingScores = true;
				importHighScores(HIGHSCOREFILE, 3);
				loadMainMenu();
			}
			break;
		}
		case 3: {
			// Back / Quit game
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
		int enemiesKilled = 0;
		fromFile >> nrOfScores;
		
		for (int i = 0; i < NrOfScoresToView; i++)
		{
			fromFile >> name;
			fromFile >> time;
			fromFile.ignore();
			fromFile >> coins;
			fromFile.ignore();
			fromFile >> enemiesKilled;
			fromFile.ignore();
			containerString = to_string(i + 1) + ". Name: " + name + " Coins: " + to_string(coins) + " time: " + to_string(time) + " Enemies: " + to_string(enemiesKilled);
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
	if (event.type == Event::TextEntered)
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
		else if (event.text.unicode == Keyboard::Return)
		{
			collision->saveMarioStats(HIGHSCOREFILE, containerString);
		}
	}
}
