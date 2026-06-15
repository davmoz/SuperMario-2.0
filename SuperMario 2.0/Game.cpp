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
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setFont(menuFont);
		menu[i].setString(menuOptions[i]);
	}
	menu[0].setFillColor(Color::Red);
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
		// Consume events; each state interprets them its own way.
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
			switch (state)
			{
			case GameState::Playing:      handlePlayingEvent(); break;
			case GameState::Registration: registerPlayerName();  break;
			default:                      handleMenuInput();      break; // any menu
			}
		}

		// Render exactly once per frame, driven by the current state.
		if (state == GameState::Playing)
		{
			update();
			collision->updateCharacter();
			collision->moveEnemy();
			collision->checkMarioLootCollision();
			if (collision->checkMarioHostileCollision())
			{
				audio.themeMusicPause();
				audio.deadMusicPlay();
				playerName.clear();
				state = GameState::Registration;
			}
			else if (collision->checkMarioFinishCollision())
			{
				audio.themeMusicPause();
				audio.finishMusicPlay();
				playerName.clear();
				state = GameState::Registration;
			}
			window->clear();
			collision->draw(window, false);
			window->display();
		}
		else if (state == GameState::Registration)
		{
			drawRegistration();
		}
		else
		{
			drawMenu();
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

void Game::handlePlayingEvent()
{
	if (event.type != Event::KeyPressed)
		return;
	if (event.key.code == Keyboard::Escape)
	{
		audio.themeMusicPause();
		enterMenu(GameState::PauseMenu);
	}
	else if (event.key.code == Keyboard::Space)
	{
		collision->jump();
		audio.jumpMusicPlay();
	}
}

void Game::resetLevel()
{
	delete collision;
	collision = new Collision(HIGHSCOREFILE, TILEFILE, FONTFILE, COORDFILE);
	audio.themeMusicReset();
	audio.themeMusicPlay();
	state = GameState::Playing;
}

// Switch to a menu state and (re)build its labels and selection highlight.
void Game::enterMenu(GameState menuState)
{
	state = menuState;
	selectedMenu = 0;
	menuOptions[0] = (menuState == GameState::GameOverMenu) ? "New Game" : "Resume";
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setString(menuOptions[i]);
		menu[i].setFillColor(Color::White);
	}
	menu[0].setFillColor(Color::Red);
}

void Game::positionMenu()
{
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setPosition(window->getView().getCenter().x,
			window->getView().getCenter().y / 2.5f * (i + 1));
		menu[i].setOrigin(menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.0f,
			menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.0f);
	}
}

void Game::drawMenu()
{
	positionMenu();
	window->clear();
	for (int i = 0; i < nrOfMenuOptions; i++)
		window->draw(menu[i]);
	window->display();
}

void Game::handleMenuInput()
{
	if (event.type != Event::KeyPressed)
		return;
	const Keyboard::Key key = event.key.code;

	// The high-score list only offers "Back".
	if (state == GameState::Highscores)
	{
		if (key == Keyboard::Return || key == Keyboard::Escape)
			enterMenu(highscoreReturnState);
		return;
	}

	// Escape resumes a paused game.
	if (key == Keyboard::Escape && state == GameState::PauseMenu)
	{
		audio.themeMusicPlay();
		state = GameState::Playing;
		return;
	}

	if (key == Keyboard::Up && selectedMenu > 0)
	{
		menu[selectedMenu].setFillColor(Color::White);
		selectedMenu--;
		menu[selectedMenu].setFillColor(Color::Red);
	}
	else if (key == Keyboard::Down && selectedMenu < nrOfMenuOptions - 1)
	{
		menu[selectedMenu].setFillColor(Color::White);
		selectedMenu++;
		menu[selectedMenu].setFillColor(Color::Red);
	}
	else if (key == Keyboard::Return)
	{
		switch (selectedMenu)
		{
		case 0: // Resume (pause) or New Game (game over)
			if (state == GameState::PauseMenu)
			{
				audio.themeMusicPlay();
				state = GameState::Playing;
			}
			else
				resetLevel();
			break;
		case 1: // Restart
			resetLevel();
			break;
		case 2: // View high scores
			highscoreReturnState = state;
			importHighScores(HIGHSCOREFILE, nrOfMenuOptions - 1);
			state = GameState::Highscores;
			selectedMenu = nrOfMenuOptions - 1; // highlight "Back"
			for (int i = 0; i < nrOfMenuOptions; i++)
				menu[i].setFillColor(Color::White);
			menu[selectedMenu].setFillColor(Color::Red);
			break;
		case 3: // Quit
			window->close();
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
			enterMenu(GameState::GameOverMenu);
		}
	}
}

void Game::drawRegistration()
{
	menu[0].setString("ENTER YOUR NAME");
	menu[1].setString(playerName.empty() ? "_" : playerName);
	menu[2].setString("");
	menu[3].setString("Press ENTER to save");
	for (int i = 0; i < nrOfMenuOptions; i++)
		menu[i].setFillColor(i == 1 ? Color::Yellow : Color::White);
	positionMenu();
	window->clear();
	for (int i = 0; i < nrOfMenuOptions; i++)
		window->draw(menu[i]);
	window->display();
}
