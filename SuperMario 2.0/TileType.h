#pragma once

// Single source of truth for the meaning of every integer in a level file.
// Both the renderer (Map) and the collision/spawn logic (Collision) consult
// this, so tile semantics can no longer drift between the two.
namespace tiles
{
	enum Tile : int
	{
		Empty          = 0,
		Floor          = 1,
		Block          = 2,
		LootBox        = 3,  // decorative solid block
		PipeTopLeft    = 4,
		PipeTopRight   = 5,
		PipeBottomLeft = 6,
		PipeBottomRight = 7,
		EnemySpawn     = 8,  // spawns an enemy; tile itself is empty
		BlockLoot      = 9,  // spawns a speed mushroom; tile itself is empty
		BossSpawn      = 10, // spawns the boss; tile itself is empty
		GrowSpawn      = 11, // spawns a grow mushroom; tile itself is empty
		StarSpawn      = 12, // spawns a star; tile itself is empty
		Coin           = -1, // spawns a coin; tile itself is empty
		FlagPole       = -3,
		Finish         = -4, // reaching this completes the level
		FlagMiddle     = -5,
		FlagTop        = -6
	};

	// A cell (column, row) in the 16-px tileset to draw for a tile.
	// {-1, -1} means the tile draws nothing (empty / pure spawn markers).
	struct AtlasCell { int x; int y; };

	inline AtlasCell atlasCell(int t)
	{
		switch (t)
		{
		case Floor:           return { 0, 0 };
		case Block:           return { 1, 0 };
		case LootBox:         return { 0, 3 };
		case PipeTopLeft:     return { 2, 0 };
		case PipeTopRight:    return { 3, 0 };
		case PipeBottomLeft:  return { 2, 1 };
		case PipeBottomRight: return { 3, 1 };
		case FlagPole:        return { 1, 6 };
		case Finish:          return { 2, 6 };
		case FlagMiddle:      return { 3, 6 };
		case FlagTop:         return { 4, 6 };
		default:              return { -1, -1 };
		}
	}

	// Everything blocks movement except empty space and the pure spawn markers
	// (enemy, power-up, coin), whose tiles are walkable.
	inline bool isSolid(int t)
	{
		return t != Empty && t != EnemySpawn && t != BlockLoot && t != BossSpawn
			&& t != GrowSpawn && t != StarSpawn && t != Coin;
	}

	inline bool isFinish(int t) { return t == Finish; }
}
