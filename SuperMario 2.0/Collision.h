#pragma once
#include <SFML/Graphics.hpp>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
using namespace sf;
class Collision
{
private:
	Mario *mario = nullptr;
	Map *map;
public:
	Collision();
	virtual ~Collision();
	void MarioMoveLeft();
	void MarioMoveRight();
	Map getMap() const;
	Sprite getMarioSprite() const;
	RectangleShape getRect() const;
	void moveViewRight();
	void moveViewLeft();
	void setBackgroundPos(const float x, const float y);
};

