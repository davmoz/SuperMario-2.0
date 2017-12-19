#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream> // För testing
#include <string>
using namespace std;
using namespace sf;
class Character
{
private:
	float xPosition;
	float yPosition;
	float xVelocity;
	float yVelocity;
	float xAcceleration;
	float yAcceleration;
	float gravity;
	bool isJumping;
	int healthPoints;
	bool healthState;
	Texture texture;
	Sprite appearence;
public:
	Character(const string TileLocation, const IntRect tilePositionInFile);
	virtual ~Character();
	void moveLeft();
	void moveRight();
	void jump();
	void updateCharacter();
	Sprite getSprite() const;
	virtual void updateTexture(float &elapsedTime, const int direction) = 0;
	void setTexture(const IntRect tilePositionInFile, const int direction);
};