#include "Collision.h"


Collision::Collision()
{
	this->mario = new Mario("Ground.png", IntRect(0, 32, 16, 16));
	this->map = new Map(500, 16, 16.0f, 32.0f);
}

Collision::~Collision()
{
	delete this->mario;
	delete this->map;
}

void Collision::MarioMoveLeft()
{
	this->mario->moveLeft();
}

void Collision::MarioMoveRight()
{
	this->mario->moveRight();
}

Sprite Collision::getMarioSprite() const
{
	return this->mario->getSprite();
}

void Collision::animateMario(float &elapsedTime, const int direction)
{
	this->mario->updateTexture(elapsedTime, direction);
}

RectangleShape Collision::getRect() const
{
	return this->mario->getRectShape();
}

void Collision::moveViewRight()
{
	this->map->moveViewRight();
}

void Collision::moveViewLeft()
{
	this->map->moveViewLeft();
}

void Collision::setBackgroundPos(const float x, const float y)
{
	this->map->setBackgroundPos(x, y);
}

Map Collision::getMap() const
{
	return *this->map;
}
