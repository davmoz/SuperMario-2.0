#pragma once
#include "Enemy.h"

// The end-of-game boss: a larger, tougher enemy that survives several stomps.
// It patrols like a ground enemy and only falls when its health is exhausted.
class Boss : public Enemy
{
private:
	int health;

public:
	Boss(const sf::Texture &texture, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const sf::Vector2f velocity, const float gravity, const int startingHealth);

	bool onStomped() override; // takes one hit; returns true only when defeated
	bool isBoss() const override { return true; }
	int getHealth() const { return health; }
};
