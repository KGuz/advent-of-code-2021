cmake_minimum_required(VERSION 3.24)

project(AoC21)
set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        src/dataset.ixx
        src/advent/advent.ixx
        src/parser.ixx
        src/main.cc
        )

set(DAYS
        src/advent/puzzle.hh
        src/advent/day01.ixx
        src/advent/day02.ixx
        src/advent/day03.ixx
        src/advent/day04.ixx
        src/advent/day05.ixx
        src/advent/day06.ixx
        src/advent/day07.ixx
        src/advent/day08.ixx
        src/advent/day09.ixx
        src/advent/day10.ixx
        src/advent/day11.ixx
        src/advent/day12.ixx
        src/advent/day13.ixx
        src/advent/day14.ixx
        src/advent/day15.ixx
        src/advent/day16.ixx
        src/advent/day17.ixx
        src/advent/day18.ixx
        src/advent/day19.ixx
        src/advent/day20.ixx
        src/advent/day21.ixx
        src/advent/day22.ixx
        src/advent/day23.ixx
        src/advent/day24.ixx
        src/advent/day25.ixx
        )

include_directories(libs)

add_executable(AoC21
        libs/pprint.hh
        src/utilities.ixx
        ${DAYS}
        ${SOURCES}
        )