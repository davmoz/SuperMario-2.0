#include "Game.h"
#include <iostream>

Game::Game(RenderWindow *window)
{
	this->collision = new Collision;
	
	this->menuFont.loadFromFile("Fonts/Chunkfive.otf");
	this->gamePaused = false;
	this->gameOver = false;
	this->selectedMenu = 0;
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		this->menu[i].setFont(this->menuFont);
		this->menu[i].setString(menuOptions[i]);
		this->menu[i].setPosition(Vector2f(window->getView().getCenter().x, window->getView().getCenter().y / 2.5f * (i + 1)));
		this->menu[i].setOrigin(menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.0f, menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.0f);
	}
	this->menu[0].setFillColor(Color(Color::Red));
}

Game::Game()
{
}

Game::~Game()
{
	delete this->collision;
}

void Game::runGame(RenderWindow *window, Clock *clock)
{
	this->audio.themeMusicPlay();
	float totaltime = 0.0f;

	while (window->isOpen())
	{
		totaltime += clock->restart().asSeconds(); 
		
		Event event;
		
		window->setFramerateLimit(90);
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
			if (Keyboard::isKeyPressed(Keyboard::Escape) && event.key.code == Keyboard::Escape)
			{
				if (!gamePaused)
				{
					this->audio.themeMusicPause();
					this->gamePaused = true;
				}
				else
				{
					this->audio.themeMusicPlay();
					this->gamePaused = false;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space) && event.key.code == Keyboard::Space)
			{
				this->collision->jump();
				this->audio.jumpMusicPlay();
			}
		}
		if (!this->gamePaused)	
		{
			this->update(totaltime);
			this->collision->updateCharacter(totaltime);
			this->collision->moveEnemy();
			if (this->collision->checkMarioEnemyCollision())
			{
				this->audio.themeMusicPause();
				this->audio.deadMusicPlay();
				this->gameOver = true;
				this->gamePaused = true;
			}
			this->collision->checkMarioCoinCollision();
			this->collision->checkMarioShroomCollision();
			window->clear();
			this->draw(window);
			window->display();
		}
		else
		{
			window->setFramerateLimit(10);
			window->clear();
			this->draw(window);
			window->display();
		}
	}
}

void Game::update(float &totaltime)
{
	
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->collision->MarioMoveRight();
		this->collision->moveViewRight();
		this->collision->updateCharTexture(totaltime, 0, 32, 3, 16);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->collision->MarioMoveLeft();
		this->collision->moveViewLeft();
		this->collision->updateCharTexture(totaltime, 0, 32, 3, 16);
	}
}

void Game::loadMenu(RenderWindow *window)
{
	if (this->gameOver)
	{
		this->menuOptions[0] = "New Game";
		this->menu[0].setString(menuOptions[0]);
	}
	else
	{
		this->menuOptions[0] = "Resume";
		this->menu[0].setString(menuOptions[0]);
	}
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		this->menu[i].setPosition(Vector2f(window->getView().getCenter().x, window->getView().getCenter().y / 2.5f * (i + 1)));
		this->menu[i].setOrigin(menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.0f, menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.0f);
	}
}

void Game::draw(RenderWindow * window)
{
	if (!this->gamePaused)
	{
		this->collision->draw(window, this->gamePaused);
	}
	else
	{
		this->drawMenu(window);
		handleMenuInput(window);
	}
}

void Game::drawMenu(RenderWindow * window)
{
	this->loadMenu(window);
	for (int i = 0; i < nrOfMenuOptions; i++)
	{
		window->draw(menu[i]);
	}
}

void Game::handleMenuInput(RenderWindow * window)
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (this->selectedMenu - 1 >= 0)
		{
			this->menu[this->selectedMenu].setFillColor(Color(Color::White));
			this->selectedMenu--;
			this->menu[this->selectedMenu].setFillColor(Color(Color::Red));
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (this->selectedMenu + 1 < nrOfMenuOptions)
		{
			this->menu[this->selectedMenu].setFillColor(Color(Color::White));
			this->selectedMenu++;
			this->menu[this->selectedMenu].setFillColor(Color(Color::Red));
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		switch (this->selectedMenu)
		{
		case 0: {
			if (this->gameOver)
			{
				delete this->collision;
				this->collision = new Collision;
				this->gameOver = false;
				this->gamePaused = false;
				this->audio.themeMusicPause();
				this->audio.themeMusicReset();
			}
			else
			{
				this->audio.themeMusicPlay();
				this->gamePaused = false;
			}
			break;
		}
		case 1: {
			delete this->collision;
			this->collision = new Collision;
			this->gameOver = false;
			this->gamePaused = false;
			this->audio.themeMusicPlay();
			break;
		}
		case 2: {

			break;
		}
		case 3: {
			window->close();
			break;
		}
		default:
			break;
		}
	}
}