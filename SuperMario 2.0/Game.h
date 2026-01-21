#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Collision.h"
#include "Audio.h"

const int nrOfMenuOptions = 4;

class Game
{
private:
	Audio audio;
	sf::Event event;
	sf::RenderWindow *window;
	Collision *collision;

	bool gamePaused;
	bool gameOver;
	bool viewingScores;
	bool viewingRegistrationPage;

	sf::Font menuFont;
	int selectedMenu;
	sf::Text menu[nrOfMenuOptions];
	std::string menuOptions[nrOfMenuOptions] = { "Resume", "Restart", "Highscore", "Quit" };
	std::string containerString;

public:
	Game(sf::RenderWindow *window);
	Game();
	~Game();
	const std::string HIGHSCOREFILE = "Score/scores.txt";
	const std::string TILEFILE = "Tiles/main.png";
	const std::string FONTFILE = "Fonts/Super Mario Bros.ttf";
	const std::string COORDFILE = "Coords.txt";

	void runGame();
	void update();
	void loadMainMenu();
	void drawMenu();
	void handleMenuInput();
	void importHighScores(const std::string fileLocation, int NrOfScoresToView);
	void registerPlayerName();
};
