#include "Character.h"


Character::Character(const string TileLocation, const IntRect tilePositionInFile)
{
	this->xPosition = 250.0f;
	this->yPosition = 520.0f;
	this->xVelocity = 2.5f;
	this->yVelocity = 0.0f;
	this->xAcceleration = 5.0f;
	this->yAcceleration = 15.0f;
	this->gravity = 0.5f;
	this->isJumping = false;

	this->texture.loadFromFile(TileLocation);
	this->appearence.setTexture(texture);
	this->appearence.setOrigin(8, 8);
	this->appearence.setPosition(Vector2f(xPosition, yPosition));
	this->appearence.setTextureRect(tilePositionInFile);
	this->appearence.scale(Vector2f(2, 2));

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
	this->appearence.move(-this->xVelocity, 0);
}

void Character::moveRight()
{
	this->xPosition = appearence.getPosition().x;
	this->appearence.move(this->xVelocity, 0);
}

void Character::jump()
{
	if (!this->isJumping)
	{
		this->yVelocity = -yAcceleration;
	}
	
}

void Character::updateCharacter()
{
	if (this->appearence.getPosition().y < 520.0f || this->yVelocity < 0)
	{
		this->yVelocity += this->gravity;
	}
	else
	{
		this->yVelocity = 0;
		this->appearence.setPosition(this->appearence.getPosition().x, 520.0f - this->appearence.getGlobalBounds().height);
	}
	if (this->appearence.getPosition().y + this->appearence.getGlobalBounds().height == 520.0f)
	{
		this->isJumping = false;
	}
	else
	{
		this->isJumping = true;
	}
	this->yPosition += this->yVelocity;
	this->appearence.setPosition(appearence.getPosition().x, this->yPosition);
	
}

void Character::setTexture(const IntRect tilePositionInFile, const int direction)
{
	this->appearence.setTextureRect(tilePositionInFile);
	this->appearence.setScale(direction * 2, 2);
}