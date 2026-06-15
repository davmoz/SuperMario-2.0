#include "Hud.h"
#include <iostream>

using namespace sf;
using namespace std;

void Hud::load(const string &fontFileLocation)
{
	if (!font.loadFromFile(fontFileLocation))
		std::cerr << "Error: Failed to load font from " << fontFileLocation << std::endl;
	for (Text *t : { &levelText, &coinsText, &timeText, &enemiesText })
	{
		t->setFont(font);
		t->setCharacterSize(22);
		t->setFillColor(Color::White);
		t->setOutlineColor(Color::Black);
		t->setOutlineThickness(2.0f);
	}
	levelText.setFillColor(Color(255, 210, 60));
}

void Hud::draw(RenderWindow *window, const PlayerStats &stats, const string &levelName)
{
	levelText.setString(levelName);
	coinsText.setString("$ " + to_string(stats.coins));
	timeText.setString("TIME " + to_string(stats.time));
	enemiesText.setString("ENEMIES " + to_string(stats.enemies));

	levelText.setPosition(14.0f, 8.0f);
	coinsText.setPosition(320.0f, 8.0f);
	timeText.setPosition(470.0f, 8.0f);
	enemiesText.setPosition(640.0f, 8.0f);

	// Render against the default view so the HUD ignores the level camera.
	const View previous = window->getView();
	window->setView(window->getDefaultView());
	window->draw(levelText);
	window->draw(coinsText);
	window->draw(timeText);
	window->draw(enemiesText);
	window->setView(previous);
}
