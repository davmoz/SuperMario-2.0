#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Loot
{
private:
	Texture texture;
	Sprite appearence;
public:
	Loot(const string TileLocation, const IntRect tilePositionInFile, Vector2f position);
	~Loot();
	Sprite getCoinSprite() const;
};