#include "Collision.h"
#include "Constants.h"
#include "TileType.h"
#include "Boss.h"

using namespace std;
using namespace sf;

Collision::Collision(TextureManager &textures, const string tileFileLocation, const string coordMapLocation)
{
	const Texture &tileTexture = textures.get(tileFileLocation);
	const Texture &backgroundTexture = textures.get("Tiles/Mario_BG.JPG");
	mario = make_unique<Mario>(tileTexture, IntRect(0, TILE_SIZE, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE), Vector2f(160.0f, 0), Vector2f(2.0f, 0.0f), DEFAULT_GRAVITY, DEFAULT_JUMP_HEIGHT);
	map = make_unique<Map>(COLLISION_MAP_WIDTH, COLLISION_MAP_HEIGHT, (float)TILE_TEXTURE_SIZE, (float)TILE_SIZE, coordMapLocation, tileTexture, backgroundTexture);
	loadCollisionMap(coordMapLocation);

	for (int y = 0; y < COLLISION_MAP_HEIGHT; y++)
	{
		for (int x = 0; x < COLLISION_MAP_WIDTH; x++)
		{
			const Vector2f pos((float)TILE_SIZE * x, (float)TILE_SIZE * y);
			bool spawnLoot = true;
			LootType lootType = LootType::Coin;
			switch (collisionMap[x][y])
			{
			case tiles::Coin:      lootType = LootType::Coin;         break;
			case tiles::BlockLoot: lootType = LootType::SpeedShroom;  break;
			case tiles::GrowSpawn: lootType = LootType::GrowMushroom; break;
			case tiles::StarSpawn: lootType = LootType::Star;         break;
			default:               spawnLoot = false;                 break;
			}
			if (spawnLoot)
			{
				loots.push_back(make_unique<Loot>(tileTexture, pos, lootType));
			}
			else if (collisionMap[x][y] == tiles::EnemySpawn)
			{
				bool canFly;
				float gravity;
				IntRect enemyRect;
				if (rand() % 4 > 1) {
					gravity = DEFAULT_GRAVITY;
					canFly = false;
					enemyRect = IntRect(64, 0, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE);
				}
				else
				{
					gravity = FLYING_ENEMY_GRAVITY;
					canFly = true;
					enemyRect = IntRect(0, 96, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE);
				}
				enemies.push_back(make_unique<Enemy>(tileTexture, enemyRect, pos, Vector2f(1.0f, 0.0f), canFly, gravity, ENEMY_JUMP_HEIGHT));
			}
			else if (collisionMap[x][y] == tiles::BossSpawn)
			{
				enemies.push_back(make_unique<Boss>(tileTexture, IntRect(64, 0, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE), pos, Vector2f(1.0f, 0.0f), DEFAULT_GRAVITY, BOSS_HEALTH));
			}
		}
	}
}

void Collision::MarioMoveLeft()
{
	mario->moveLeft();
	if (collidingWithLeft(mario->getPosition()))
	{
		mario->moveRight(false);
		map->moveViewRight(mario->isBoosted());
	}
}

void Collision::MarioMoveRight()
{
	mario->moveRight();
	if (collidingWithRight(mario->getPosition()))
	{
		mario->moveLeft(false);
		map->moveViewLeft(mario->isBoosted());
	}
}

void Collision::moveViewLeft()
{
	map->moveViewLeft(mario->isBoosted());
}

void Collision::moveViewRight()
{
	map->moveViewRight(mario->isBoosted());
}

void Collision::jump() const
{
	mario->jump();
}

void Collision::moveEnemy()
{
	for (auto &e : enemies)
	{
		if (e)
			e->move(collidingWithRight(e->getPosition()), collidingWithLeft(e->getPosition()));
	}
}

void Collision::loadCollisionMap(const string coordMapLocation)
{
	for (int i = 0; i < COLLISION_MAP_WIDTH; i++)
		for (int j = 0; j < COLLISION_MAP_HEIGHT; j++)
			collisionMap[i][j] = tiles::Empty;

	ifstream fromFile;
	fromFile.open(coordMapLocation);
	int x = 0, y = 0, tileType;
	if (fromFile.is_open())
	{
		while (fromFile >> tileType)
		{
			if (x < COLLISION_MAP_WIDTH && y < COLLISION_MAP_HEIGHT)
				collisionMap[x][y] = tileType;   // ignore anything past the grid
			if (fromFile.peek() == '\n')
			{
				fromFile.ignore();
				x = 0;
				y++;
			}
			else
			{
				fromFile.ignore();
				x++;
			}
		}
	}
	fromFile.close();
}

void Collision::updateCharacter()
{
	mario->updateTimers();
	mario->updateCharacter(collidingWithTop(mario->getPosition()), collidingWithBottom(mario->getPosition()));
	for (auto &e : enemies)
	{
		if (!e)
			continue;
		// Reclaim enemies that have fallen off the bottom of the world.
		if (e->getPosition().y > ENEMY_DESPAWN_Y)
		{
			e.reset();
			continue;
		}
		e->fly();
		e->updateTexture(-1);
		e->updateCharacter(collidingWithTop(e->getPosition()), collidingWithBottom(e->getPosition()));
	}
}

void Collision::updateCharTexture(const int nrOfTilesToView)
{
	mario->updateTexture(nrOfTilesToView);
}

bool Collision::isCollidable(Vector2f position) const
{
	int xPos = position.x / TILE_SIZE;
	int yPos = position.y / TILE_SIZE;
	if (xPos < 0 || xPos >= COLLISION_MAP_WIDTH || yPos < 0 || yPos >= COLLISION_MAP_HEIGHT)
		return false;
	return tiles::isSolid(collisionMap[xPos][yPos]);
}

