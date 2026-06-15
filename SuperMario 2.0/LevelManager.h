#pragma once
#include <string>
#include <vector>

// An ordered list of the game's levels and a cursor into it. Adding content is
// a matter of dropping a level data file in Levels/ and registering it here.
struct LevelInfo
{
	std::string file;
	std::string name;
};

class LevelManager
{
private:
	std::vector<LevelInfo> levels;
	int current = 0;

public:
	LevelManager();
	const std::string& currentFile() const;
	const std::string& currentName() const;
	int currentNumber() const;  // 1-based
	int count() const;
	bool hasNext() const;
	void advance();
	void reset();
};
