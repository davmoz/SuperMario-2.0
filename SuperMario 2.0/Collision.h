#pragma once
#include <SFML/Graphics.hpp>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
using namespace sf;
class Collision
{
private:
	Mario *mario;
	Map *map;
public:
	Collision();
	virtual ~Collision();
	Mario& getMario() const;
	Map& getMap() const;
};

