#!/usr/bin/env python3
"""Generate Super Mario 2.0 level grids.

A level is a 144x19 grid of integers matching the tile encoding in
SuperMario 2.0/TileType.h. Level 1 is the hand-made original (Coords.txt);
this script emits the later levels deterministically so they are valid by
construction (correct dimensions, walls, floor, a reachable finish flag) and
can be regenerated/tuned in one place.

Usage:  python3 tools/gen_levels.py
Writes: SuperMario 2.0/Levels/level2.txt, level3.txt
"""
import os

W, H = 144, 19          # columns, rows
FLOOR_TOP = 17          # rows 17 and 18 are the ground
GROUND_ROW = 16         # entities stand here, just above the floor
WALL = 1
EMPTY = 0
BLOCK = 2
LOOTBOX = 3
PIPE_TL, PIPE_TR, PIPE_BL, PIPE_BR = 4, 5, 6, 7
ENEMY = 8
BLOCKLOOT = 9           # power-up
BOSS = 10               # boss spawn
COIN = -1
FLAG_POLE = -3
FINISH = -4

START_COL = 5           # Mario spawns near here; keep it clear


def blank_grid():
    g = [[EMPTY for _ in range(W)] for _ in range(H)]
    # side walls
    for y in range(H):
        g[y][0] = g[y][1] = WALL
        g[y][W - 2] = g[y][W - 1] = WALL
    # solid ground
    for y in (FLOOR_TOP, FLOOR_TOP + 1):
        for x in range(W):
            g[y][x] = WALL
    return g


def carve_pit(g, x0, width):
    for x in range(x0, x0 + width):
        if 2 <= x < W - 2:
            for y in (FLOOR_TOP, FLOOR_TOP + 1):
                g[y][x] = EMPTY


def pipe(g, x, height):
    """A 2-wide pipe `height` tiles tall rising from the floor."""
    top = FLOOR_TOP - height
    g[top][x] = PIPE_TL
    g[top][x + 1] = PIPE_TR
    for y in range(top + 1, FLOOR_TOP):
        g[y][x] = PIPE_BL
        g[y][x + 1] = PIPE_BR


def coin_row(g, x0, count, row):
    for x in range(x0, x0 + count):
        if 2 <= x < W - 2:
            g[row][x] = COIN


def block_run(g, x0, pattern, row):
    for i, t in enumerate(pattern):
        x = x0 + i
        if 2 <= x < W - 2:
            g[row][x] = t


def enemy(g, x, row=GROUND_ROW):
    if 2 <= x < W - 2:
        g[row][x] = ENEMY


def place_finish(g, x):
    """Flag pole at column x, reachable, with solid ground beneath."""
    g[3][x - 1] = FLAG_POLE
    for y in range(3, FLOOR_TOP):
        g[y][x] = FINISH
    g[FLOOR_TOP][x] = WALL
    g[FLOOR_TOP][x - 1] = WALL


def render(g):
    return "\n".join(" ".join(str(v) for v in row) for row in g) + "\n"


def level2():
    """World 1-2 — pits and pipes, a step up from level 1."""
    g = blank_grid()
    enemy(g, 12)
    coin_row(g, 16, 4, 11)
    block_run(g, 16, [BLOCK, LOOTBOX, BLOCK], 12)
    pipe(g, 26, 2)
    enemy(g, 34)
    carve_pit(g, 40, 3)
    coin_row(g, 41, 2, 13)
    pipe(g, 50, 3)
    enemy(g, 56)
    enemy(g, 58)
    block_run(g, 62, [BLOCK, BLOCKLOOT, BLOCK], 11)
    carve_pit(g, 72, 4)
    coin_row(g, 73, 3, 12)
    pipe(g, 84, 2)
    enemy(g, 90)
    coin_row(g, 96, 5, 11)
    block_run(g, 100, [LOOTBOX, LOOTBOX], 12)
    carve_pit(g, 108, 3)
    enemy(g, 116)
    enemy(g, 118)
    pipe(g, 122, 4)
    coin_row(g, 128, 4, 13)
    place_finish(g, 138)
    return g


def level3():
    """World 1-3 — dense enemies and floating platforms; the run-up to harder
    challenges. Tuned tougher than level 2."""
    g = blank_grid()
    enemy(g, 10)
    enemy(g, 13)
    block_run(g, 14, [BLOCK, BLOCK, LOOTBOX, BLOCK, BLOCK], 11)
    coin_row(g, 14, 5, 9)
    carve_pit(g, 24, 3)
    pipe(g, 30, 3)
    enemy(g, 36)
    enemy(g, 38)
    enemy(g, 40)
    carve_pit(g, 46, 4)
    block_run(g, 52, [BLOCK, BLOCKLOOT, BLOCK], 10)
    coin_row(g, 52, 3, 8)
    pipe(g, 60, 4)
    enemy(g, 66)
    carve_pit(g, 70, 5)
    coin_row(g, 71, 4, 12)
    block_run(g, 80, [LOOTBOX, BLOCK, LOOTBOX], 11)
    enemy(g, 86)
    enemy(g, 88)
    pipe(g, 92, 2)
    pipe(g, 98, 3)
    carve_pit(g, 104, 4)
    enemy(g, 112)
    enemy(g, 114)
    enemy(g, 116)
    block_run(g, 120, [BLOCK, BLOCKLOOT, BLOCK], 9)
    coin_row(g, 126, 5, 11)
    place_finish(g, 138)
    return g


def level4():
    """Bowser's Fortress — the boss arena. Solid ground (no pits), a couple of
    minions, and the boss. There is no finish flag: defeating the boss ends the
    game."""
    g = blank_grid()
    # a few blocks for cover during the fight
    block_run(g, 30, [BLOCK, BLOCK, BLOCK], 12)
    block_run(g, 70, [BLOCK, BLOCK, BLOCK], 12)
    coin_row(g, 30, 3, 10)
    coin_row(g, 70, 3, 10)
    # minions guarding the boss
    enemy(g, 24)
    enemy(g, 60)
    enemy(g, 84)
    # the boss, standing on the ground in the right half of the arena
    g[GROUND_ROW][104] = BOSS
    return g


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    out_dir = os.path.join(here, "..", "SuperMario 2.0", "Levels")
    os.makedirs(out_dir, exist_ok=True)
    for name, g in (("level2.txt", level2()), ("level3.txt", level3()),
                    ("level4.txt", level4())):
        path = os.path.join(out_dir, name)
        with open(path, "w") as f:
            f.write(render(g))
        assert len(g) == H and all(len(r) == W for r in g), "bad dimensions"
        print("wrote", os.path.normpath(path))


if __name__ == "__main__":
    main()
