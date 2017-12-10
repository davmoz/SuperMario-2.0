#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
using namespace sf;
class Mario : public Character
{
private:
	Texture texture;
public:
	Mario();
	~Mario();
	void setXPosition(const float x);
	void setYPosition(const float y);
	int getXPosition() const;
	int getYPosition() const;
	void jump();
};

