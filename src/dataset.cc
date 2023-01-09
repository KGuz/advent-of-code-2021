#include "dataset.hh"
#include <cassert>
#include <fstream>
#include <string>

using std::ifstream;
using std::istreambuf_iterator;
using std::string;

auto Dataset::get(int day, bool example) -> std::string {
    assert(day > 0 and day < 26);

    auto path = string("C:/Users/kamil/Projekty/AdventOfCode/AoC21/dataset/");
    path += example ? "example" : "puzzle";
    path += (day < 10 ? "0" : "") + std::to_string(day) + ".txt";

    auto f = ifstream(path);
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}

auto Dataset::operator[](std::pair<int, bool> index) -> std::string { return this->get(index.first, index.second); }
