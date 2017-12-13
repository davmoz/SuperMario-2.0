#include "Map.h"

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

void Map::moveViewRight()
{
	this->view.move(0.5f, 0.0f);
}

void Map::moveViewLeft()
{
	this->view.move(-0.5f, 0.0f);
}

Map::Map(int width, int height, float tileTextureDimension, float tileWorldDimension)
{
	this->view.setSize(sf::Vector2f(900, 600));
	this->view.setCenter(sf::Vector2f(450, 300));

	this->width = width;
	this->height = height;
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;

	this->tileSet = new Texture[this->nrOfTiles];
	this->tileSet[0].loadFromFile("Ground.png");
	this->tileSet[1].loadFromFile("Mario_BG.JPG");
	this->tileSet[1].setRepeated(true);
	this->tileSet[1].setSmooth(true);
	this->background.setTexture(tileSet[1]);
	this->vertexArray.setPrimitiveType(Quads);
	this->vertexArray.resize(this->width * this->height * 4);

	for (int x = 0; x < this->width; x++)
	{
		if (x >= 8 && x <= 13)
		{
			if (x == 10)
			{
				this->addTilesToVertexArray(1, 0, Vector2f((float)x, 10.8));
			}
			else
			{
				this->addTilesToVertexArray(1, 1, Vector2f((float)x, 10.8));
			}
		}
		if (x == 25)
		{
			this->addTilesToVertexArray(2, 0, Vector2f((float)x, 14.8));
			this->addTilesToVertexArray(2, 1, Vector2f((float)x, 15.8));
		}
		else if (x == 26)
		{
			this->addTilesToVertexArray(3, 0, Vector2f((float)x, 14.8));
			this->addTilesToVertexArray(3, 1, Vector2f((float)x, 15.8));
		}
		this->addTilesToVertexArray(0, 0, Vector2f((float)x, 16.8));
		this->addTilesToVertexArray(0, 0, Vector2f((float)x, 17.8));
		/*for (int y = 0; y < this->height; y++)
		{
			
		}*/
	}
}

Map::Map()
{
}


Map::~Map()
{

}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	states.texture = &tileSet[0];
	target.draw(this->background);
	target.draw(this->vertexArray, states);
	target.setView(this->view);
}