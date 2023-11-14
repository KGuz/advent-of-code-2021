cmake_minimum_required(VERSION 3.24)
project(aoc)

set(CMAKE_CXX_STANDARD 23)

add_library(utl
        src/utilities/utl.hh
        src/utilities/utl.cc
        )
target_include_directories(utl PUBLIC libs)
target_link_directories(utl PUBLIC libs)

add_library(advent
        src/advent/advent.hh
        src/advent/day01.cc
        src/advent/day02.cc
        src/advent/day03.cc
        src/advent/day04.cc
        src/advent/day05.cc
        src/advent/day06.cc
        src/advent/day07.cc
        src/advent/day08.cc
        src/advent/day09.cc
        src/advent/day10.cc
        src/advent/day11.cc
        src/advent/day12.cc
        src/advent/day13.cc
        src/advent/day14.cc
        src/advent/day15.cc
        src/advent/day16.cc
        src/advent/day17.cc
        src/advent/day18.cc
        src/advent/day19.cc
        src/advent/day20.cc
        src/advent/day21.cc
        src/advent/day22.cc
        src/advent/day23.cc
        src/advent/day24.cc
        src/advent/day25.cc
        )
target_link_libraries(advent PUBLIC utl)
target_include_directories(advent PUBLIC src/utilities)
target_link_directories(advent PUBLIC src/utilities)

add_executable(aoc 
        src/aoc/args.hh
        src/aoc/assets.hh
        src/aoc/main.cc
        )
target_link_libraries(aoc PUBLIC advent)
target_include_directories(aoc PUBLIC libs src/aoc src/advent)
target_link_directories(aoc PUBLIC libs src/aoc src/advent)
