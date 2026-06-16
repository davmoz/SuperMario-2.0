# Architecture

Super Mario 2.0 is a 2D side-scrolling platformer built on SFML 2.6. This
document describes the current code structure. It is kept in sync with the
code as the game evolves.

## Module overview

| Class       | Responsibility |
|-------------|----------------|
| `Game`      | Top-level loop, window, event handling, the `GameState` machine, menus, and high-score I/O. Owns a `Collision` and a `LevelManager`. |
| `LevelManager` | The ordered list of levels and a cursor; hands out the current level file and advances between levels. |
| `Hud`       | The in-game heads-up display (level / coins / time / enemies), drawn in screen space so it stays fixed while the level scrolls. |
| `Collision` | Level container "god object": owns Mario, the map, and the enemy/loot arrays; runs all collision math, entity spawning from the map, and finish detection. |
| `Map`       | Renders the tiled world (a `sf::VertexArray`) plus a scrolling background; owns the camera `sf::View`. |
| `Character` | Base entity: texture/sprite, position/velocity, gravity, jumping, animation, and character-vs-character overlap classification. |
| `Mario`     | Player character: coins, time, enemies-killed, speed boost, HUD text, high-score persistence. |
| `Enemy`     | AI character: ground or flying, walks and reverses on wall collisions. Exposes `onStomped()`/`isBoss()` so subclasses can override stomp behaviour. |
| `Boss`      | `Enemy` subclass for the endgame: larger, tinted, and survives several stomps (HP); defeating it completes the boss level. |
| `Loot`      | A collectible: coin or power-up. |
| `Audio`     | Loads and plays music + sound effects. |
| `Constants` | Shared tunables (tile sizes, physics, boost, animation). |

## Game states

`Game` is driven by a single `GameState` enum (no overlapping booleans). Each
frame, events are dispatched by the current state and the screen is rendered
exactly once:

```
Title ──Enter──► Story ──Enter──► Playing
                                     │
Playing ──Esc──► PauseMenu ──Resume/Esc──► Playing
   │                 │
   │                 ├─Restart──► Playing (fresh level)
   │ death           ├─Highscore► Highscores ──Back──► (previous menu)
   │   │
   │   ▼
   │ Registration ──Enter(name)──► GameOverMenu ──New Game/Restart──► Playing
   │
   └ final-level finish ──► Victory ──Enter──► Registration

(finishing a non-final level advances straight to the next level)
```

## Data flow

```
main() -> Game(window) -> Collision(level files)
                              |-- Mario
                              |-- Map (view/camera + tiles)
                              |-- Enemy[]   (spawned from map tile 8)
                              |-- Loot[]    (spawned from map tiles -1 and 9)

Game::runGame() each frame:
  poll events -> update() (movement input)
              -> Collision::updateCharacter() (gravity, AI)
              -> Collision::moveEnemy()
              -> Collision::checkMario{Loot,Hostile,Finish}Collision()
              -> Collision::draw(window)
```

## Levels

Levels live in `Levels/` (`level1.txt`, `level2.txt`, …) and are registered, in
order, by `LevelManager`. `Game` asks the manager for the current level file
when it builds a `Collision`; reaching a finish flag advances to the next level
(carrying the run's coins/time/enemies forward via `PlayerStats`), and finishing
the last level records the score. `tools/gen_levels.py` generates the later
levels deterministically.

Each level file is a space-separated integer grid, **144 columns × 19 rows**. It
is loaded twice: by `Map` (to build the visible tiles) and by `Collision` (for
solidity and entity spawns). Both interpret the same encoding:

| Token        | Meaning |
|--------------|---------|
| `0`          | empty (non-solid) |
| `1`          | floor (solid) |
| `2`          | block (solid) |
| `3`          | loot box (solid, visual) |
| `4 5 6 7`    | pipe top-left / top-right / bottom-left / bottom-right (solid) |
| `8`          | enemy spawn |
| `9`          | block containing a power-up |
| `10`         | boss spawn |
| `-1`         | coin |
| `-3 -4 -5 -6`| flag / finish tiles (`-4` triggers level completion) |

## Coordinate system

- World tiles are `TILE_SIZE` (32 px) apart; the source atlas tiles are
  `TILE_TEXTURE_SIZE` (16 px) and drawn at 2× scale.
- Sprites use a centred origin (`TILE_TEXTURE_SIZE/2`), so `getPosition()`
  returns the sprite centre.

See [ROADMAP.md](ROADMAP.md) for the planned evolution of these systems.
