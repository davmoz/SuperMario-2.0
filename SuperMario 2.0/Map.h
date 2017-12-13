#pragma once
#include <SFML/Graphics.hpp>
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
	int nrOfTiles = 2;
	int width;
	int height;
	Texture *tileSet;
	VertexArray vertexArray;
	Sprite background;
	View view;
	float tileWorldDimension;
	float tileTextureDimension;
public:
	Map(int width, int height, float tileTextureDimension, float tileWorldDimension);
	Map();
	virtual ~Map();
	void draw(RenderTarget& target, RenderStates states) const;
	void addTilesToVertexArray(const int x, const int y, Vector2f position);
	void moveViewRight();
	void moveViewLeft();
};

