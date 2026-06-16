# Known issues

## macOS startup crash — fixed via openal-soft

**History:** the game used to crash intermittently on launch on macOS (Apple
Silicon) with `EXC_BAD_ACCESS` before the window was usable.

**Cause:** Homebrew's `sfml@2` audio library links Apple's **deprecated
`OpenAL.framework`**, which races inside CoreAudio's HAL
(`AudioDeviceGetPropertyInfo`) when OpenAL first opens the audio device.

**Fix (automatic):** the macOS build now ships a copy of `libsfml-audio`
relinked against **openal-soft** next to the binary, so the game never touches
the Apple framework. Just install openal-soft once:

```sh
brew install openal-soft
```

CMake detects it and applies the relink as a post-build step
(`cmake/use_openal_soft.sh`). You can confirm the framework is gone:

```sh
otool -L build/SuperMario2 build/libsfml-audio.2.6.dylib | grep -i OpenAL.framework   # no output
```

If openal-soft is **not** installed, CMake prints a warning and the game falls
back to the system framework (and the old intermittent crash). The bundled
`run.sh` retry launcher remains as a fallback for that case.

**Not affected:** Linux/CI uses `openal-soft` (`libopenal-dev`) already.
