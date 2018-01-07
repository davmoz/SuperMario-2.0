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
	bool coin;
public:
	Loot(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const bool isCoin);
	~Loot();
	Sprite getLootSprite() const;
	bool isCoin() const;
};