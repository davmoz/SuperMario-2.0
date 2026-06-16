# Roadmap

The path from the original school-project prototype to a production-ready
platformer. Each item was delivered as its own PR that compiles (enforced by
CI) and keeps the docs in sync.

Status: ☐ todo · ◐ in progress · ☑ done

## Phase 0 — Infrastructure
- ☑ **CI + build hygiene** — GitHub Actions (Ubuntu + macOS), portable CMake, `.gitignore`, docs.
- ☑ **Headless unit tests** run in CI (`ctest`).

## Phase 1 — Correctness
- ☑ **Critical bug sweep** — uninitialised members; stale `getPosition`; `expandArray` value-init; enemy fall cleanup; stomp detection via velocity + bounds; no-op/dead code.
- ☑ **Input & high-score fixes** — text entry (unicode vs scancode), registration commit + transition, real high-score count, malformed-file guards.
- ☑ **Audio** — buffered SFX vs streamed theme; macOS OpenAL crash documented.

## Phase 2 — Foundation refactors
- ☑ **`GameState` machine** — replaces the four-boolean state soup.
- ☑ **`TileType` registry** — one source of truth for tile semantics, shared by `Map` and `Collision`.
- ☑ **`LevelManager`** — multiple level data files; level progression with carried stats.

## Phase 3 — Core systems
- ☑ **Lives + respawn** (checkpoints pending).
- ☑ **Score + screen-space HUD + victory results screen.**
- ☑ **Mario power state** (small / big / star invincibility).
- ☑ **Power-up system** (coin, speed, grow, star; typed via `LootType`).

## Phase 4 — Enemies & combat
- ☑ **Frame-rate-independent flying enemy.**
- ☐ **Further enemy variety** (shells/spiky) and **projectiles / fireballs.**

## Phase 5 — Content, endgame & narrative
- ☑ **Multiple authored levels + difficulty curve** (6 levels incl. boss).
- ☑ **Boss enemy + endgame arena.**
- ☑ **Title screen + story intro + victory flow.**

## Phase 6 — Polish & robustness
- ☑ **`Hud` module** decoupled from the menu slots; screen-space menus + pause overlay.
- ☑ **Resource manager + smart pointers** — shared `TextureManager`, `vector<unique_ptr>` entities.
- ☐ **Save/progression persistence + externalised config.**

## Backlog (nice-to-have)
- Mid-level checkpoints.
- Fire flower + projectiles; more enemy archetypes.
- Persisted progression / unlocks and tunables in a config file.

## Design principle

With the `GameState` machine, the `TileType` registry, and the `LevelManager`
in place, new content (levels, the boss arena, cutscenes) is **data files plus
small subclasses** — never edits to the main loop. That is what keeps the
codebase from regressing into magic-number / boolean spaghetti.
