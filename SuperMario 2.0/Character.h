#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Character
{
private:
	Sprite sprite;
	RectangleShape boundry;
	float xPosition;
	float yPosition;
	int healthPoints;
	bool healthState;
public:
	Character();
	~Character();
	Sprite getSprite() const;
	void moveRight();
	void moveLeft();
	void setSprite(const Sprite sprite);
	virtual int getXPosition() const = 0;
	virtual int getYPosition() const = 0;
	virtual void setXPosition(const float x) = 0;
	virtual void setYPosition(const float y) = 0;
	virtual RectangleShape getBoundry() const;
};