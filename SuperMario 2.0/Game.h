#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
using namespace sf;
class Game
{
private:
	RenderWindow *window;
	Collision collision;
public:
	Game();
	virtual ~Game();
	void runGame(RenderWindow *window);
	void draw(RenderWindow *window);

};

