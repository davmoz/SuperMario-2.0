#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
using namespace std;
using namespace sf;
class Character
{
private:
	Texture texture;
	IntRect tilePosition;
	Sprite appearence;
	Vector2f position;
	Vector2f velocity;
	bool isMovingRight;
	bool isJumping;
	float gravity;
	float jumpHeight;
	Clock clock;

public:
	Character(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const float gravity, const float jumpheight);
	Character();
	virtual ~Character();

	void moveLeft(bool trulyMoving = true);
	void moveRight(bool trulyMoving = true);
	void jump();
	void doubleVelocityX(const bool isBoosted);
	void updateCharacter(const bool topCollision, const bool botCollision);
	void updateTexture(int nrOfTilesToView);
	
	string collidesWithChar(const Character & otherChar);
	Sprite getSprite() const;
	Vector2f getPosition() const;
	void drawCharacter(RenderWindow * window);
};