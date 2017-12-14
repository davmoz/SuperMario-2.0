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
	void runGame(RenderWindow *window, Clock *clock);
	void update(float &totaltime);
	void draw(RenderWindow *window);

};