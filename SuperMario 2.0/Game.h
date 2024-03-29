#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Collision.h"
#include "Audio.h"
using namespace sf;
const int nrOfMenuOptions = 4;
class Game
{
private:
	Audio audio;
	Event event;
	RenderWindow *window;
	Collision *collision;

	bool gamePaused;
	bool gameOver;
	bool viewingScores;
	bool viewingRegistrationPage;

	Font menuFont;
	int selectedMenu;
	Text menu[nrOfMenuOptions];
	string menuOptions[nrOfMenuOptions] = { "Resume", "Restart", "Highscore", "Quit" };
	string containerString;

public:
	Game(RenderWindow *window);
	Game();
	~Game();
	const string HIGHSCOREFILE = "Score/scores.txt";
	const string TILEFILE = "Tiles/main.png";
	const string FONTFILE = "Fonts/Super Mario Bros.ttf";
	const string COORDFILE = "Coords.txt";

	
	void runGame();
	void update();
	void loadMainMenu();
	void drawMenu();
	void handleMenuInput();
	void importHighScores(const string fileLocation, int NrOfScoresToView);
	void registerPlayerName();
};