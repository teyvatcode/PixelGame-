cmake_minimum_required(VERSION 3.20)
project(PixelGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(PIXELGAME_USE_BUNDLED_RAYLIB "Use third_party/raylib if present" ON)

# raylib dependency:
# - If your network blocks git clone from GitHub, you can download raylib into
#   third_party/raylib and the build will use it automatically.
if (PIXELGAME_USE_BUNDLED_RAYLIB AND EXISTS "${CMAKE_SOURCE_DIR}/third_party/raylib/CMakeLists.txt")
  message(STATUS "Using bundled raylib: third_party/raylib")
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
  add_subdirectory(third_party/raylib)
else()
  include(FetchContent)
  set(FETCHCONTENT_QUIET OFF)

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
  )

  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(raylib)
endif()

add_executable(PixelGame
  src/main.cpp
  src/core/Types.h
  src/world/Tile.h
  src/world/Level.h
  src/world/Level.cpp
  src/economy/Weapon.h
  src/economy/Weapon.cpp
  src/economy/Arsenal.h
  src/economy/Arsenal.cpp
  src/economy/Shop.h
  src/economy/Shop.cpp
  src/entity/Player.h
  src/entity/Player.cpp
  src/entity/Monster.h
  src/entity/Projectile.h
  src/entity/Projectile.cpp
  src/combat/CombatSystem.h
  src/combat/CombatSystem.cpp
  src/render/Renderer.h
  src/render/Renderer.cpp
  src/game/Scene.h
  src/game/Game.h
  src/game/Game.cpp
)

target_link_libraries(PixelGame PRIVATE raylib)

if (MSVC)
  target_compile_options(PixelGame PRIVATE /W4)
else()
  target_compile_options(PixelGame PRIVATE -Wall -Wextra -Wpedantic)
endif()

