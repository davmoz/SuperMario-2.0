#include "Game.h"
#include <iostream>

using namespace std;
using namespace sf;

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
	window->setFramerateLimit(90);
	audio.themeMusicPlay();
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			
			if (viewingRegistrationPage)
			{
				registerPlayerName();
			}
			else if (gamePaused)
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
	if (!viewingScores && !viewingRegistrationPage)
	{
		menuOptions[0] = gameOver ? "New Game" : "Resume";
		for (int i = 0; i < nrOfMenuOptions; i++)
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
		int nrOfScores = 0;
		string name;
		int time = 0;
		int coins = 0;
		int enemiesKilled = 0;
		if (!(fromFile >> nrOfScores) || nrOfScores < 0)
			nrOfScores = 0;

		// Show at most the available scores AND at most what fits on screen.
		int toShow = nrOfScores < NrOfScoresToView ? nrOfScores : NrOfScoresToView;
		int i = 0;
		for (; i < toShow; i++)
		{
			if (!(fromFile >> name >> time >> coins >> enemiesKilled))
				break; // file shorter than its header claimed
			containerString = to_string(i + 1) + ". " + name + "  $:" + to_string(coins) + "  Time:" + to_string(time) + "  Enemies:" + to_string(enemiesKilled);
			menu[i].setString(containerString);
		}
		// Clear any leftover slots so stale/garbage text is never shown.
		for (; i < NrOfScoresToView; i++)
			menu[i].setString(i == 0 ? "No scores yet" : "");
		menu[NrOfScoresToView].setString("Back");
	}
	fromFile.close();
}

void Game::registerPlayerName()
{
	// Text entry. event.text.unicode is a Unicode code point, NOT an
	// sf::Keyboard::Key scancode, so it must be compared against character
	// values (8 = backspace) and printable ASCII ranges.
	if (event.type == Event::TextEntered)
	{
		const sf::Uint32 c = event.text.unicode;
		if (c == 8) // backspace
		{
			if (!playerName.empty())
				playerName.pop_back();
		}
		else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		{
			if (playerName.size() < MAX_NAME_LENGTH)
				playerName += static_cast<char>(c);
		}
	}
	// Enter confirms. Detected via KeyPressed (reliable) rather than the
	// carriage-return character, which some platforms don't emit as text.
	else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
	{
		if (!playerName.empty())
		{
			collision->saveMarioStats(HIGHSCOREFILE, playerName);
			playerName.clear();
			viewingRegistrationPage = false;
			selectedMenu = 0; // hand control back to the game-over menu
			for (int i = 0; i < nrOfMenuOptions; i++)
				menu[i].setFillColor(Color::White);
			menu[0].setFillColor(Color::Red);
			return; // menu renders next frame
		}
	}

	// Render the registration screen.
	menu[0].setString("ENTER YOUR NAME");
	menu[1].setString(playerName.empty() ? "_" : playerName);
	menu[2].setString("");
	menu[3].setString("Press ENTER to save");
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setFillColor(i == 1 ? Color::Yellow : Color::White);
		menu[i].setPosition(window->getView().getCenter().x, window->getView().getCenter().y / 2.5f * (i + 1));
		menu[i].setOrigin(menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.0f,
			menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.0f);
	}
	window->clear();
	for (int i = 0; i < nrOfMenuOptions; i++)
		window->draw(menu[i]);
	window->display();
}
