// Lightweight headless unit tests for the pure-logic parts of the game (no
// SFML / GL context needed), so they run anywhere including CI.
#include "TileType.h"
#include "LevelManager.h"

#include <iostream>
#include <string>

static int failures = 0;

#define CHECK(cond)                                                       \
	do {                                                                  \
		if (!(cond)) {                                                    \
			std::cerr << "FAIL: " << #cond << " (" << __FILE__ << ":"     \
			          << __LINE__ << ")\n";                               \
			++failures;                                                   \
		}                                                                 \
	} while (0)

static void testTileSolidity()
{
	using namespace tiles;
	// Spawn markers and empty space are walkable.
	CHECK(!isSolid(Empty));
	CHECK(!isSolid(Coin));
	CHECK(!isSolid(EnemySpawn));
	CHECK(!isSolid(BlockLoot));
	CHECK(!isSolid(BossSpawn));
	CHECK(!isSolid(GrowSpawn));
	CHECK(!isSolid(StarSpawn));
	// Structure tiles block movement.
	CHECK(isSolid(Floor));
	CHECK(isSolid(Block));
	CHECK(isSolid(LootBox));
	CHECK(isSolid(PipeTopLeft));
	CHECK(isSolid(Finish));
}

static void testFinish()
{
	using namespace tiles;
	CHECK(isFinish(Finish));
	CHECK(!isFinish(Floor));
	CHECK(!isFinish(Empty));
	CHECK(!isFinish(FlagPole));
}

static void testAtlasCells()
{
	using namespace tiles;
	CHECK(atlasCell(Floor).x == 0 && atlasCell(Floor).y == 0);
	CHECK(atlasCell(Block).x == 1 && atlasCell(Block).y == 0);
	// Pure spawn markers draw nothing.
	CHECK(atlasCell(EnemySpawn).x == -1);
	CHECK(atlasCell(Coin).x == -1);
	CHECK(atlasCell(Empty).x == -1);
}

static void testLevelManager()
{
	LevelManager lm;
	CHECK(lm.count() >= 2);
	CHECK(lm.currentNumber() == 1);
	CHECK(!lm.currentName().empty());
	CHECK(lm.hasNext());

	// Walk to the last level.
	int guard = 0;
	while (lm.hasNext() && guard++ < 100)
		lm.advance();
	CHECK(!lm.hasNext());
	CHECK(lm.currentNumber() == lm.count());

	// advance() past the end is a no-op.
	const int last = lm.currentNumber();
	lm.advance();
	CHECK(lm.currentNumber() == last);

	lm.reset();
	CHECK(lm.currentNumber() == 1);
}

int main()
{
	testTileSolidity();
	testFinish();
	testAtlasCells();
	testLevelManager();

	if (failures == 0)
	{
		std::cout << "All tests passed.\n";
		return 0;
	}
	std::cerr << failures << " test(s) failed.\n";
	return 1;
}
