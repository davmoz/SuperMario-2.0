#include "Boss.h"

using namespace sf;
using namespace std;

Boss::Boss(const string TileLocation, const IntRect tilePositionInFile, const Vector2f position, const Vector2f velocity, const float gravity, const int startingHealth)
	: Enemy(TileLocation, tilePositionInFile, position, velocity, false /*canFly*/, gravity, 0.0f),
	  health(startingHealth)
{
	setBaseScale(3.5f);                   // visibly larger than a normal foe
	setAppearanceColor(Color(255, 90, 90)); // menacing red tint
}

bool Boss::onStomped()
{
	if (health > 0)
		health--;
	return health <= 0;
}
