#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Shroom
{
private:
	Texture texture;
	Sprite appearence;
public:
	Shroom(const string TileLocation, const IntRect tilePositionInFile, Vector2f position);
	~Shroom();
	Sprite getShroomSprite() const;
};