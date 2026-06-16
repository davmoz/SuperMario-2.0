#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <ctime>
#include <string>

class Enemy : public Character
{
private:
	bool canFly = false;
	bool collidedWithLeft = true;
	bool collidedWithRight = false;

public:
	Enemy(const sf::Texture &texture, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const sf::Vector2f velocity, const bool canFly, const float gravity, const float jumpheight);
	Enemy();
	virtual ~Enemy();
	void fly();
	void move(const bool collidedWithRight, const bool collidedWithLeft);

	// Called when Mario stomps this enemy. Returns true if the enemy is
	// defeated and should be removed; an ordinary enemy always dies in one hit.
	virtual bool onStomped();
	virtual bool isBoss() const { return false; }
};
