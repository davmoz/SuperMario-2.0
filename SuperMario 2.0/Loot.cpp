#include "Loot.h"



Loot::Loot(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const bool isCoin)
{
	texture.loadFromFile(TileLocation);
	appearence.setTexture(texture);
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
