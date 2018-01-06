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
	Vector2f position;
	Vector2f velocity;
	bool isMovingRight;
	bool isJumping;
	float gravity;
	float jumpHeight;
public:
	Character(const string TileLocation, const IntRect tilePositionInFile, Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight);
	Character();
	virtual ~Character();

	void moveLeft(bool trulyMoving = true);
	void moveRight(bool trulyMoving = true);
	void jump();
	void doubleVelocityX(const bool isBoosted);
	void updateCharacter(const bool topCollision, const bool botCollision);
	void updateTexture(float &elapsedTime, const int tileCoordX, const int tileCoordY, const int nrOfTilesToView, const int tileSize);
	void autoMove(const bool collidedWithRight, const bool collidedWithLeft);
	string collidesWithChar(const Character & otherChar);
	Sprite getSprite() const;
	Vector2f getPosition() const;
	void drawCharacter(RenderWindow * window);
};