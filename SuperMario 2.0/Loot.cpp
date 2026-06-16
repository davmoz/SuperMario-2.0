#include "Loot.h"
#include "Constants.h"

using namespace std;
using namespace sf;

namespace
{
	// Atlas cells (in 16-px tiles) used for collectibles.
	const IntRect COIN_RECT(0, 64, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE);   // (0,4)
	const IntRect SHROOM_RECT(0, 16, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE); // (0,1)
}

Loot::Loot(const Texture &texture, Vector2f position, LootType type)
{
	this->type = type;
	appearence.setTexture(texture);

	// Sprite + tint per type. The tints distinguish the two mushrooms and the
	// star, which reuse the same base sprites.
	switch (type)
	{
	case LootType::Coin:
		appearence.setTextureRect(COIN_RECT);
		break;
	case LootType::SpeedShroom:
		appearence.setTextureRect(SHROOM_RECT);
		appearence.setColor(Color(255, 130, 130)); // red mushroom
		break;
	case LootType::GrowMushroom:
		appearence.setTextureRect(SHROOM_RECT);
		appearence.setColor(Color(130, 255, 130)); // green mushroom
		break;
	case LootType::Star:
		appearence.setTextureRect(COIN_RECT);
		appearence.setColor(Color(255, 240, 80)); // bright star
		break;
	}
	appearence.setPosition(position);
	appearence.scale(2, 2);
}

Loot::~Loot()
{

}

Sprite Loot::getLootSprite() const
{
	return appearence;
}

LootType Loot::getType() const
{
	return type;
}
