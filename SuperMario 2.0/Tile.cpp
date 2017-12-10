#include "Tile.h"


Tile::Tile(const float x, const float y)
{
	this->x = x;
	this->y = y;
}


Tile::~Tile()
{
}

int Tile::getX() const
{
	return this->x;
}

int Tile::getY() const
{
	return this->y;
}

void Tile::setX(const float x)
{
	this->x = x;
}

void Tile::setY(const float y)
{
	this->y = y;
}
