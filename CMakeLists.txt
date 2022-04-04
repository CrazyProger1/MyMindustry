cmake_minimum_required(VERSION 3.20)
project(MyMindustry)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "externals/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(${PROJECT_NAME} code/main.cpp code/game/game.h code/engine/srcs/managers/LoggingManager.cpp code/engine/include/managers/LoggingManager.h code/engine/include/types.h code/engine/srcs/GameCore.cpp code/engine/include/GameCore.h code/engine/engine.h code/engine/srcs/managers/ScenesManager.cpp code/engine/include/managers/ScenesManager.h code/engine/srcs/Scene.cpp code/engine/include/Scene.h code/engine/srcs/managers/EntitiesManager.cpp code/engine/include/managers/EntitiesManager.h code/engine/srcs/managers/MemoryManager.cpp code/engine/include/managers/MemoryManager.h code/engine/srcs/Entity.cpp code/engine/include/Entity.h code/engine/srcs/GUI/Button.cpp code/engine/include/GUI/Button.h code/engine/srcs/GUI/Text.cpp code/engine/include/GUI/Text.h)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} stdc++fs)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)