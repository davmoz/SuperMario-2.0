#include "Character.h"


Character::Character(const string TileLocation, const IntRect tilePositionInFile)
{
	

	this->texture.loadFromFile(TileLocation);
	this->appearence.setTexture(texture);
	this->appearence.setOrigin(8, 8);
	this->appearence.setPosition(sf::Vector2f(250, 500));
	this->appearence.setTextureRect(tilePositionInFile);
	this->appearence.scale(Vector2f(2, 2));

	this->boundry.setSize(sf::Vector2f(30, 30));
	this->boundry.setPosition(sf::Vector2f(250, 500));
	this->boundry.setFillColor(sf::Color::Transparent);
	this->boundry.setOutlineThickness(1);
	this->boundry.setOutlineColor(sf::Color(250, 150, 100));
	this->boundry.setOrigin(8, 8);

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

RectangleShape Character::getRectShape() const
{
	return this->boundry;
}

void Character::updateTexture(float &elapsedTime, const int direction)
{
	float leftRectPos = this->appearence.getTextureRect().left;
	if (elapsedTime > 0.09f)
	{
		if (leftRectPos > 48.0f)
		{
			this->appearence.setTextureRect(IntRect(0, 32, 16, 16));
			this->appearence.setScale(direction * 2, 2);
		}
		else
		{
			this->appearence.setTextureRect(IntRect(leftRectPos + 16, 32, 16, 16));
			this->appearence.setScale(direction * 2, 2);
		}
		elapsedTime = 0;
	}
}
