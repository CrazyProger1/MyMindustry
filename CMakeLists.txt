cmake_minimum_required(VERSION 3.20)
project(MyMindustry)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "externals/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} stdc++fs)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)