#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

float x = 0;
float y = 0;
float velocityX = 0;
float velocityY = 0;
float accelerationX = 0;
float accelerationY = 0;

float gravity = 2;

void updateMovement() {

	if (y < 500)                  //If you are above ground
		velocityY += gravity;    //Add gravity
	else if (y > 500)             //If you are below ground
		y = 500;                 //That's not supposed to happen, put him back up

	velocityX += accelerationX;
	velocityY += accelerationY;

	x += velocityX;
	y += velocityY;
}

int main() {
	sf::RenderWindow ventana(sf::VideoMode(800, 600), "mi ventana");
	ventana.setFramerateLimit(60);
	sf::Texture Image;
	Image.loadFromFile("Tiles/main.png", IntRect(0, 32, 16, 16));
	sf::Sprite sprite(Image);
	sprite.setPosition(-230, 100);

	sf::CircleShape figura(10);

	while (ventana.isOpen())
	{
		//Eventos
		Event miEvento;
		while (ventana.pollEvent(miEvento)) {
			if (miEvento.type == sf::Event::Closed) {
				ventana.close();
			}
			else if (miEvento.type == sf::Event::KeyPressed && miEvento.key.code == sf::Keyboard::Space) {
				velocityY = -30;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			velocityX = -5;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			velocityX = 5;

		updateMovement();
		sprite.setPosition(x, y);

		//Renderizado
		ventana.clear();
		ventana.draw(sprite);
		ventana.display();
	}

	return 0;
}