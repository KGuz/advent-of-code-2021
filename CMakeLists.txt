cmake_minimum_required(VERSION 3.24)

project(AoC21)
set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        src/main.cc
        src/dataset.cc
        src/advent.cc
        src/parser.cc
        src/utils.cc
        )

set(HEADERS
        include/dataset.hh
        include/advent.hh
        include/parser.hh
        include/puzzle.hh
        include/utils.hh
        )

set(HEADERS_DAYS
        days/include/day01.hh
        days/include/day02.hh
        days/include/day03.hh
        days/include/day04.hh
        days/include/day05.hh
        days/include/day06.hh
        days/include/day07.hh
        days/include/day08.hh
        days/include/day09.hh
        days/include/day10.hh
        days/include/day11.hh
        days/include/day12.hh
        days/include/day13.hh
        days/include/day14.hh
        days/include/day15.hh
        days/include/day16.hh
        days/include/day17.hh
        days/include/day18.hh
        days/include/day19.hh
        days/include/day20.hh
        days/include/day21.hh
        days/include/day22.hh
        days/include/day23.hh
        days/include/day24.hh
        days/include/day25.hh
        )

set(SOURCES_DAYS
        days/src/day01.cc
        days/src/day02.cc
        days/src/day03.cc
        days/src/day04.cc
        days/src/day05.cc
        days/src/day06.cc
        days/src/day07.cc
        days/src/day08.cc
        days/src/day09.cc
        days/src/day10.cc
        days/src/day11.cc
        days/src/day12.cc
        days/src/day13.cc
        days/src/day14.cc
        days/src/day15.cc
        days/src/day16.cc
        days/src/day17.cc
        days/src/day18.cc
        days/src/day19.cc
        days/src/day20.cc
        days/src/day21.cc
        days/src/day22.cc
        days/src/day23.cc
        days/src/day24.cc
        days/src/day25.cc
        )

set(LIBS libs/pprint.hh)

include_directories(include)
include_directories(days/include)
include_directories(libs)

add_executable(AoC21 ${SOURCES} ${HEADERS} ${LIBS} ${SOURCES_DAYS} ${HEADERS_DAYS})

