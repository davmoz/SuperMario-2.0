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
	const sf::Texture *tileSet = nullptr;        // shared, owned by TextureManager
	sf::Sprite background;
	sf::VertexArray vertexArray;
	float tileWorldDimension;
	float tileTextureDimension;

public:
	Map(const int width, const int height, const float tileTextureDimension, const float tileWorldDimension, const std::string mapFileLocation, const sf::Texture &tileset, const sf::Texture &backgroundTexture);
	virtual ~Map();
	void moveViewRight(const bool isBoosted);
	void moveViewLeft(const bool isBoosted);
	void addTilesToVertexArray(const int x, const int y, sf::Vector2f position);
	void importMapFromFile(const std::string mapFileLocation);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
