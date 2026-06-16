#include "Character.h"
#include "Constants.h"
#include <iostream>

using namespace std;
using namespace sf;


Character::Character(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight)
{
	this->velocity = velocity;
	this->gravity = gravity;
	this->jumpHeight = jumpheight;
	this->tilePosition = tilePositionInFile;
	isJumping = false;
	isMovingRight = true;

	if (!texture.loadFromFile(TileLocation))
		std::cerr << "Error: Failed to load texture from " << TileLocation << std::endl;
	appearence.setTexture(texture);
	appearence.setPosition(position);
	appearence.setTextureRect(tilePositionInFile);
	appearence.setScale(scaleFactor, scaleFactor);
	appearence.setOrigin(TILE_TEXTURE_SIZE / 2.0f, TILE_TEXTURE_SIZE / 2.0f);
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

void Character::bounce()
{
	velocity.y = -jumpHeight * 0.6f;
	isJumping = true;
}

void Character::setBaseScale(float factor)
{
	scaleFactor = factor;
	appearence.setScale(scaleFactor, scaleFactor);
}

void Character::setAppearanceColor(Color color)
{
	appearence.setColor(color);
}

void Character::doubleVelocityX(const bool isBoosted)
{
	if (isBoosted)
	{
		velocity.x += BOOST_VELOCITY_INCREASE;
	}
	else if(!isBoosted)
	{
		velocity.x -= BOOST_VELOCITY_INCREASE;
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
	}
	else if (botCollision)
	{
		isJumping = false;
		velocity.y = 0.0f;
		appearence.setPosition(appearence.getPosition().x, appearence.getPosition().y - gravity);
	}
}

void Character::updateTexture(int nrOfTilesToView)
{
	float leftRectPos = appearence.getTextureRect().left;
	if (clock.getElapsedTime().asSeconds() > ANIMATION_INTERVAL)
	{
		if (isMovingRight)
		{
			if (leftRectPos > nrOfTilesToView * tilePosition.width)
			{
				appearence.setTextureRect(tilePosition);
				appearence.setScale(scaleFactor, scaleFactor);
			}
			else
			{
				appearence.setTextureRect(IntRect(leftRectPos + tilePosition.width, tilePosition.top, tilePosition.width, tilePosition.height));
				appearence.setScale(scaleFactor, scaleFactor);
			}
		}
		else
		{
			if (leftRectPos > nrOfTilesToView * tilePosition.width)
			{
				appearence.setTextureRect(tilePosition);
				appearence.setScale(-scaleFactor, scaleFactor);
			}
			else
			{
				appearence.setTextureRect(IntRect(leftRectPos + tilePosition.width, tilePosition.top, tilePosition.width, tilePosition.height));
				appearence.setScale(-scaleFactor, scaleFactor);
			}
		}
		clock.restart();
	}
}



string Character::collidesWithChar(const Character & otherChar)
{
	string collided = "";
	FloatRect thisBounds = appearence.getGlobalBounds();
	FloatRect otherBounds = otherChar.appearence.getGlobalBounds();
	if (thisBounds.intersects(otherBounds))
	{
		float thisCenterX = thisBounds.left + thisBounds.width / 2.0f;
		float thisCenterY = thisBounds.top + thisBounds.height / 2.0f;
		float otherCenterX = otherBounds.left + otherBounds.width / 2.0f;
		float otherCenterY = otherBounds.top + otherBounds.height / 2.0f;

		if (thisCenterY < otherCenterY)
		{
			// Above the other's mid-line: descending onto it is a stomp,
			// rising through it (e.g. bouncing off a boss) is harmless.
			if (velocity.y > 0.0f)
				collided = "BOTTOM";
		}
		else if (thisCenterX < otherCenterX)
		{
			collided = "RIGHT"; // deadly side contact on this character's right
		}
		else
		{
			collided = "LEFT";
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
	return appearence.getPosition();
}

void Character::drawCharacter(RenderWindow * window)
{
	window->draw(appearence);
}
