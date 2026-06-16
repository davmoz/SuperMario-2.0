#include "LevelManager.h"

LevelManager::LevelManager()
{
	levels = {
		{ "Levels/level1.txt", "World 1-1" },
		{ "Levels/level2.txt", "World 1-2" },
		{ "Levels/level3.txt", "World 1-3" },
		{ "Levels/level4.txt", "Bowser's Fortress" },
	};
}

const std::string& LevelManager::currentFile() const { return levels[current].file; }
const std::string& LevelManager::currentName() const { return levels[current].name; }
int LevelManager::currentNumber() const { return current + 1; }
int LevelManager::count() const { return static_cast<int>(levels.size()); }
bool LevelManager::hasNext() const { return current + 1 < static_cast<int>(levels.size()); }
void LevelManager::advance() { if (hasNext()) current++; }
void LevelManager::reset() { current = 0; }
