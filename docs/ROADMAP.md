# Roadmap

The path from the original school-project prototype to a production-ready
platformer. Items are dependency-ordered; each is delivered as its own PR that
must compile (enforced by CI) and keep the docs in sync.

Status: ☐ todo · ◐ in progress · ☑ done

## Phase 0 — Infrastructure
- ☑ **CI + build hygiene** — GitHub Actions (Ubuntu + macOS), portable CMake, `.gitignore`, docs.

## Phase 1 — Correctness (bug fixes, no big refactor)
- ☐ **Critical bug sweep** — uninitialised members; `expandArray` value-init; enemy fall cleanup; remove double-camera scroll; stomp detection via velocity + bounds; no-op/dead code.
- ☐ **Input & high-score fixes** — fix text entry (unicode vs scancode), make registration commit + transition, read the real high-score count, guard malformed files.

## Phase 2 — Foundation refactors
- ☐ **`GameState` enum** — replace the four-boolean state soup with one state machine.
- ☐ **`TileType` registry** — one source of truth for tile semantics (sprite, solidity, finish, spawn), shared by `Map` and `Collision`.
- ☐ **`LevelManager`** — load multiple level data files; explicit per-level dimensions; level progression.

## Phase 3 — Core systems
- ☐ **Lives + checkpoints + respawn.**
- ☐ **Score + persistent screen-space HUD + level-complete results screen.**
- ☐ **Mario power-state machine** (small / big / star invincibility).
- ☐ **Power-up system** (coin, speed, grow, fire, star, 1-up) via polymorphic `onCollect`.

## Phase 4 — Enemies & combat
- ☐ **Enemy hierarchy + deterministic AI** (Goomba, Koopa, flyer, spiky).
- ☐ **Projectiles / fireballs.**

## Phase 5 — Content, endgame & narrative
- ☐ **Multiple authored levels + difficulty curve.**
- ☐ **Boss enemy + endgame arena.**
- ☐ **Title screen + story/cutscene + win/credits flow.**

## Phase 6 — Polish & robustness
- ☐ **UI/HUD module** decoupled from shared menu slots.
- ☐ **Resource manager + smart pointers** (shared textures, `vector<unique_ptr>`).
- ☐ **Save/progression persistence + externalised config.**

## Design principle

Once the `GameState` enum, `TileType` registry, and `LevelManager` exist, new
content (levels, the boss arena, cutscenes) becomes **data files plus small
subclasses** — never edits to the main loop. That is what keeps the codebase
from regressing into magic-number / boolean spaghetti.
