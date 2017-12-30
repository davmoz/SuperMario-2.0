#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream> // For testing
#include <string>
using namespace std;
using namespace sf;
class Character
{
private:
	Texture texture;
	Sprite appearence;
	float xVelocity;
	float yVelocity;
	bool isMovingRight;
	bool isJumping;
	bool healthState;
public:
	Character(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const float xVelocity);
	Character();
	virtual ~Character();

	const float gravity = 0.8f;
	const float jumpHeight = 20.0f;
	const float groundHeight = 550.0f;

	void moveLeft(bool trulyMoving = true);
	void moveRight(bool trulyMoving = true);
	void jump();
	void changeVelocityX(const bool isBoosted);
	void updateCharacter(const bool topCollision, const bool botCollision);
	void updateTexture(float &elapsedTime, const int tileCoordX, const int tileCoordY, const int nrOfTilesToView, const int tileSize);
	void autoMove(const bool collidedWithRight, const bool collidedWithLeft);
	string collidesWithChar(const Character & otherChar);
	Sprite getSprite() const;
	void kill();
	void drawCharacter(RenderWindow * window);
};