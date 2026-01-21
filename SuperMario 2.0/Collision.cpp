#include "Collision.h"


Collision::Collision(const string highScoreFileLocation, const string tileFileLocation, const string fontFileLocation, const string coordMapLocation)
{
	enemyArrayCapacity = 20;
	lootArrayCapacity = 20;
	nrOfEnemies = 0;
	nrOfLoot = 0;
	bool canFly;
	float gravity;
	mario = new Mario(tileFileLocation, IntRect(0, 32, 16, 16), fontFileLocation, Vector2f(160.0f, 0), Vector2f(2.0f, 0.0f), 0.4f, 16.0f);
	enemy = new Enemy*[enemyArrayCapacity];
	loot = new Loot*[lootArrayCapacity];
	map = new Map(50, 16, 16.0f, 32.0f, coordMapLocation, tileFileLocation);
	loadCollisionMap(coordMapLocation);
	IntRect enemyRect;
	
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 144; x++)
		{
			if (collisionMap[x][y] == -1)
			{
				expandArray(loot, nrOfLoot, lootArrayCapacity);
				loot[nrOfLoot] = new Loot(tileFileLocation, IntRect(0, 64, 16, 16), Vector2f(32.0f * x, 32.0f * y), true);
				nrOfLoot++;
			}
			else if (collisionMap[x][y] == 9) {
				expandArray(loot, nrOfLoot, lootArrayCapacity);
				loot[nrOfLoot] = new Loot(tileFileLocation, IntRect(0, 16, 16, 16), Vector2f(32.0f * x, 32.0f * y), false);
				nrOfLoot++;
			}
			else if (collisionMap[x][y] == 8)
			{
				if (rand() % 4 > 1) {
					gravity = 0.4f;
					canFly = false;
					enemyRect = IntRect(64, 0, 16, 16);
				}
				else 
				{
					gravity = 0.3f;
					canFly = true;
					enemyRect = IntRect(0, 96, 16, 16);
				}

				expandArray(enemy, nrOfEnemies, enemyArrayCapacity);
				enemy[nrOfEnemies] = new Enemy(tileFileLocation, enemyRect, Vector2f(32.0f * x, 32.0f * y), Vector2f(1.0f, 0.0f), canFly, gravity, 10.0f);
				nrOfEnemies++;
			} 
			
		}
	}
}

Collision::~Collision()
{
	delete mario;
	delete map;
	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			delete enemy[i];
		}
	}
	delete[] enemy;
	for (int i = 0; i < nrOfLoot; i++)
	{
		if (loot[i] != nullptr)
		{
			delete loot[i];
		}
	}
	delete[] loot;
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
	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->move(collidingWithRight(enemy[i]->getPosition()), collidingWithLeft(enemy[i]->getPosition()));
		}
	}
}

void Collision::loadCollisionMap(const string coordMapLocation)
{
	ifstream fromFile;
	fromFile.open(coordMapLocation);
	int x = 0, y = 0, tileType;
	if (fromFile.is_open())
	{
		while (fromFile >> tileType)
		{
			collisionMap[x][y] = tileType;
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

template<typename T>
void Collision::expandArray(T **&arr, int nrOfItems, int & capacity)
{
	if (nrOfItems == capacity)
	{
		T* *temp = new T*[capacity * 2];
		for (int i = 0; i < nrOfItems; i++)
		{
			if (arr[i] != nullptr)
			{
				temp[i] = arr[i];
			}
		}
		delete[] arr;
		arr = temp;
		capacity *= 2;
	}
}
void Collision::updateCharacter()
{
	mario->getPosition();
	mario->updateCharacter(collidingWithTop(mario->getPosition()), collidingWithBottom(mario->getPosition()));
	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->fly();
			enemy[i]->updateTexture(-1);
			enemy[i]->updateCharacter(collidingWithTop(enemy[i]->getPosition()), collidingWithBottom(enemy[i]->getPosition()));
		}
	}
} 

void Collision::updateCharTexture(const int nrOfTilesToView)
{
	mario->updateTexture(nrOfTilesToView);
}

bool Collision::isCollidable(Vector2f position) const
{
	bool collided = false;
	int xPos = position.x / 32.0f;
	int yPos = position.y / 32.0f;
	if (xPos < 0 || xPos >= 144 || yPos < 0 || yPos >= 19)
		return false;
	if (collisionMap[xPos][yPos] != 0
		&& collisionMap[xPos][yPos] != 9
		&& collisionMap[xPos][yPos] != 8
		&& collisionMap[xPos][yPos] != -1)
	{
		collided = true;
	}
	return collided;
}

bool Collision::collidingWithLeft(Vector2f currentPosition)
{
	int quarterOrTile = 8;
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
	int quarterOrTile = 8;
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
	int quarterOrTile = 8;
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
	int quarterOrTile = 8;
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
	string collisionSide = "";
	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			collisionSide = mario->collidesWithChar(*enemy[i]);
			if (collisionSide == "BOTTOM")
			{
				audio.stompMusicPlay();
				mario->increaseEnemiesKilled();
				delete enemy[i];
				enemy[i] = nullptr;
			}
			else if(collisionSide == "LEFT" || collisionSide == "RIGHT")
			{
				marioIsDead = true;
			}
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
	for (int i = 0; i < nrOfLoot; i++)
	{
		if (loot[i] != nullptr)
		{
			if (mario->getSprite().getGlobalBounds().intersects(loot[i]->getLootSprite().getGlobalBounds()))
			{
				if (loot[i]->isCoin())
				{
					audio.coinMusicPlay();
					mario->increaseCoins();
				}
				else
				{
					audio.shroomMusicPlay();
					mario->changeMarioVelocityX(true);
				}
				
				delete loot[i];
				loot[i] = nullptr;
			}
		}
	}
}

bool Collision::checkMarioFinishCollision()
{
	bool finished = false;
	int xPos = (mario->getPosition().x / 32.0f) + 1;
	int yPos = mario->getPosition().y / 32.0f;
	if (xPos < 0 || xPos >= 144 || yPos < 0 || yPos >= 19)
		return false;
	if (collisionMap[xPos][yPos] == -4)
	{
		finished = true;
	}
	return finished;
}

void Collision::draw(RenderWindow * window, const bool paused)
{
	window->draw(*map);
	mario->drawCharacter(window);

	mario->updateAndDrawCoinsAndTime(window, paused);
	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->drawCharacter(window);
		}
	}
	for (int i = 0; i < nrOfLoot; i++)
	{
		if (loot[i] != nullptr)
		{
			window->draw(loot[i]->getLootSprite());
		}
	}
}

void Collision::saveMarioStats(const string HighScoreFileLocation, const string name) const
{
	mario->exportScoreToFile(HighScoreFileLocation, name);
}
