#include "Loot.h"



Loot::Loot(const string TileLocation, const IntRect tilePositionInFile, Vector2f position)
{
	this->texture.loadFromFile(TileLocation);
	this->appearence.setTexture(texture);
	this->appearence.setTexture(this->texture);
	this->appearence.setTextureRect(tilePositionInFile);
	this->appearence.setPosition(position);
	this->appearence.scale(2, 2);
}

Loot::~Loot()
{

}

Sprite Loot::getCoinSprite() const
{
	return this->appearence;
}
