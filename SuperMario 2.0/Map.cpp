#include "Map.h"
#include "TileType.h"
#include <iostream>

using namespace std;
using namespace sf;


Map::Map(const int width, const int height, const float tileTextureDimension, const float tileWorldDimension, const string mapFileLocation, const string tileFileLocation)
{
	view.setSize(sf::Vector2f(900, 600));
	view.setCenter(sf::Vector2f(450, 300));
	this->width = width;
	this->height = height;
	viewVelocity = Vector2f(2.0f, 0.0f);
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;
	if (!tileSet.loadFromFile(tileFileLocation))
		std::cerr << "Error: Failed to load tileset from " << tileFileLocation << std::endl;
	if (!backgroundTexture.loadFromFile("Tiles/Mario_BG.JPG"))
		std::cerr << "Error: Failed to load background texture from Tiles/Mario_BG.JPG" << std::endl;
	background.setTexture(backgroundTexture);
	vertexArray.setPrimitiveType(Quads);
	vertexArray.resize(width * height * 4);
	importMapFromFile(mapFileLocation);
}

Map::Map()
{

}

Map::~Map()
{

}

void Map::moveViewRight(const bool isBoosted)
{
	if (isBoosted)
	{
		view.move(viewVelocity.x * 2, viewVelocity.y);
		background.move(viewVelocity.x * 2, viewVelocity.y);
	}
	else
	{
		view.move(viewVelocity);
		background.move(viewVelocity);
	}
}

void Map::moveViewLeft(const bool isBoosted)
{
	if (isBoosted)
	{
		view.move(-viewVelocity.x * 2, viewVelocity.y);
		background.move(-viewVelocity.x * 2, viewVelocity.y);
	}
	else
	{
		view.move(-viewVelocity.x, viewVelocity.y);
		background.move(-viewVelocity.x, viewVelocity.y);
	}
}

void Map::addTilesToVertexArray(const int x, const int y, Vector2f position)
{
	vertexArray.append(Vertex((Vector2f(0.0f, 0.0f) + position) * tileWorldDimension,
		Vector2f(tileTextureDimension * x, tileTextureDimension * y)));

	vertexArray.append(Vertex((Vector2f(1.0f, 0.0f) + position) * tileWorldDimension,
		Vector2f(tileTextureDimension * x + tileTextureDimension, tileTextureDimension * y)));

	vertexArray.append(Vertex((Vector2f(1.0f, 1.0f) + position) * tileWorldDimension,
		Vector2f(tileTextureDimension * x + tileTextureDimension, tileTextureDimension * y + tileTextureDimension)));

	vertexArray.append(Vertex((Vector2f(0.0f, 1.0f) + position)* tileWorldDimension,
		Vector2f(tileTextureDimension * x, tileTextureDimension * y + tileTextureDimension)));
}

void Map::importMapFromFile(const string mapFileLocation)
{
	ifstream fromFile;
	fromFile.open(mapFileLocation);
	int x = 0, y = 0, tileType;
	if (fromFile.is_open())
	{
		while (fromFile >> tileType)
		{
			tiles::AtlasCell cell = tiles::atlasCell(tileType);
			if (cell.x >= 0 && x < width && y < height)
				addTilesToVertexArray(cell.x, cell.y, Vector2f((float)x, (float)y));
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


void Map::draw(RenderTarget& target, RenderStates states) const
{
	target.setView(view);
	states.texture = &tileSet;
	target.draw(background, states);
	target.draw(vertexArray, states);
}