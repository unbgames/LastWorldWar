# Using the lastest version available for CMake to date
cmake_minimum_required(VERSION 3.8)

# Project's name
project(LastWorldWar)

# Get all .cpp files and set they to the source code
file(GLOB SOURCE_FILES *.cpp *.h)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Set the libraries - Must have
find_package(SDL REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Set compiler flags
set(CMAKE_CXX_FLAGS "sdl-config --cflags --libs -Wall -W -pedantic -ansi -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_net -std=c++0x -o -g")

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

# Run the executable
add_executable(LastWorldWar ${SOURCE_FILES})
target_link_libraries(LastWorldWar ${SDL_LIBRARY})
