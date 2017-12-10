#include "Collision.h"


Collision::Collision()
{
	this->mario = new Mario;
	this->map = new Map(30, 16, 16.0f, 32.0f);
}


Collision::~Collision()
{
	delete this->mario;
	delete this->map;
}

Mario& Collision::getMario() const
{
	return *this->mario;
}

Map & Collision::getMap() const
{
	return *this->map;
}
