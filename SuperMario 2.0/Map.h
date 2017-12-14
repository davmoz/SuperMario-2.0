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
	int width;
	int height;
	View view;
	Texture tileSet;
	Sprite background;
	VertexArray vertexArray;
	float tileWorldDimension;
	Texture backgroundTexture;
	float tileTextureDimension;
public:
	Map(int width, int height, float tileTextureDimension, float tileWorldDimension);
	Map();
	virtual ~Map();
	void moveViewRight();
	void moveViewLeft();
	void setBackgroundPos(const float x, const float y);
	void draw(RenderTarget& target, RenderStates states) const;
	void addTilesToVertexArray(const int x, const int y, Vector2f position);
};

