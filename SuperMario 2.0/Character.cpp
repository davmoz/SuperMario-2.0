#include "Character.h"


Character::Character()
{
	this->boundry.setSize(sf::Vector2f(30, 30));
	this->boundry.setPosition(sf::Vector2f(250, 500));
	this->boundry.setFillColor(sf::Color::Transparent);
	this->boundry.setOutlineThickness(1);
	this->boundry.setOutlineColor(sf::Color(250, 150, 100));
}


Character::~Character()
{
}

Sprite Character::getSprite() const
{
	return this->appearence;
}

float Character::getX() const
{
	return this->xPosition;
}

float Character::getY() const
{
	return this->yPosition;
}

void Character::moveLeft()
{
	this->xPosition = appearence.getPosition().x;
	this->boundry.setPosition(sf::Vector2f(this->xPosition - 0.5, 500));
	this->appearence.setPosition(boundry.getPosition());
}

void Character::moveRight()
{
	this->xPosition = appearence.getPosition().x;
	this->boundry.setPosition(sf::Vector2f(this->xPosition + 0.5, 500));
	this->appearence.setPosition(boundry.getPosition());
}

RectangleShape Character::getRect() const
{
	return this->boundry;
}

void Character::setSprite(const Sprite appearence)
{
	this->appearence = appearence;
}