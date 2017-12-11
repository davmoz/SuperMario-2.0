#include "Mario.h"
#include <iostream>

Mario::Mario() : Character()
{
	this->texture.loadFromFile("Mario.png", sf::IntRect(20, 505, 20, 20));
	Sprite sprite = this->getSprite();
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 500));
	sprite.setScale(2, 2);
	this->setSprite(sprite);
}


Mario::~Mario()
{
}

void Mario::moveLeft()
{
	Character::moveLeft();
}

void Mario::moveRight()
{
	Character::moveRight();
}


void Mario::jump()
{

}
