#include "Collision.h"


Collision::Collision()
{
	srand(time(0));
	bool canFly;
	this->mario = new Mario("Tiles/main.png", IntRect(0, 32, 16, 16), Vector2f(160.0f, 0), Vector2f(2.0f, 0.0f));
	this->shroom = new Shroom*[this->shroomArrayCapacity];
	this->enemy = new Enemy*[this->enemyArrayCapacity];
	this->loot = new Loot*[this->coinArrayCapacity];
	this->map = new Map(50, 16, 16.0f, 32.0f);
	this->loadCollisionMap();
	IntRect enemyRect;
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 144; x++)
		{
			if (this->collisionMap[x][y] == 9)
			{
				this->expandArray(loot, this->nrOfCoins, this->coinArrayCapacity);
				this->loot[this->nrOfCoins] = new Loot("Tiles/main.png", IntRect(0, 64, 16, 16), Vector2f(32.0f * x, 32.0f * y));
				this->nrOfCoins++;
			}
			else if (this->collisionMap[x][y] == 8)
			{
				//fixas senare...........................................................
				if (rand() % 20 > 9) {
					canFly = false;
					enemyRect = IntRect(64, 0, 16, 16);
				}
				else {
					canFly = true;
					enemyRect = IntRect(0, 96, 16, 16);
				}

				this->expandArray(enemy, this->nrOfEnemies, this->enemyArrayCapacity);
				this->enemy[this->nrOfEnemies] = new Enemy("Tiles/main.png", enemyRect, Vector2f(32.0f * x, 32.0f * y), Vector2f(1.0f, 0.0f), canFly);
				this->nrOfEnemies++;
			} 
			else if (this->collisionMap[x][y] == -1) {
				this->expandArray(shroom, this->nrOfShrooms, this->shroomArrayCapacity);
				this->shroom[this->nrOfShrooms] = new Shroom("Tiles/main.png", IntRect(0, 16, 16, 16), Vector2f(32.0f * x, 32.0f * y));
				this->nrOfShrooms++;
			}
		}
	}
}

Collision::~Collision()
{
	delete this->mario;
	delete this->map;
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemy[i] != nullptr)
		{
			delete this->enemy[i];
			this->enemy[i] = nullptr; // Onödigt då arrayen tas bort omedelbart efteråt
		}
	}
	delete[] this->enemy;
	this->enemy = nullptr;
	for (int i = 0; i < this->nrOfCoins; i++)
	{
		if (this->loot[i] != nullptr)
		{
			delete this->loot[i];
			this->loot[i] = nullptr;
		}
	}
	delete[] this->loot;
	this->loot = nullptr;
	for (int i = 0; i < this->nrOfShrooms; i++)
	{
		if (this->shroom[i] != nullptr)
		{
			delete this->shroom[i];
			this->shroom[i] = nullptr;
		}
	}
	delete[] this->shroom;
	this->shroom = nullptr;
}

void Collision::MarioMoveLeft()
{
	this->mario->moveLeft();
	if (this->collidingWithLeft(this->mario->getSprite().getPosition()))
	{
		this->mario->moveRight(false);
		this->map->moveViewRight(mario->isBoosted());
	}
}

void Collision::MarioMoveRight()
{
	this->mario->moveRight();
	if (this->collidingWithRight(this->mario->getSprite().getPosition()))
	{
		this->mario->moveLeft(false);
		this->map->moveViewLeft(mario->isBoosted());
	}
}

void Collision::moveViewLeft()
{
	this->map->moveViewLeft(mario->isBoosted());
}

void Collision::moveViewRight()
{
	this->map->moveViewRight(mario->isBoosted());
}

void Collision::jump() const
{
	this->mario->jump();
}

void Collision::moveEnemy()
{
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemy[i] != nullptr)
		{
			this->enemy[i]->autoMove(this->collidingWithRight(this->enemy[i]->getSprite().getPosition()), this->collidingWithLeft(this->enemy[i]->getSprite().getPosition()));
		}
	}
}

Map Collision::getMap() const
{
	return *this->map;
}

