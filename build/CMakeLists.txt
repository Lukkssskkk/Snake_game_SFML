cmake_minimum_required(VERSION 3.10)
project(Snake_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/HEADER_FILES)

file(GLOB MAIN "${CMAKE_SOURCE_DIR}/../src/snake.cpp")
add_executable(Snake_game ${MAIN})


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
    target_link_libraries(Snake_game PRIVATE sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(Snake_game PRIVATE -lm -lpthread -lsfml-graphics -lsfml-window -lsfml-system -Wnarrowing)
endif()