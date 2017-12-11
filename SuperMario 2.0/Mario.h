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
	void moveLeft();
	void moveRight();
	void jump();
};

