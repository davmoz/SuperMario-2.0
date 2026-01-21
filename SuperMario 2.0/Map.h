#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Map : public sf::Drawable
{
private:
	int width;
	int height;
	sf::View view;
	sf::Vector2f viewVelocity;
	sf::Texture tileSet;
	sf::Sprite background;
	sf::VertexArray vertexArray;
	float tileWorldDimension;
	sf::Texture backgroundTexture;
	float tileTextureDimension;

public:
	Map(const int width, const int height, const float tileTextureDimension, const float tileWorldDimension, const std::string mapFileLocation, const std::string tileFileLocation);
	Map();
	virtual ~Map();
	void moveViewRight(const bool isBoosted);
	void moveViewLeft(const bool isBoosted);
	void addTilesToVertexArray(const int x, const int y, sf::Vector2f position);
	void importMapFromFile(const std::string mapFileLocation);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
