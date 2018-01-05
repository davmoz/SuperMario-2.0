#include "Shroom.h"

Shroom::Shroom(const string TileLocation, const IntRect tilePositionInFile, Vector2f position)
{
	texture.loadFromFile(TileLocation);
	appearence.setTexture(texture);
	appearence.setTexture(texture);
	appearence.setTextureRect(tilePositionInFile);
	appearence.setPosition(position);
	appearence.scale(2, 2);
}

Shroom::~Shroom()
{

}

Sprite Shroom::getShroomSprite() const
{
	return appearence;
}
