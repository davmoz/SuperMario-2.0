#pragma once
class Tile
{
private:
	float x;
	float y;
public:
	Tile(const float x, const float y);
	~Tile();
	int getX() const;
	int getY() const;
	void setX(const float x);
	void setY(const float y);
};

