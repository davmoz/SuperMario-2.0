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
			this->collision.moveViewRight();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->collision.MarioMoveLeft();
			this->collision.moveViewLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//this->collision.getMario().jump();
		}
		update();
		window->clear();
		draw(window);
		window->display();
	}
}

void Game::update()
{
	this->collision.setBackgroundPos(this->collision.getMarioSprite().getPosition().x - 250 , this->collision.getMarioSprite().getPosition().y - 550);
}

void Game::draw(RenderWindow * window)
{
	window->draw(collision.getMap());
	window->draw(collision.getMarioSprite());
	window->draw(collision.getRect());
}