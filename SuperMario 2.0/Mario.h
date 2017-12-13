#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
using namespace sf;
class Mario : public Character
{
private:
	
public:
	Mario(const string TileLocation, const IntRect tilePositionInFile);
	virtual ~Mario();
	void jump();
};

