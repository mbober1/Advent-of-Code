cmake_minimum_required(VERSION 3.20)

project(AoC LANGUAGES CXX)
option(Day "Day" "All")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -pedantic -Wshadow -Wold-style-cast -Wunused -Wsign-conversion -Wuseless-cast -Wdouble-promotion -Wduplicated-cond -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wformat=2 -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -pedantic -Wshadow -Wold-style-cast -Wunused -O3 -DNDEBUG ")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(utils)
add_executable(${PROJECT_NAME} 2024/src/day_${Day}.cpp)
include_directories(utils)
target_link_libraries(${PROJECT_NAME} PUBLIC utils)
