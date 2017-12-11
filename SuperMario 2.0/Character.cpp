#include "Character.h"


Character::Character()
{
	this->boundry.setSize(sf::Vector2f(30, 30));
	this->boundry.setPosition(sf::Vector2f(0, 500));
	this->boundry.setFillColor(sf::Color::Transparent);
	this->boundry.setOutlineThickness(1);
	this->boundry.setOutlineColor(sf::Color(250, 150, 100));
}


Character::~Character()
{
}

Sprite Character::getSprite() const
{
	return this->sprite;
}

void Character::moveRight()
{
	this->xPosition = sprite.getPosition().x;
	this->boundry.setPosition(sf::Vector2f(this->xPosition + 0.5, 500));
	this->sprite.setPosition(boundry.getPosition());
}

void Character::moveLeft()
{
	this->xPosition = sprite.getPosition().x;
	this->boundry.setPosition(sf::Vector2f(this->xPosition -0.5, 500));
	this->sprite.setPosition(boundry.getPosition());
}

void Character::setSprite(const Sprite sprite)
{
	this->sprite = sprite;
}

RectangleShape Character::getBoundry() const
{
	return this->boundry;
}