#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
using namespace sf;
class Game
{
private:
	Collision collision;
public:
	Game();
	virtual ~Game();
	void runGame(RenderWindow *window);
	void update();
	void draw(RenderWindow *window);

};