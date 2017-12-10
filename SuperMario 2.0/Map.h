#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
/*
	Textures: 
		1. Background
		2. Ground-sheet
*/
using namespace std;
using namespace sf;
class Map : public Drawable
{
private:
	
	int width;
	int height;
	Texture *tileSet[2];
	VertexArray *vertexArray;
	Sprite background;
	float tileWorldDimension;
	float tileTextureDimension;
	void addTileVertices(Tile tile, Vector2f position);
	
public:
	Map(int width, int height, float tileTextureDimension, float tileWorldDimension);
	Map();
	~Map();
	void draw(RenderTarget& target, RenderStates states) const;
};

