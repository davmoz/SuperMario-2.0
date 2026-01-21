#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <ctime>
#include <string>

class Enemy : public Character
{
private:
	bool canFly;
	bool collidedWithLeft;
	bool collidedWithRight;

public:
	Enemy(const std::string TileLocation, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const sf::Vector2f velocity, const bool canFly, const float gravity, const float jumpheight);
	Enemy();
	~Enemy();
	void fly();
	void move(const bool collidedWithRight, const bool collidedWithLeft);
};
