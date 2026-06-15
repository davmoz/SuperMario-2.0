# Known issues

## Intermittent crash on startup (macOS, Apple Silicon)

**Symptom:** the game occasionally crashes immediately on launch with
`EXC_BAD_ACCESS` / `SIGSEGV` before the window is usable. Re-launching works.

**Cause:** this is *not* a bug in the game. Homebrew's `sfml@2` audio library
links Apple's **deprecated `OpenAL.framework`**:

```
$ otool -L libsfml-audio.2.6.dylib | grep -i openal
    /System/Library/Frameworks/OpenAL.framework/.../OpenAL
```

Apple deprecated that framework in macOS 10.15 and it races inside CoreAudio's
HAL (`HAL_HardwarePlugIn_ObjectHasProperty` / `AudioDeviceGetPropertyInfo`)
when OpenAL first opens the audio device. The crash happens on the first sound
played, regardless of whether it is `sf::Music` or `sf::Sound`.

**Workarounds:**

- Use the retry launcher, which re-runs past a failed audio init:
  ```sh
  ./run.sh        # from the "SuperMario 2.0" directory
  ```
- Or simply launch again — a successful start runs normally for the whole
  session.

**Not affected:** Linux/CI builds, which use `openal-soft` (`libopenal-dev`)
instead of the Apple framework, do not exhibit this race.

A permanent fix requires SFML to link a modern `openal-soft` on macOS, which is
a packaging concern outside this repository's source.
