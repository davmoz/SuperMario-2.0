#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

// Loads each texture from disk at most once and hands out shared references.
// Previously every Character, Loot and Map loaded its own copy of the tileset,
// so a level decoded the same PNG dozens of times into dozens of GPU textures.
// The owner (Game) must outlive every sprite that references a texture from here.
class TextureManager
{
private:
	std::unordered_map<std::string, sf::Texture> cache;

public:
	const sf::Texture &get(const std::string &path);
};
