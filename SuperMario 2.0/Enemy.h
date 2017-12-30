#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
using namespace sf;
class Enemy : public Character
{
private:
	bool canFly;
public:
	Enemy(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const float xVelocity);
	Enemy();
	virtual ~Enemy();
	void moveEnemy();
};

