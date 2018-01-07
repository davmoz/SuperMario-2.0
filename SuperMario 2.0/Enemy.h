#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <ctime>
using namespace sf;
class Enemy : public Character
{
private:
	bool canFly;
	bool collidedWithLeft;
	bool collidedWithRight;
public:
	Enemy(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const bool canFly, const float gravity, const float jumpheight);
	Enemy();

	void fly();
	void move(const bool collidedWithRight, const bool collidedWithLeft);
	virtual ~Enemy();
};

