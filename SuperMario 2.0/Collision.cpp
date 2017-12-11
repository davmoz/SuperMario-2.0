#include "Collision.h"


Collision::Collision()
{
	this->mario = new Mario;
	this->map = Map(30, 16, 16.0f, 32.0f);
}

Collision::~Collision()
{
	delete this->mario;
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

RectangleShape Collision::getRect() const
{
	return this->mario->getRect();
}

Map Collision::getMap() const
{
	return this->map;
}
