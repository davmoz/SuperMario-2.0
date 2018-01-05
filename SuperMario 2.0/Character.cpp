#include "Character.h"


Character::Character(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity)
{
	this->velocity = velocity;
	this->isJumping = false;
	this->healthState = true;

	this->texture.loadFromFile(TileLocation);
	this->appearence.setTexture(texture);
	this->appearence.setPosition(position);
	this->appearence.setTextureRect(tilePositionInFile);
	this->appearence.scale(Vector2f(2, 2));
	this->appearence.setOrigin(8, 8);
}

Character::Character()
{

}

Character::~Character()
{

}

void Character::moveLeft(bool trulyMoving)
{
	this->appearence.move(-this->velocity.x, 0.0f);
	this->isMovingRight = false;
	if (trulyMoving)
	{
		this->isMovingRight = false;
	}
	else
	{
		this->isMovingRight = true;
	}
}

void Character::moveRight(bool trulyMoving)
{
	this->appearence.move(this->velocity.x, 0.0f);
	this->isMovingRight = true;
	if (trulyMoving)
	{
		this->isMovingRight = true;
	}
	else
	{
		this->isMovingRight = false;
	}
}

void Character::jump()
{
	if (!this->isJumping)
	{
		this->velocity.y = -this->jumpHeight;
		isJumping = true;
	}
}

void Character::doubleVelocityX(const bool isBoosted)
{
	if (isBoosted)
	{
		this->velocity.x += 2.0f;
	}
	else if(!isBoosted)
	{
		this->velocity.x -= 2.0f;
	}
}

void Character::updateCharacter(const bool topCollision, const bool botCollision)
{

	if (topCollision)
	{
		this->velocity.y = 0.0f;
	}
	if (!botCollision || this->velocity.y < 0.0f)
	{
		this->velocity.y += gravity;
		
		this->appearence.move(0.0f, this->velocity.y);
		this->position = appearence.getPosition();
	}
	else if (botCollision)
	{
		//this->appearence.move(0.0f, this->velocity.y - gravity);
		this->isJumping = false;
		this->velocity.y = 0.0f;
		this->appearence.setPosition(this->appearence.getPosition().x, this->appearence.getPosition().y - gravity);
		this->position = appearence.getPosition();
	}
}

void Character::updateTexture(float & elapsedTime, const int tileCoordX, const int tileCoordY, const int nrOfTilesToView, const int tileSize)
{
	float leftRectPos = this->getSprite().getTextureRect().left;
	if (elapsedTime > 0.09f)
	{
		if (this->isMovingRight)
		{
			if (leftRectPos > nrOfTilesToView * tileSize)
			{
				this->appearence.setTextureRect(IntRect(tileCoordX, tileCoordY, tileSize, tileSize));
				this->appearence.setScale(2, 2);
			}
			else
			{
				this->appearence.setTextureRect(IntRect(leftRectPos + tileSize, tileCoordY, tileSize, tileSize));
				this->appearence.setScale(2, 2);
			}
		}
		else
		{
			if (leftRectPos > nrOfTilesToView * tileSize)
			{
				this->appearence.setTextureRect(IntRect(tileCoordX, tileCoordY, tileSize, tileSize));
				this->appearence.setScale(2 * (-1), 2);
			}
			else
			{
				this->appearence.setTextureRect(IntRect(leftRectPos + tileSize, tileCoordY, tileSize, tileSize));
				this->appearence.setScale(2 * (-1), 2);
			}
		}
		
		elapsedTime = 0;
	}
}

void Character::autoMove(const bool collidedWithRight, const bool collidedWithLeft)
{
	if (collidedWithRight)
	{
		this->velocity.x *= -1;
	}
	else if (collidedWithLeft)
	{
		this->velocity.x *= -1;
	}
	this->appearence.move(this->velocity);
}

string Character::collidesWithChar(const Character & otherChar)
{
	if (&otherChar != nullptr)
	{
		string collided = "";
		if (this->appearence.getGlobalBounds().intersects(otherChar.appearence.getGlobalBounds()))
		{
			int thisX = this->appearence.getPosition().x;
			int thisY = this->appearence.getPosition().y;
			int otherX = otherChar.appearence.getPosition().x;
			int otherY = otherChar.appearence.getPosition().y;

			if (thisX >= otherX - 16 && thisX <= otherX + 16 && thisY + 16 >= otherY - 16/* && thisY + 16 <= otherY - 16*/)
			{
				cout << "Collided from bottom" << endl;
				collided = "BOTTOM";
			}
			else if (thisX - 16 >= otherX && thisX - 16 <= otherX + 16 && thisY >= otherY)
			{
				cout << "Collided from LEFT" << endl;
				collided = "LEFT";
			}
			else if (thisX + 16 >= otherX - 16 && thisX + 16 <= otherX && thisY >= otherY)
			{
				cout << "collided from RIGHT" << endl;
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
		return this->appearence;
	}
}

Vector2f Character::getPosition() const
{
	return this->position;
}

void Character::kill()
{
	this->healthState = false;
}

void Character::drawCharacter(RenderWindow * window)
{
	window->draw(this->appearence);
}
