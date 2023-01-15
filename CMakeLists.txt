cmake_minimum_required(VERSION 3.24)
project(AoC21)

set(CMAKE_CXX_STANDARD 23)

add_library(Utl
        src/utilities.ixx
        )
target_include_directories(Utl PUBLIC libs)
target_link_directories(Utl PUBLIC libs)

add_library(Days
        src/days/day01.ixx
        src/days/day02.ixx
        src/days/day03.ixx
        src/days/day04.ixx
        src/days/day05.ixx
        src/days/day06.ixx
        src/days/day07.ixx
        src/days/day08.ixx
        src/days/day09.ixx
        src/days/day10.ixx
        src/days/day11.ixx
        src/days/day12.ixx
        src/days/day13.ixx
        src/days/day14.ixx
        src/days/day15.ixx
        src/days/day16.ixx
        src/days/day17.ixx
        src/days/day18.ixx
        src/days/day19.ixx
        src/days/day20.ixx
        src/days/day21.ixx
        src/days/day22.ixx
        src/days/day23.ixx
        src/days/day24.ixx
        src/days/day25.ixx
        )
target_include_directories(Days PUBLIC src)
target_link_directories(Days PUBLIC src)
target_link_libraries(Days PUBLIC Utl)

add_executable(AoC21
        src/advent.ixx
        src/args.ixx
        src/dataset.ixx
        src/main.cc
        )
target_include_directories(AoC21 PUBLIC libs src src/days)
target_link_directories(AoC21 PUBLIC libs src src/days)
target_link_libraries(AoC21 PUBLIC Utl Days)