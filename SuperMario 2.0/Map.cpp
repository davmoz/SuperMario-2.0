#include "Map.h"

void Map::addTileVertices(Tile tile, Vector2f position)
{
	this->vertexArray->append(Vertex((Vector2f(0.0f, 0.0f) + position) * this->tileWorldDimension, 
		Vector2f(this->tileTextureDimension * tile.getX(), this->tileTextureDimension * tile.getY())));
	
	this->vertexArray->append(Vertex((Vector2f(1.0f, 0.0f) + position) * this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * tile.getX() + this->tileTextureDimension, this->tileTextureDimension * tile.getY())));
	
	this->vertexArray->append(Vertex((Vector2f(1.0f, 1.0f) + position) * this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * tile.getX() + this->tileTextureDimension, this->tileTextureDimension * tile.getY() + this->tileTextureDimension)));
	
	this->vertexArray->append(Vertex((Vector2f(0.0f, 1.0f) + position)* this->tileWorldDimension,
		Vector2f(this->tileTextureDimension * tile.getX(), this->tileTextureDimension * tile.getY() + this->tileTextureDimension)));
}

Map::Map(int width, int height, float tileTextureDimension, float tileWorldDimension)
{
	this->width = width;
	this->height = height;
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;
	this->vertexArray = new VertexArray();
	this->tileSet[0] = new Texture;
	this->tileSet[1] = new Texture;
	this->tileSet[0]->loadFromFile("Ground.png");
	this->tileSet[1]->loadFromFile("Mario_BG.JPG");
	this->tileSet[1]->setSmooth(true);
	this->background.setTexture(*tileSet[1]);
	this->vertexArray->setPrimitiveType(Quads);
	this->vertexArray->resize(this->width * this->height * 4);
	Tile tile = Tile(0, 0);
	for (int x = 0; x < this->width; x++)
	{
		this->addTileVertices(tile, Vector2f((float)x, 17.8));
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
	delete this->tileSet[0];
	delete this->tileSet[1];
	delete this->vertexArray;
}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	states.texture = this->tileSet[0];
	target.draw(background);
	target.draw(*vertexArray, states);
}
