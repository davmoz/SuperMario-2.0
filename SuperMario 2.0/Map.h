#pragma once
#include <SFML/Graphics.hpp>
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
	Map(const int width, const int height, const float tileTextureDimension, const float tileWorldDimension, const string mapFileLocation, const string tileFileLocation);
	Map();
	virtual ~Map();
	void moveViewRight(const bool isBoosted);
	void moveViewLeft(const bool isBoosted);
	void addTilesToVertexArray(const int x, const int y, Vector2f position);
	void importMapFromFile(const string mapFileLocation);
	void draw(RenderTarget& target, RenderStates states) const;
};