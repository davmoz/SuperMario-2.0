#include "Map.h"


Map::Map(int width, int height, float tileTextureDimension, float tileWorldDimension)
{
	this->view.setSize(sf::Vector2f(900, 600));
	this->view.setCenter(sf::Vector2f(450, 300));
	this->width = width;
	this->height = height;
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;
	this->tileSet.loadFromFile("Tiles/main.png");
	this->backgroundTexture.loadFromFile("Tiles/Mario_BG.JPG");
	this->background.setTexture(this->backgroundTexture);
	this->vertexArray.setPrimitiveType(Quads);
	this->vertexArray.resize(this->width * this->height * 4);
	this->importMapFromFile();
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
		this->view.move(2.0f * 2, 0.0f);
		this->background.move(2.0f * 2, 0.0f);
	}
	else
	{
		this->view.move(2.0f, 0.0f);
		this->background.move(2.0f, 0.0f);
	}
	
}

void Map::moveViewLeft(const bool isBoosted)
{
	if (isBoosted)
	{
		this->view.move(-2.0f * 2, 0.0f);
		this->background.move(-2.0f * 2, 0.0f);
	}
	else
	{
		this->view.move(-2.0f, 0.0f);
		this->background.move(-2.0f, 0.0f);
	}
}

void Map::addTilesToVertexArray(const int x, const int y, Vector2f position)
{
	this->vertexArray.append(Vertex((Vector2f(0.0f, 0.0f) + position) * this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * x, this->tileTextureDimension * y)));

	this->vertexArray.append(Vertex((Vector2f(1.0f, 0.0f) + position) * this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * x + this->tileTextureDimension, this->tileTextureDimension * y)));

	this->vertexArray.append(Vertex((Vector2f(1.0f, 1.0f) + position) * this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * x + this->tileTextureDimension, this->tileTextureDimension * y + this->tileTextureDimension)));

	this->vertexArray.append(Vertex((Vector2f(0.0f, 1.0f) + position)* this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * x, this->tileTextureDimension * y + this->tileTextureDimension)));
}

void Map::importMapFromFile()
{
	ifstream fromFile;
	fromFile.open("Coords.txt");
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
				this->addTilesToVertexArray(0, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 2: { // Blocks
				this->addTilesToVertexArray(1, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 3: { // LootBox
				this->addTilesToVertexArray(0, 3, Vector2f((float)x, (float)y));
				break;
			}
			case 4: { // Pipe-topLeft
				this->addTilesToVertexArray(2, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 5: { // Pipe-topRight
				this->addTilesToVertexArray(3, 0, Vector2f((float)x, (float)y));
				break;
			}
			case 6: { // Pipe-BottomLeft
				this->addTilesToVertexArray(2, 1, Vector2f((float)x, (float)y));
				break;
			}
			case 7: { // Pipe-BottomRight
				this->addTilesToVertexArray(3, 1, Vector2f((float)x, (float)y));
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
	target.draw(this->background, states);
	target.draw(vertexArray, states);
	target.setView(this->view);
}