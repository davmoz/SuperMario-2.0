#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
#include "Loot.h"
#include "Shroom.h"
#include "Audio.h"

using namespace sf;
class Collision
{
private:
	int enemyArrayCapacity = 20;
	int coinArrayCapacity = 20;
	int shroomArrayCapacity = 20;
	int nrOfEnemies = 0;
	int nrOfCoins = 0;
	int nrOfShrooms = 0;
	Audio audio;
	Mario *mario;
	Map *map;
	Enemy* *enemy;
	Loot * *loot;
	Shroom* *shroom;


	int collisionMap[144][19];
public:
	Collision();
	virtual ~Collision();
	void MarioMoveLeft();
	void MarioMoveRight();
	void moveViewLeft();
	void moveViewRight();
	void jump() const;
	void moveEnemy();
	Map getMap() const;
	void loadCollisionMap();
	template<typename T>
	void expandArray(T **&arr, int nrOfItems, int &capacity);
	void updateCharacter(float elapsedTime);
	void updateCharTexture(float & elapsedTime, const int tileCoordX, const int tileCoordY, const int nrOfTilesToView, const int tileSize);
	bool isCollidable(Vector2f position) const;
	bool collidingWithLeft(Vector2f currentPosition);
	bool collidingWithRight(Vector2f currentPosition);
	bool collidingWithTop(Vector2f currentPosition);
	bool collidingWithBottom(Vector2f currentPosition);
	bool checkMarioEnemyCollision();
	void checkMarioCoinCollision();
	void checkMarioShroomCollision();
	void draw(RenderWindow *window, const bool paused);
	void saveMarioStats(const string name) const;
};

