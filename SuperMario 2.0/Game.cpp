#include "Game.h"
#include <iostream>

Game::Game()
{
}


Game::~Game()
{
}

void Game::runGame(RenderWindow *window)
{       
	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->collision.MarioMoveRight();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->collision.MarioMoveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//this->collision.getMario().jump();
		}
		window->clear(/*sf::Color(0, 150, 255)*/);
		draw(window);
		window->display();
	}
}

void Game::draw(RenderWindow * window)
{
	window->draw(collision.getMap());
	window->draw(collision.getMarioSprite());
	window->draw(collision.getRect());
}
