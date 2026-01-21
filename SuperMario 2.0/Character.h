#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class Character
{
private:
	sf::Texture texture;
	sf::IntRect tilePosition;
	sf::Sprite appearence;
	sf::Vector2f position;
	sf::Vector2f velocity;
	bool isMovingRight;
	bool isJumping;
	float gravity;
	float jumpHeight;
	sf::Clock clock;

public:
	Character(const std::string TileLocation, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const sf::Vector2f velocity, const float gravity, const float jumpheight);
	Character();
	virtual ~Character();

	void moveLeft(bool updateFacingDirection = true);
	void moveRight(bool updateFacingDirection = true);
	void jump();
	void doubleVelocityX(const bool isBoosted);
	void updateCharacter(const bool topCollision, const bool botCollision);
	void updateTexture(int nrOfTilesToView);

	std::string collidesWithChar(const Character & otherChar);
	sf::Sprite getSprite() const;
	sf::Vector2f getPosition() const;
	void drawCharacter(sf::RenderWindow * window);
};
