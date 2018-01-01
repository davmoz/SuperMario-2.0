#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

int main() {
	sf::RenderWindow ventana(sf::VideoMode(800, 600), "mi ventana");
	ventana.setFramerateLimit(60);
	Font font;
	font.loadFromFile("Fonts/Super Mario Bros.ttf");
	sf::CircleShape figura(10);
	Text text;
	string txt = "Name: ";
	text.setFont(font);
	text.setFillColor(Color::Red);
	text.setCharacterSize(32);

	while (ventana.isOpen())
	{
		//Eventos
		Event miEvento;
		while (ventana.pollEvent(miEvento)) {
			if (miEvento.type == sf::Event::Closed) {
				ventana.close();
			}
			else if (miEvento.type == sf::Event::KeyPressed && miEvento.key.code == sf::Keyboard::Space) {
				
			}
			else if (Event::TextEntered)
			{
				if (miEvento.text.unicode == 32)
				{
					txt += " ";
					text.setString(txt);
				}
				else if (miEvento.text.unicode == Keyboard::BackSpace)
				{
					txt = txt.substr(0, txt.length() - 1);
					text.setString(txt);
				}
				else if((miEvento.text.unicode >= 48 
					&& miEvento.text.unicode <= 57 
					&& miEvento.text.unicode != Keyboard::Space) 
					|| (miEvento.text.unicode >= 65 
						&& miEvento.text.unicode <= 122))
				{
					txt += (char)(miEvento.text.unicode);
					text.setString(txt);
				}
				else if (miEvento.text.unicode == Keyboard::Return)
				{
					txt = "Enter";
					text.setString(txt);
				}
			}
		}

		//Renderizado
		ventana.clear();
		ventana.draw(text);
		ventana.display();
	}

	return 0;
}