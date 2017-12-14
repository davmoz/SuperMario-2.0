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
	int healthPoints;
	bool healthState;
	Texture texture;
	Sprite appearence;
	RectangleShape boundry;
	
public:
	Character(const string TileLocation, const IntRect tilePositionInFile);
	virtual ~Character();
	void moveLeft();
	void moveRight();
	Sprite getSprite() const;
	RectangleShape getRectShape() const;
	void updateTexture(float &elapsedTime, const int direction);
};