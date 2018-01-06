#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
using namespace sf;
class Enemy : public Character
{
private:
	bool canFly;
public:
	Enemy(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const bool canFly, const float gravity, const float jumpheight);
	Enemy();

	void fly(float elapsedTime);

	virtual ~Enemy();
};

