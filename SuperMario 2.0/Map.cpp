#include "Map.h"


Map::Map(const int width, const int height, const float tileTextureDimension, const float tileWorldDimension, const string mapFileLocation, const string tileFileLocation)
{
	view.setSize(sf::Vector2f(900, 600));
	view.setCenter(sf::Vector2f(450, 300));
	this->width = width;
	this->height = height;
	viewVelocity = Vector2f(2.0f, 0.0f);
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;
	tileSet.loadFromFile(tileFileLocation);
	backgroundTexture.loadFromFile("Tiles/Mario_BG.JPG");
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
		while (!fromFile.eof())
		{
			fromFile >> tileType;
			fromFile.ignore();
			switch (tileType)
			{
			case 1: { // Floor
				addTilesToVertexArray(0, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 2: { // Blocks
				addTilesToVertexArray(1, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 3: { // LootBox
				addTilesToVertexArray(0, 3, Vector2f((float)x, (float)y));
				break;
			}
			case 4: { // Pipe-topLeft
				addTilesToVertexArray(2, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 5: { // Pipe-topRight
				addTilesToVertexArray(3, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 6: { // Pipe-BottomLeft
				addTilesToVertexArray(2, 1, Vector2f((float)x, (float)y));
				break;
			}
			case 7: { // Pipe-BottomRight
				addTilesToVertexArray(3, 1, Vector2f((float)x, (float)y));
				break;
			}
			case -3: {
				addTilesToVertexArray(1, 6, Vector2f((float)x, (float)y));
				break;
			}
			case -4: {
				addTilesToVertexArray(2, 6, Vector2f((float)x, (float)y));
				break;
			}
			case -5: {
				addTilesToVertexArray(3, 6, Vector2f((float)x, (float)y));
				break;
			}
			case -6: {
				addTilesToVertexArray(4, 6, Vector2f((float)x, (float)y));
				break;
			}
			default:

				break;
			}
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


void Map::draw(RenderTarget& target, RenderStates states) const
{
	target.setView(view);
	states.texture = &tileSet;
	target.draw(background, states);
	target.draw(vertexArray, states);
	target.setView(view);
}