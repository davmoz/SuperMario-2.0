# Super Mario 2.0

A 2D side-scrolling platformer written in C++17 with [SFML](https://www.sfml-dev.org/) 2.6.

![Snapshot while ingame](supermariosh.png)

## Build & run

See [docs/BUILD.md](docs/BUILD.md). In short, from the `SuperMario 2.0/` directory:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
cd build && ./SuperMario2
```

## Gameplay

Race through five worlds and Bowser's Fortress to reclaim the stolen Star.
Stomp enemies, grab coins, and collect power-ups: a **green mushroom** makes
you big (you survive one hit), a **red mushroom** boosts your speed, and a
**star** makes you briefly invincible. Reach the flag to finish a level — or
defeat the boss to win. You have three lives.

## Controls

| Key            | Action                      |
|----------------|-----------------------------|
| ← / →          | Move                        |
| Space          | Jump                        |
| Escape         | Pause / resume              |
| ↑ / ↓ + Enter  | Navigate menus              |
| Enter / Space  | Advance the title & story   |

## Documentation

- [Architecture](docs/DESIGN.md)
- [Roadmap](docs/ROADMAP.md)
- [Build guide](docs/BUILD.md)
- [Known issues](docs/KNOWN_ISSUES.md)

## Credits

Originally a school project. Tile and audio assets are the property of their
respective owners and are used here for educational purposes only.
