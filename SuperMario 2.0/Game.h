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
	// Collision Handler
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
	virtual ~Game();
	void runGame(RenderWindow *window, Clock *clock);
	void update(float &totaltime);
	void loadMenu(RenderWindow *window);
	void draw(RenderWindow *window);
	void drawMenu(RenderWindow *window);
	void handleMenuInput(RenderWindow * window);
	void importHighScores(const string fileLocation, int NrOfScoresToView);
	void registerPlayerName();
};