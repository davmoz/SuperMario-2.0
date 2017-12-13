#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Character
{
private:
	Sprite appearence;
	Texture texture;
	RectangleShape boundry;
	float xPosition;
	float yPosition;
	int healthPoints;
	bool healthState;
public:
	Character(const string TileLocation, const IntRect tilePositionInFile);
	virtual ~Character();
	Sprite getSprite() const;
	void moveLeft();
	void moveRight();
	RectangleShape getRect() const;
};