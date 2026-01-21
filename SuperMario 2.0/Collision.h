#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>
#include <string>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
#include "Loot.h"
#include "Audio.h"
#include "Constants.h"

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

	int collisionMap[COLLISION_MAP_WIDTH][COLLISION_MAP_HEIGHT];

public:
	Collision(const std::string highScoreFileLocation, const std::string tileFileLocation, const std::string fontFileLocation, const std::string coordMapLocation);
	~Collision();
	void MarioMoveLeft();
	void MarioMoveRight();
	void moveViewLeft();
	void moveViewRight();
	void jump() const;
	void moveEnemy();
	void loadCollisionMap(const std::string coordMapLocation);
	const float groundheight = GROUND_HEIGHT;
	template<typename T>
	void expandArray(T **&arr, int nrOfItems, int &capacity);
	void updateCharacter();
	void updateCharTexture(const int nrOfTilesToView);
	bool isCollidable(sf::Vector2f position) const;
	bool collidingWithLeft(sf::Vector2f currentPosition);
	bool collidingWithRight(sf::Vector2f currentPosition);
	bool collidingWithTop(sf::Vector2f currentPosition);
	bool collidingWithBottom(sf::Vector2f currentPosition);
	bool checkMarioHostileCollision();
	void checkMarioLootCollision();
	bool checkMarioFinishCollision();
	void draw(sf::RenderWindow *window, const bool paused);
	void saveMarioStats(const std::string HighScoreFileLocation, const std::string name) const;
};
