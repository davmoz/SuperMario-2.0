#include "Enemy.h"


Enemy::Enemy(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const bool canFly, const float gravity, const float jumpheight) 
	: Character(TileLocation, tilePositionInFile, position, velocity, gravity, jumpheight)
{
	this->canFly = canFly;
	collidedWithLeft = true;
	collidedWithRight = false;
}

Enemy::Enemy() : Character()
{

}

void Enemy::fly()
{
	if (canFly) 
	{
		if (rand() % 101 > 99)
		{
			jump();
		}
	}
}

void Enemy::move(const bool collidedWithRight, const bool collidedWithLeft)
{
	if (collidedWithRight)
	{
		this->collidedWithRight = true;
		this->collidedWithLeft = false;
	}
	else if (collidedWithLeft)
	{
		this->collidedWithRight = false;
		this->collidedWithLeft = true;
	}
	if (this->collidedWithRight)
	{
		moveLeft(false);
	}
	else if (this->collidedWithLeft)
	{
		moveRight(false);
	}
}


Enemy::~Enemy()
{

}