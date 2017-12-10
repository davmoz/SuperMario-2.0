#include "Mario.h"
#include <iostream>

Mario::Mario() : Character()
{
	this->texture.loadFromFile("Mario.png", sf::IntRect(20, 505, 20, 20));
	Sprite sprite = this->getSprite();
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 535));
	sprite.setScale(2, 2);
	this->setSprite(sprite);
}


Mario::~Mario()
{
}

void Mario::setXPosition(const float x)
{
	this->setXPosition(x);
}

void Mario::setYPosition(const float y)
{
	this->setYPosition(y);
}

int Mario::getXPosition() const
{
	return this->getXPosition();
}

int Mario::getYPosition() const
{
	return this->getYPosition();
}

void Mario::jump()
{
	this->getSprite().setPosition(0, 200);
}