bool Collision::collidingWithLeft(Vector2f currentPosition)
{
	int quarterOrTile = QUARTER_TILE;
	bool collided = false;
	float x = currentPosition.x;
	float y = currentPosition.y;

	Vector2f firstLeft = Vector2f(x - quarterOrTile * 2, y - quarterOrTile * 1);
	Vector2f secondLeft = Vector2f(x - quarterOrTile * 2, y);
	Vector2f thirdLeft = Vector2f(x - quarterOrTile * 2, y + quarterOrTile * 1);

	if (isCollidable(firstLeft) || isCollidable(secondLeft) || isCollidable(thirdLeft))
	{
		collided = true;
	}
	return collided;
}

bool Collision::collidingWithRight(Vector2f currentPosition)
{
	int quarterOrTile = QUARTER_TILE;
	bool collided = false;
	float x = currentPosition.x;
	float y = currentPosition.y;

	Vector2f firstRight = Vector2f(x + quarterOrTile * 2, y - quarterOrTile * 1);
	Vector2f secondRight = Vector2f(x + quarterOrTile * 2, y);
	Vector2f thirdRight = Vector2f(x + quarterOrTile * 2, y + quarterOrTile * 1);

	if (isCollidable(firstRight) || isCollidable(secondRight) || isCollidable(thirdRight))
	{
		collided = true;
	}
	return collided;
}

bool Collision::collidingWithTop(Vector2f currentPosition)
{
	int quarterOrTile = QUARTER_TILE;
	bool collided = false;
	float x = currentPosition.x;
	float y = currentPosition.y;

	Vector2f firstTop = Vector2f(x - quarterOrTile * 1, y - quarterOrTile * 2);
	Vector2f secondTop = Vector2f(x,					y - quarterOrTile * 2);
	Vector2f thirdTop = Vector2f(x + quarterOrTile * 1, y - quarterOrTile * 2);

	if (isCollidable(firstTop) || isCollidable(secondTop) || isCollidable(thirdTop))
	{
		collided = true;
	}
	return collided;
}

bool Collision::collidingWithBottom(Vector2f currentPosition)
{
	int quarterOrTile = QUARTER_TILE;
	bool collided = false;
	float x = currentPosition.x;
	float y = currentPosition.y;

	Vector2f firstBottom = Vector2f(x + quarterOrTile * 1,	y + quarterOrTile * 2);
	Vector2f secondBottom = Vector2f(x,						y + quarterOrTile * 2);
	Vector2f thirdBottom = Vector2f(x - quarterOrTile * 1,	y + quarterOrTile * 2);
	
	
	if (isCollidable(firstBottom) || isCollidable(secondBottom) || isCollidable(thirdBottom))
	{
		collided = true;
	}
	return collided;
}

bool Collision::checkMarioHostileCollision()
{
	bool marioIsDead = false;
	for (auto &e : enemies)
	{
		if (!e)
			continue;
		const string collisionSide = mario->collidesWithChar(*e);
		if (collisionSide.empty())
			continue; // no contact this frame

		const bool stomp = (collisionSide == "BOTTOM");
		if (stomp || mario->isStarActive())
		{
			// Stomping, or steamrolling while a star is active: damage it.
			if (stomp)
				mario->bounce();
			const bool wasBoss = e->isBoss();
			if (e->onStomped()) // defeated?
			{
				if (wasBoss)
					bossDefeated = true;
				mario->increaseEnemiesKilled();
				e.reset();
			}
			audio.stompMusicPlay();
		}
		else if (!mario->isInvulnerable())
		{
			// A deadly side hit: a big Mario shrinks and survives; a small
			// Mario dies.
			if (mario->absorbHit())
				marioIsDead = true;
			else
				audio.stompMusicPlay();
		}
	}
	if (mario->getPosition().y > groundheight)
	{
		marioIsDead = true;
	}
	return marioIsDead;
}

void Collision::checkMarioLootCollision()
{
	for (auto &item : loots)
	{
		if (!item)
			continue;
		if (mario->getSprite().getGlobalBounds().intersects(item->getLootSprite().getGlobalBounds()))
		{
			switch (item->getType())
			{
			case LootType::Coin:
				audio.coinMusicPlay();
				mario->increaseCoins();
				break;
			case LootType::SpeedShroom:
				audio.shroomMusicPlay();
				mario->changeMarioVelocityX();
				break;
			case LootType::GrowMushroom:
				audio.shroomMusicPlay();
				mario->grow();
				break;
			case LootType::Star:
				audio.starMusicPlay();
				mario->activateStar();
				break;
			}
			item.reset();
		}
	}
}

bool Collision::checkMarioFinishCollision()
{
	if (bossDefeated) // beating the boss completes a boss level
		return true;
	int xPos = (mario->getPosition().x / TILE_SIZE) + 1;
	int yPos = mario->getPosition().y / TILE_SIZE;
	if (xPos < 0 || xPos >= COLLISION_MAP_WIDTH || yPos < 0 || yPos >= COLLISION_MAP_HEIGHT)
		return false;
	return tiles::isFinish(collisionMap[xPos][yPos]);
}

void Collision::draw(RenderWindow * window)
{
	window->draw(*map);
	mario->drawCharacter(window);
	for (auto &e : enemies)
	{
		if (e)
			e->drawCharacter(window);
	}
	for (auto &item : loots)
	{
		if (item)
			window->draw(item->getLootSprite());
	}
}

void Collision::saveMarioStats(const string HighScoreFileLocation, const string name) const
{
	mario->exportScoreToFile(HighScoreFileLocation, name);
}

PlayerStats Collision::getMarioStats() const
{
	return mario->getStats();
}

void Collision::applyMarioStats(const PlayerStats &stats)
{
	mario->applyStats(stats);
}
