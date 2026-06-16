#include "TextureManager.h"
#include <iostream>

// std::unordered_map guarantees that references to elements stay valid across
// inserts/rehashes, so the references returned here remain usable for the
// manager's lifetime.
const sf::Texture &TextureManager::get(const std::string &path)
{
	auto it = cache.find(path);
	if (it != cache.end())
		return it->second;

	sf::Texture &texture = cache[path];
	if (!texture.loadFromFile(path))
		std::cerr << "Error: Failed to load texture from " << path << std::endl;
	return texture;
}
