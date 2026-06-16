#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <memory>
#include "Mario.h"
#include "Enemy.h"
#include "Map.h"
#include "Loot.h"
#include "Audio.h"
#include "Constants.h"

class Collision
{
private:
	Audio audio;
	std::unique_ptr<Mario> mario;
	std::unique_ptr<Map> map;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Loot>> loots;

	int collisionMap[COLLISION_MAP_WIDTH][COLLISION_MAP_HEIGHT];
	bool bossDefeated = false; // set when this level's boss is beaten

public:
	Collision(const std::string tileFileLocation, const std::string coordMapLocation);
	void MarioMoveLeft();
	void MarioMoveRight();
	void moveViewLeft();
	void moveViewRight();
	void jump() const;
	void moveEnemy();
	void loadCollisionMap(const std::string coordMapLocation);
	const float groundheight = GROUND_HEIGHT;
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
	void draw(sf::RenderWindow *window);
	void saveMarioStats(const std::string HighScoreFileLocation, const std::string name) const;
	PlayerStats getMarioStats() const;
	void applyMarioStats(const PlayerStats &stats);
};
