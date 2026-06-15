#!/usr/bin/env bash
# Launch the game from the build directory, retrying past the intermittent
# macOS startup crash caused by SFML 2.6 linking Apple's deprecated
# OpenAL.framework (see docs/KNOWN_ISSUES.md). On Linux this just runs once.
set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
BIN="$HERE/build/SuperMario2"
ATTEMPTS="${1:-8}"

if [[ ! -x "$BIN" ]]; then
	echo "Build first: cmake -S '$HERE' -B '$HERE/build' && cmake --build '$HERE/build'" >&2
	exit 1
fi

cd "$HERE/build" || exit 1
for ((i = 1; i <= ATTEMPTS; i++)); do
	./SuperMario2 &
	pid=$!
	sleep 2
	if kill -0 "$pid" 2>/dev/null; then
		wait "$pid"
		exit $?
	fi
	wait "$pid"
	echo "Audio-init crash on launch $i/$ATTEMPTS, retrying..." >&2
done
echo "Gave up after $ATTEMPTS attempts (see docs/KNOWN_ISSUES.md)." >&2
exit 1
