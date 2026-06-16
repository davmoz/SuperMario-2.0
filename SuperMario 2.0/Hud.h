#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Mario.h" // PlayerStats

// The in-game heads-up display. Drawn in screen space (the window's default
// view) so it stays fixed while the level scrolls underneath it.
class Hud
{
private:
	sf::Font font;
	sf::Text levelText;
	sf::Text livesText;
	sf::Text scoreText;
	sf::Text coinsText;
	sf::Text timeText;
	sf::Text enemiesText;

public:
	Hud() = default;
	void load(const std::string &fontFileLocation); // call once before draw()
	void draw(sf::RenderWindow *window, const PlayerStats &stats, const std::string &levelName, int lives);
};
