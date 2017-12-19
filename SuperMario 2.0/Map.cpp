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

void Map::importMap()
{
	ifstream fromFile;
	fromFile.open("Coords.txt");
	int x = 0, y = 0, tileType;
	if (fromFile.is_open())
	{
		while (!fromFile.eof())
		{
			cout << "x: " << x << "y: " << y << endl;
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
			case 8: {
				this->addTilesToVertexArray(1, 1, Vector2f((float)x, (float)y));
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
	else
	{
		cout << "nope";
	}
	fromFile.close();
}

void Map::moveViewRight()
{
	this->view.move(2.5f, 0.0f);
}

void Map::moveViewLeft()
{
	this->view.move(-2.5f, 0.0f);
}

void Map::setBackgroundPos(const float x, const float y)
{
	this->background.setPosition(x, y);
}

Map::Map(int width, int height, float tileTextureDimension, float tileWorldDimension)
{
	this->view.setSize(sf::Vector2f(900, 600));
	this->view.setCenter(sf::Vector2f(450, 300));
	this->width = width;
	this->height = height;
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;
	this->tileSet.loadFromFile("WOW.png");
	this->backgroundTexture.loadFromFile("Mario_BG.JPG");
	this->background.setTexture(this->backgroundTexture);
	this->vertexArray.setPrimitiveType(Quads);
	this->vertexArray.resize(this->width * this->height * 4);
	importMap();
	/*for (int x = 0; x < this->width; x++)
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
		this->addTilesToVertexArray(0, 0, Vector2f((float)x, 17.8));*/
		/*for (int y = 0; y < this->height; y++)
		{
			
		}*/
	//}
}

Map::Map()
{

}


Map::~Map()
{

}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	states.texture = &tileSet;
	target.draw(this->background, states);
	target.draw(vertexArray, states);
	target.setView(this->view);
}