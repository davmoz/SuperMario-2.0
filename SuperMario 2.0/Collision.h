#pragma once
#include <SFML/Graphics.hpp>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
using namespace sf;
class Collision
{
private:
	Mario *mario;
	Map *map;
public:
	Collision();
	virtual ~Collision();
	void MarioMoveLeft();
	void MarioMoveRight();
	Map getMap() const;
	void moveViewLeft();
	void moveViewRight();
	void jump() const;
	Sprite getMarioSprite() const;
	void setBackgroundPos(const float x, const float y);
	void animateMario(float &elapsedTime, const int direction);
	void updateCharacter();
};

