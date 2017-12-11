#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Character
{
private:
	Sprite appearence;
	RectangleShape boundry;
	float xPosition;
	float yPosition;
	int healthPoints;
	bool healthState;
public:
	Character();
	~Character();
	Sprite getSprite() const;
	float getX() const;
	float getY() const;
	void moveLeft();
	void moveRight();
	RectangleShape getRect() const;
	void setSprite(const Sprite appearence);
};