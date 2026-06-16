cmake_minimum_required(VERSION 3.16)
project(SuperMario2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 2.x. On macOS the keg-only sfml@2 Homebrew formula isn't on the
# default search path, so add it there; on Linux the distro package is found
# directly.
if(APPLE)
    foreach(prefix /opt/homebrew/opt/sfml@2 /usr/local/opt/sfml@2)
        if(EXISTS "${prefix}")
            list(APPEND CMAKE_PREFIX_PATH "${prefix}")
        endif()
    endforeach()
endif()
find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)

# Source files
set(SOURCES
    SuperMario.cpp
    Game.cpp
    Collision.cpp
    Character.cpp
    Mario.cpp
    Enemy.cpp
    Map.cpp
    Loot.cpp
    Audio.cpp
    LevelManager.cpp
    Hud.cpp
    Boss.cpp
    TextureManager.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
)

# Copy resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Tiles"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Tiles"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Music"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Music"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Fonts"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Fonts"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Score"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Score"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Levels"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Levels"
)

# macOS only: SFML 2.6's audio links Apple's deprecated OpenAL.framework, which
# races in CoreAudio and crashes intermittently on launch. Ship a copy of
# libsfml-audio relinked against openal-soft beside the binary so the game uses
# a modern OpenAL instead. Requires `brew install openal-soft`.
if(APPLE)
    find_library(OPENAL_SOFT_LIB NAMES openal
        PATHS /opt/homebrew/opt/openal-soft/lib /usr/local/opt/openal-soft/lib
        NO_DEFAULT_PATH)
    if(OPENAL_SOFT_LIB)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND bash "${CMAKE_SOURCE_DIR}/cmake/use_openal_soft.sh"
                "$<TARGET_FILE:${PROJECT_NAME}>"
                "$<TARGET_FILE:sfml-audio>"
                "${OPENAL_SOFT_LIB}"
            VERBATIM
            COMMENT "Relinking libsfml-audio against openal-soft (macOS OpenAL.framework workaround)")
    else()
        message(WARNING "openal-soft not found - run 'brew install openal-soft' to avoid the intermittent macOS startup crash (see docs/KNOWN_ISSUES.md).")
    endif()
endif()

# Headless unit tests for the pure-logic parts (no SFML / GL context needed).
enable_testing()
add_executable(SuperMario2_tests tests/tests.cpp LevelManager.cpp)
target_include_directories(SuperMario2_tests PRIVATE "${CMAKE_SOURCE_DIR}")
add_test(NAME unit COMMAND SuperMario2_tests)
