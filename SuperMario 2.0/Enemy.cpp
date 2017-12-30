#include "Enemy.h"


Enemy::Enemy(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const float xVelocity) : Character(TileLocation, tilePositionInFile, position, xVelocity)
{

}

Enemy::Enemy() : Character()
{

}


Enemy::~Enemy()
{

}

void Enemy::moveEnemy()
{
	this->moveRight();
}
