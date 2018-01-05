#include "Character.h"


Character::Character(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity)
{
	this->velocity = velocity;
	isJumping = false;

	texture.loadFromFile(TileLocation);
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

void Character::moveLeft(bool trulyMoving)
{
	appearence.move(-velocity.x, 0.0f);
	isMovingRight = false;
	if (trulyMoving)
	{
		isMovingRight = false;
	}
	else
	{
		isMovingRight = true;
	}
}

void Character::moveRight(bool trulyMoving)
{
	appearence.move(velocity.x, 0.0f);
	isMovingRight = true;
	if (trulyMoving)
	{
		isMovingRight = true;
	}
	else
	{
		isMovingRight = false;
	}
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
		//appearence.move(0.0f, velocity.y - gravity);
		isJumping = false;
		velocity.y = 0.0f;
		appearence.setPosition(appearence.getPosition().x, appearence.getPosition().y - gravity);
		position = appearence.getPosition();
	}
}

void Character::updateTexture(float & elapsedTime, const int tileCoordX, const int tileCoordY, const int nrOfTilesToView, const int tileSize)
{
	float leftRectPos = appearence.getTextureRect().left;
	if (elapsedTime > 0.09f)
	{
		if (isMovingRight)
		{
			if (leftRectPos > nrOfTilesToView * tileSize)
			{
				appearence.setTextureRect(IntRect(tileCoordX, tileCoordY, tileSize, tileSize));
				appearence.setScale(2, 2);
			}
			else
			{
				appearence.setTextureRect(IntRect(leftRectPos + tileSize, tileCoordY, tileSize, tileSize));
				appearence.setScale(2, 2);
			}
		}
		else
		{
			if (leftRectPos > nrOfTilesToView * tileSize)
			{
				appearence.setTextureRect(IntRect(tileCoordX, tileCoordY, tileSize, tileSize));
				appearence.setScale(2 * (-1), 2);
			}
			else
			{
				appearence.setTextureRect(IntRect(leftRectPos + tileSize, tileCoordY, tileSize, tileSize));
				appearence.setScale(2 * (-1), 2);
			}
		}
		
		elapsedTime = 0;
	}
}

void Character::autoMove(const bool collidedWithRight, const bool collidedWithLeft)
{
	if (collidedWithRight)
	{
		velocity.x *= -1;
	}
	else if (collidedWithLeft)
	{
		velocity.x *= -1;
	}
	appearence.move(velocity);
}

string Character::collidesWithChar(const Character & otherChar)
{
	if (&otherChar != nullptr)
	{
		string collided = "";
		if (appearence.getGlobalBounds().intersects(otherChar.appearence.getGlobalBounds()))
		{
			int thisX = appearence.getPosition().x;
			int thisY = appearence.getPosition().y;
			int otherX = otherChar.appearence.getPosition().x;
			int otherY = otherChar.appearence.getPosition().y;

			if (thisX >= otherX - 16 && thisX <= otherX + 16 && thisY + 16 >= otherY - 16/* && thisY + 16 <= otherY - 16*/)
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
}

Sprite Character::getSprite() const
{
	if (this != nullptr)
	{
		return appearence;
	}
}

Vector2f Character::getPosition() const
{
	return position;
}

void Character::drawCharacter(RenderWindow * window)
{
	window->draw(appearence);
}
