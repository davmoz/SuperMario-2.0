#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// The kinds of collectible that can sit in a level.
enum class LootType
{
	Coin,         // adds to the coin count
	SpeedShroom,  // temporary speed boost
	GrowMushroom, // makes Mario big (absorbs one hit)
	Star          // temporary invincibility
};

class Loot
{
private:
	sf::Sprite appearence;
	LootType type;

public:
	Loot(const sf::Texture &texture, sf::Vector2f position, LootType type);
	~Loot();
	sf::Sprite getLootSprite() const;
	LootType getType() const;
};
