#include "Character.h"


Character::Character(const string TileLocation, const IntRect tilePositionInFile)
{
	this->texture.loadFromFile(TileLocation, tilePositionInFile);
	this->appearence.scale(Vector2f(1, 1));
	this->appearence.setTexture(texture);
	
	this->appearence.setPosition(sf::Vector2f(250, 500));
	this->appearence.scale(Vector2f(2, 2));
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

void Character::moveLeft()
{
	this->xPosition = appearence.getPosition().x;
	this->boundry.setPosition(sf::Vector2f(this->xPosition - 2.5f, 500));
	this->appearence.setPosition(boundry.getPosition());
}

void Character::moveRight()
{
	this->xPosition = appearence.getPosition().x;
	this->boundry.setPosition(sf::Vector2f(this->xPosition + 2.5f, 500));
	this->appearence.setPosition(boundry.getPosition());
}

RectangleShape Character::getRect() const
{
	return this->boundry;
}