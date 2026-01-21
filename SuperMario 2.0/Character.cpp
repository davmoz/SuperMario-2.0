#include "Character.h"
#include <iostream>


Character::Character(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight)
{
	this->velocity = velocity;
	this->gravity = gravity;
	this->jumpHeight = jumpheight;
	this->tilePosition = tilePositionInFile;
	isJumping = false;

	if (!texture.loadFromFile(TileLocation))
		std::cerr << "Error: Failed to load texture from " << TileLocation << std::endl;
	appearence.setTexture(texture);
	appearence.setPosition(position);
	appearence.setTextureRect(tilePositionInFile);
	appearence.scale(Vector2f(2, 2));
	appearence.setOrigin(8, 8);
}

Character::Character()
{

}

Character::~Character()
{

}

void Character::moveLeft(bool updateFacingDirection)
{
	appearence.move(-velocity.x, 0.0f);
	if (updateFacingDirection)
		isMovingRight = false;
}

void Character::moveRight(bool updateFacingDirection)
{
	appearence.move(velocity.x, 0.0f);
	if (updateFacingDirection)
		isMovingRight = true;
}

void Character::jump()
{
	if (!isJumping)
	{
		velocity.y = -jumpHeight;
		isJumping = true;
	}
}

void Character::doubleVelocityX(const bool isBoosted)
{
	if (isBoosted)
	{
		velocity.x += 2.0f;
	}
	else if(!isBoosted)
	{
		velocity.x -= 2.0f;
	}
}

void Character::updateCharacter(const bool topCollision, const bool botCollision)
{

	if (topCollision)
	{
		velocity.y = 0.0f;
	}
	if (!botCollision || velocity.y < 0.0f)
	{
		velocity.y += gravity;
		
		appearence.move(0.0f, velocity.y);
		position = appearence.getPosition();
	}
	else if (botCollision)
	{
		isJumping = false;
		velocity.y = 0.0f;
		appearence.setPosition(appearence.getPosition().x, appearence.getPosition().y - gravity);
		position = appearence.getPosition();
	}
}

void Character::updateTexture(int nrOfTilesToView)
{
	float leftRectPos = appearence.getTextureRect().left;
	if (clock.getElapsedTime().asSeconds() > 0.09f)
	{
		if (isMovingRight)
		{
			if (leftRectPos > nrOfTilesToView * tilePosition.width)
			{
				appearence.setTextureRect(tilePosition);
				appearence.setScale(2, 2);
			}
			else
			{
				appearence.setTextureRect(IntRect(leftRectPos + tilePosition.width, tilePosition.top, tilePosition.width, tilePosition.height));
				appearence.setScale(2, 2);
			}
		}
		else
		{
			if (leftRectPos > nrOfTilesToView * tilePosition.width)
			{
				appearence.setTextureRect(tilePosition);
				appearence.setScale(2 * (-1), 2);
			}
			else
			{
				appearence.setTextureRect(IntRect(leftRectPos + tilePosition.width, tilePosition.top, tilePosition.width, tilePosition.height));
				appearence.setScale(2 * (-1), 2);
			}
		}
		clock.restart();
	}
}



string Character::collidesWithChar(const Character & otherChar)
{
	string collided = "";
	if (appearence.getGlobalBounds().intersects(otherChar.appearence.getGlobalBounds()))
	{
		int thisX = appearence.getPosition().x;
		int thisY = appearence.getPosition().y;
		int otherX = otherChar.appearence.getPosition().x;
		int otherY = otherChar.appearence.getPosition().y;

		if (thisX >= otherX - 16 && thisX <= otherX + 16 && thisY + 16 >= otherY - 16)
		{
			collided = "BOTTOM";
		}
		else if (thisX - 16 >= otherX && thisX - 16 <= otherX + 16 && thisY >= otherY)
		{
			collided = "LEFT";
		}
		else if (thisX + 16 >= otherX - 16 && thisX + 16 <= otherX && thisY >= otherY)
		{
			collided = "RIGHT";
		}
	}
	return collided;
}

Sprite Character::getSprite() const
{
	return appearence;
}

Vector2f Character::getPosition() const
{
	return position;
}

void Character::drawCharacter(RenderWindow * window)
{
	window->draw(appearence);
}
