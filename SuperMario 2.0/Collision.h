#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
#include "Loot.h"
#include "Audio.h"

using namespace sf;
class Collision
{
private:
	int enemyArrayCapacity;
	int lootArrayCapacity;
	int nrOfEnemies;
	int nrOfLoot;

	Audio audio;
	Mario *mario;
	Map *map;
	Enemy* *enemy;
	Loot * *loot;

	int collisionMap[144][19];

public:
	Collision(const string highScoreFileLocation, const string tileFileLocation, const string fontFileLocation, const string coordMapLocation);
	~Collision();
	void MarioMoveLeft();
	void MarioMoveRight();
	void moveViewLeft();
	void moveViewRight();
	void jump() const;
	void moveEnemy();
	void loadCollisionMap(const string coordMapLocation);
	const float groundheight = 550.0f;
	template<typename T>
	void expandArray(T **&arr, int nrOfItems, int &capacity);
	void updateCharacter();
	void updateCharTexture(const int nrOfTilesToView);
	bool isCollidable(Vector2f position) const;
	bool collidingWithLeft(Vector2f currentPosition);
	bool collidingWithRight(Vector2f currentPosition);
	bool collidingWithTop(Vector2f currentPosition);
	bool collidingWithBottom(Vector2f currentPosition);
	bool checkMarioHostileCollision();
	void checkMarioLootCollision();
	bool checkMarioFinishCollision();
	void draw(RenderWindow *window, const bool paused);
	void saveMarioStats(const string HighScoreFileLocation, const string name) const;
};

