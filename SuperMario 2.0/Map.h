#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;
class Map : public Drawable
{
private:
	int width;
	int height;
	View view;
	Vector2f viewVelocity;
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
	void moveViewRight(const bool isBoosted);
	void moveViewLeft(const bool isBoosted);
	void addTilesToVertexArray(const int x, const int y, Vector2f position);
	void importMapFromFile();
	void draw(RenderTarget& target, RenderStates states) const;
};