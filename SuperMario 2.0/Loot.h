#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Loot
{
private:
	sf::Texture texture;
	sf::Sprite appearence;
	bool coin;

public:
	Loot(const std::string TileLocation, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const bool isCoin);
	~Loot();
	sf::Sprite getLootSprite() const;
	bool isCoin() const;
};
