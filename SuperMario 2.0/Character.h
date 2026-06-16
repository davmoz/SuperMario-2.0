#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class Character
{
private:
	sf::IntRect tilePosition;
	sf::Sprite appearence;
	sf::Vector2f velocity;
	bool isMovingRight = false;
	bool isJumping = false;
	float gravity = 0.0f;
	float jumpHeight = 0.0f;
	float scaleFactor = 2.0f;
	sf::Clock clock;

protected:
	// Hooks for subclasses (e.g. Boss) to alter their appearance.
	void setBaseScale(float factor);
	void setAppearanceColor(sf::Color color);

public:
	Character(const sf::Texture &texture, const sf::IntRect tilePositionInFile, const sf::Vector2f position, const sf::Vector2f velocity, const float gravity, const float jumpheight);
	Character();
	virtual ~Character();

	void moveLeft(bool updateFacingDirection = true);
	void moveRight(bool updateFacingDirection = true);
	void jump();
	void bounce(); // a hop after stomping an enemy
	void doubleVelocityX(const bool isBoosted);
	void updateCharacter(const bool topCollision, const bool botCollision);
	void updateTexture(int nrOfTilesToView);

	std::string collidesWithChar(const Character & otherChar);
	sf::Sprite getSprite() const;
	sf::Vector2f getPosition() const;
	void drawCharacter(sf::RenderWindow * window);
};