void Collision::loadCollisionMap()
{
	ifstream fromFile;
	fromFile.open("Coords.txt");
	int x = 0, y = 0, tileType;
	if (fromFile.is_open())
	{
		while (!fromFile.eof())
		{
			fromFile >> tileType;
			fromFile.ignore();
			this->collisionMap[x][y] = tileType;
			if (fromFile.peek() == '\n')
			{
				x = 0;
				y++;
			}
			else
			{
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
// Mario dies cause below height
void Collision::updateCharacter(float elapsedTime)
{
	this->mario->getPosition();
	this->mario->updateCharacter(this->collidingWithTop(this->mario->getSprite().getPosition()), this->collidingWithBottom(this->mario->getSprite().getPosition()));
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemy[i] != nullptr)
		{
			this->enemy[i]->fly(elapsedTime);
			this->enemy[i]->updateCharacter(this->collidingWithTop(this->enemy[i]->getSprite().getPosition()), this->collidingWithBottom(this->enemy[i]->getSprite().getPosition()));
			
		}
	}
	/*if (this->mario->getSprite().getPosition().y > this->mario->groundHeight)
	{
		cout << "Mario got rekt" << endl;
	}*/
} 

void Collision::updateCharTexture(float & elapsedTime, const int tileCoordX, const int tileCoordY, const int nrOfTilesToView, const int tileSize)
{
	this->mario->updateTexture(elapsedTime, tileCoordX, tileCoordY, nrOfTilesToView, tileSize);
}

bool Collision::isCollidable(Vector2f position) const
{
	bool collided = false;
	int xPos = position.x / 32.0f;
	int yPos = position.y / 32.0f;
	if (this->collisionMap[xPos][yPos] != 0 
		&& this->collisionMap[xPos][yPos] != 9 
		&& this->collisionMap[xPos][yPos] != 8
		&& this->collisionMap[xPos][yPos] != -1)
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

	if (this->isCollidable(firstLeft) || this->isCollidable(secondLeft) || this->isCollidable(thirdLeft))
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

	if (this->isCollidable(firstRight) || this->isCollidable(secondRight) || this->isCollidable(thirdRight))
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

	Vector2f firstTop = Vector2f(x - quarterOrTile * 2, y - quarterOrTile * 2);
	Vector2f secondTop = Vector2f(x,					y - quarterOrTile * 2);
	Vector2f thirdTop = Vector2f(x + quarterOrTile * 2, y - quarterOrTile * 2);

	if (this->isCollidable(firstTop) || this->isCollidable(secondTop) || this->isCollidable(thirdTop))
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
	float y = currentPosition.y + 0.5;

	Vector2f firstBottom = Vector2f(x + quarterOrTile * 1,	y + quarterOrTile * 2);
	Vector2f secondBottom = Vector2f(x,						y + quarterOrTile * 2);
	Vector2f thirdBottom = Vector2f(x - quarterOrTile * 1,	y + quarterOrTile * 2);
	
	
	if (this->isCollidable(firstBottom) || this->isCollidable(secondBottom) || this->isCollidable(thirdBottom))
	{
		collided = true;
	}
	return collided;
}

bool Collision::checkMarioEnemyCollision()
{
	bool marioIsDead = false;
	string collisionSide = "";
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemy[i] != nullptr)
		{
			collisionSide = this->mario->collidesWithChar(*this->enemy[i]);
			if (collisionSide == "BOTTOM")
			{
				this->audio.stompMusicPlay();
				delete this->enemy[i];
				this->enemy[i] = nullptr;
			}
			else if(collisionSide == "LEFT" || collisionSide == "RIGHT")
			{
				marioIsDead = true;
			}
		}
	}
	return marioIsDead;
}

void Collision::checkMarioCoinCollision()
{
	for (int i = 0; i < this->nrOfCoins; i++)
	{
		if (this->loot[i] != nullptr)
		{
			if (this->mario->getSprite().getGlobalBounds().intersects(this->loot[i]->getCoinSprite().getGlobalBounds()))
			{
				this->audio.coinMusicPlay();
				delete this->loot[i];
				this->loot[i] = nullptr;
				this->mario->increaseCoins();
			}
		}
	}
}

void Collision::checkMarioShroomCollision()
{
	for (int i = 0; i < this->nrOfShrooms; i++)
	{
		if (this->shroom[i] != nullptr)
		{
			if (this->mario->getSprite().getGlobalBounds().intersects(this->shroom[i]->getShroomSprite().getGlobalBounds()))
			{
				delete this->shroom[i];
				this->shroom[i] = nullptr;
				this->audio.shroomMusicPlay();
				this->mario->changeMarioVelocityX(true);
			}
		}
	}
}

void Collision::draw(RenderWindow * window, const bool paused)
{
	window->draw(*this->map);
	this->mario->drawCharacter(window);

	this->mario->drawCoinsAndTime(window, paused);
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemy[i] != nullptr)
		{
			this->enemy[i]->drawCharacter(window);
		}
	}
	for (int i = 0; i < this->nrOfCoins; i++)
	{
		if (this->loot[i] != nullptr)
		{
			window->draw(this->loot[i]->getCoinSprite());
		}
	}
	for (int i = 0; i < this->nrOfShrooms; i++)
	{
		if (this->shroom[i] != nullptr)
		{
			window->draw(this->shroom[i]->getShroomSprite());
		}
	}
}

void Collision::saveMarioStats(const string name) const
{
	mario->exportScoreToFile(name);
}
