#include "Enemy.h"


Enemy::Enemy(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const bool canFly) : Character(TileLocation, tilePositionInFile, position, velocity)
{
	this->canFly = canFly;
}

Enemy::Enemy() : Character()
{

}

void Enemy::fly(float elapsedTime)
{
	if (canFly) 
	{
		if (elapsedTime > 0.9f)
		{
			jump();
		}
	}
}


Enemy::~Enemy()
{

}