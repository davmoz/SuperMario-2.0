#include "Mario.h"
#include <iostream>

Mario::Mario(const string TileLocation, const IntRect tilePositionInFile) : Character(TileLocation, tilePositionInFile)
{

}


Mario::~Mario()
{
}

void Mario::updateTexture(float & elapsedTime, const int direction)
{
	float leftRectPos = this->getSprite().getTextureRect().left;
	if (elapsedTime > 0.09f)
	{
		if (leftRectPos > 48.0f)
		{
			this->setTexture(IntRect(0, 32, 16, 16), direction);
		}
		else
		{
			this->setTexture(IntRect(leftRectPos + 16, 32, 16, 16), direction);
		}
		elapsedTime = 0;
	}
}
