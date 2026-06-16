#!/usr/bin/env bash
# Ship a copy of libsfml-audio relinked against openal-soft next to the
# executable, so the game never touches Apple's deprecated, crash-prone
# OpenAL.framework (see docs/KNOWN_ISSUES.md). Invoked as a CMake POST_BUILD
# step on macOS. Idempotent: safe to re-run on every build.
#
# Args:
#   $1 = path to the built executable
#   $2 = path to the real libsfml-audio dylib (from SFML)
#   $3 = path to openal-soft's libopenal dylib
set -euo pipefail

EXE="$1"
SFML_AUDIO="$2"
OPENAL="$3"
EXE_DIR="$(cd "$(dirname "$EXE")" && pwd)"
LOCAL="$EXE_DIR/libsfml-audio.2.6.dylib"

# Local, writable copy of libsfml-audio pointed at openal-soft.
cp -f "$SFML_AUDIO" "$LOCAL"
chmod u+w "$LOCAL"
framework=$(otool -L "$LOCAL" | awk '/OpenAL\.framework/{print $1; exit}')
if [ -n "${framework:-}" ]; then
	install_name_tool -change "$framework" "$OPENAL" "$LOCAL"
fi
install_name_tool -id @rpath/libsfml-audio.2.6.dylib "$LOCAL"
codesign --force --sign - "$LOCAL"

# Point the freshly-linked executable at the local copy beside it.
current=$(otool -L "$EXE" | awk '/libsfml-audio/{print $1; exit}')
if [ "$current" != "@loader_path/libsfml-audio.2.6.dylib" ]; then
	install_name_tool -change "$current" @loader_path/libsfml-audio.2.6.dylib "$EXE"
fi
codesign --force --sign - "$EXE"

echo "Relinked libsfml-audio against openal-soft: $OPENAL"
