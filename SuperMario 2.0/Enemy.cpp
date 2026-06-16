#include "Enemy.h"
#include "Constants.h"

using namespace std;
using namespace sf;

Enemy::Enemy(const Texture &texture, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const bool canFly, const float gravity, const float jumpheight)
	: Character(texture, tilePositionInFile, position, velocity, gravity, jumpheight)
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
	// Hop on a fixed time interval so the behaviour doesn't change with the
	// frame rate (the old per-frame rand() made it FPS-dependent).
	if (canFly && flyClock.getElapsedTime().asSeconds() >= FLY_JUMP_INTERVAL)
	{
		jump();
		flyClock.restart();
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


bool Enemy::onStomped()
{
	return true; // an ordinary enemy dies in a single stomp
}

Enemy::~Enemy()
{

}