#include "Loot.h"
#include <iostream>

using namespace std;
using namespace sf;



Loot::Loot(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const bool isCoin)
{
	if (!texture.loadFromFile(TileLocation))
		std::cerr << "Error: Failed to load texture from " << TileLocation << std::endl;
	appearence.setTexture(texture);
	appearence.setTextureRect(tilePositionInFile);
	appearence.setPosition(position);
	appearence.scale(2, 2);
	this->coin = isCoin;
}

Loot::~Loot()
{

}

Sprite Loot::getLootSprite() const
{
	return appearence;
}

bool Loot::isCoin() const
{
	return coin;
}
