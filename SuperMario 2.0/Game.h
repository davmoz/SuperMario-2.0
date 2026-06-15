#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Collision.h"
#include "Audio.h"

const int nrOfMenuOptions = 4;
const std::size_t MAX_NAME_LENGTH = 12;

// The single source of truth for what the game is currently doing. Replaces the
// old quartet of overlapping booleans, so each screen is one explicit state.
enum class GameState
{
	Playing,       // active gameplay
	PauseMenu,     // paused mid-level
	GameOverMenu,  // after a death or finish, name already recorded
	Highscores,    // viewing the high-score list
	Registration   // typing a name for the high-score table
};

class Game
{
private:
	Audio audio;
	sf::Event event;
	sf::RenderWindow *window = nullptr;
	Collision *collision = nullptr;

	GameState state = GameState::Playing;
	GameState highscoreReturnState = GameState::PauseMenu; // where "Back" returns

	sf::Font menuFont;
	int selectedMenu = 0;
	sf::Text menu[nrOfMenuOptions];
	std::string menuOptions[nrOfMenuOptions] = { "Resume", "Restart", "Highscore", "Quit" };
	std::string containerString; // scratch buffer for high-score formatting
	std::string playerName;      // name being typed on the registration screen

public:
	Game(sf::RenderWindow *window);
	Game();
	~Game();
	const std::string HIGHSCOREFILE = "Score/scores.txt";
	const std::string TILEFILE = "Tiles/main.png";
	const std::string FONTFILE = "Fonts/gomarice_no_continue.ttf";
	const std::string COORDFILE = "Coords.txt";

	void runGame();
	void update();
	void resetLevel();
	void enterMenu(GameState menuState);
	void positionMenu();
	void drawMenu();
	void handleMenuInput();
	void handlePlayingEvent();
	void drawRegistration();
	void importHighScores(const std::string fileLocation, int NrOfScoresToView);
	void registerPlayerName();
};
