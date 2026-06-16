#include "Game.h"
#include <iostream>

using namespace std;
using namespace sf;

namespace
{
	// Draw one line of text horizontally centred at (cx, y) in the current view.
	void drawCenteredLine(RenderWindow *window, const Font &font, const string &str,
		unsigned int size, Color color, float cx, float y)
	{
		Text text(str, font, size);
		text.setFillColor(color);
		FloatRect b = text.getLocalBounds();
		text.setOrigin(b.left + b.width / 2.0f, b.top + b.height / 2.0f);
		text.setPosition(cx, y);
		window->draw(text);
	}
}

Game::Game(RenderWindow *window)
{
	this->window = window;
	collision = new Collision(TILEFILE, levelManager.currentFile());
	window->setTitle("Super Mario 2.0 - " + levelManager.currentName());
	hud.load(FONTFILE);
	if (!menuFont.loadFromFile(FONTFILE))
		std::cerr << "Error: Failed to load font from " << FONTFILE << std::endl;
	if (!titleFont.loadFromFile(TITLEFONTFILE))
		titleFont = menuFont; // fall back to the menu font if the title face is missing
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
			case GameState::Title:
			case GameState::Story:        handleIntroEvent();   break;
			case GameState::Playing:      handlePlayingEvent(); break;
			case GameState::Victory:
				if (event.type == Event::KeyPressed &&
					(event.key.code == Keyboard::Return || event.key.code == Keyboard::Space))
					state = GameState::Registration; // go record the winning run
				break;
			case GameState::Registration: registerPlayerName();  break;
			default:                      handleMenuInput();      break; // any menu
			}
		}

		// Render exactly once per frame, driven by the current state.
		if (state == GameState::Title)
		{
			drawTitle();
		}
		else if (state == GameState::Story)
		{
			drawStory();
		}
		else if (state == GameState::Playing)
		{
			update();
			collision->updateCharacter();
			collision->moveEnemy();
			collision->checkMarioLootCollision();
			if (collision->checkMarioHostileCollision())
			{
				audio.deadMusicPlay();
				lives--;
				if (lives > 0)
				{
					// Respawn: replay the current level, keeping the run totals.
					loadLevel(true);
					audio.themeMusicReset();
					audio.themeMusicPlay();
				}
				else
				{
					audio.themeMusicPause();
					playerName.clear();
					state = GameState::Registration;
				}
			}
			else if (collision->checkMarioFinishCollision())
			{
				if (levelManager.hasNext())
				{
					advanceLevel();
				}
				else
				{
					// Beat the final level: celebrate, then record the run.
					audio.themeMusicPause();
					audio.finishMusicPlay();
					finalStats = collision->getMarioStats();
					playerName.clear();
					state = GameState::Victory;
				}
			}
			window->clear();
			collision->draw(window);
			hud.draw(window, collision->getMarioStats(), levelManager.currentName(), lives);
			window->display();
		}
		else if (state == GameState::Victory)
		{
			drawVictory();
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

// Build the Collision for the level the LevelManager currently points at,
// optionally carrying the run totals forward from the level just finished.
void Game::loadLevel(bool carryStats)
{
	PlayerStats carried;
	if (carryStats)
		carried = collision->getMarioStats();
	delete collision;
	collision = new Collision(TILEFILE, levelManager.currentFile());
	if (carryStats)
		collision->applyMarioStats(carried);
	window->setTitle("Super Mario 2.0 - " + levelManager.currentName());
}

// New Game / Restart: start over from the first level.
void Game::resetLevel()
{
	lives = STARTING_LIVES;
	levelManager.reset();
	loadLevel(false);
	audio.themeMusicReset();
	audio.themeMusicPlay();
	state = GameState::Playing;
}

// Reached the finish flag of a non-final level: advance and keep playing.
void Game::advanceLevel()
{
	levelManager.advance();
	loadLevel(true);
	audio.finishMusicPlay();
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
	// Menus live in screen space, centred on the window's default view.
	const Vector2f center = window->getDefaultView().getCenter();
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		menu[i].setPosition(center.x, center.y / 2.5f * (i + 1));
		menu[i].setOrigin(menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.0f,
			menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.0f);
	}
}

void Game::drawMenu()
{
	window->clear();
	// Show the frozen level, dimmed, behind the pause menu.
	if (state == GameState::PauseMenu)
	{
		collision->draw(window);
		hud.draw(window, collision->getMarioStats(), levelManager.currentName(), lives);
		window->setView(window->getDefaultView());
		RectangleShape dim(window->getDefaultView().getSize());
		dim.setFillColor(Color(0, 0, 0, 150));
		window->draw(dim);
	}
	else
	{
		window->setView(window->getDefaultView());
	}
	positionMenu();
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
	window->setView(window->getDefaultView());
	positionMenu();
	window->clear(Color(20, 20, 40));
	for (int i = 0; i < nrOfMenuOptions; i++)
		window->draw(menu[i]);
	window->display();
}

// Enter/Space advances through the title and intro screens into the game.
void Game::handleIntroEvent()
{
	if (event.type != Event::KeyPressed)
		return;
	if (event.key.code == Keyboard::Return || event.key.code == Keyboard::Space)
	{
		if (state == GameState::Title)
			state = GameState::Story;
		else // Story
			state = GameState::Playing;
	}
}

void Game::drawTitle()
{
	window->setView(window->getDefaultView());
	const float cx = window->getDefaultView().getCenter().x;
	window->clear(Color(40, 70, 160)); // sky blue
	drawCenteredLine(window, titleFont, "SUPER MARIO", 64, Color::White, cx, 170);
	drawCenteredLine(window, titleFont, "2.0", 64, Color(255, 210, 60), cx, 250);
	drawCenteredLine(window, menuFont, "Press ENTER to start", 28, Color::White, cx, 380);
	drawCenteredLine(window, menuFont, "Arrows: Move    Space: Jump    Esc: Pause", 18,
		Color(200, 200, 200), cx, 430);
	window->display();
}

void Game::drawStory()
{
	window->setView(window->getDefaultView());
	const float cx = window->getDefaultView().getCenter().x;
	window->clear(Color(10, 10, 30)); // night
	const char *lines[] = {
		"The Star of the Mushroom Kingdom",
		"has been stolen by Bowser's army,",
		"its light scattered across three worlds.",
		"",
		"Run, jump and stomp every foe",
		"in your path to win it back!"
	};
	float y = 130;
	for (const char *line : lines)
	{
		drawCenteredLine(window, menuFont, line, 26, Color::White, cx, y);
		y += 48;
	}
	drawCenteredLine(window, menuFont, "Press ENTER to begin", 24, Color(255, 210, 60), cx, 470);
	window->display();
}

void Game::drawVictory()
{
	window->setView(window->getDefaultView());
	const float cx = window->getDefaultView().getCenter().x;
	window->clear(Color(20, 20, 60));
	drawCenteredLine(window, titleFont, "YOU WIN!", 56, Color(255, 210, 60), cx, 150);
	drawCenteredLine(window, menuFont, "The Star of the Mushroom Kingdom is safe.", 24, Color::White, cx, 240);
	drawCenteredLine(window, menuFont, "Coins  " + to_string(finalStats.coins), 26, Color::White, cx, 310);
	drawCenteredLine(window, menuFont, "Enemies defeated  " + to_string(finalStats.enemies), 26, Color::White, cx, 350);
	drawCenteredLine(window, menuFont, "Time  " + to_string(finalStats.time), 26, Color::White, cx, 390);
	drawCenteredLine(window, menuFont, "Press ENTER to record your score", 22, Color(255, 210, 60), cx, 470);
	window->display();
}
