module;
#include <cassert>
#include <fstream>
#include <string>
export module dataset;

export namespace dataset {
auto input(int day, bool example) -> std::string {
    assert(day > 0 and day < 26);

    auto path = std::string("../dataset/");
    path += example ? "example" : "puzzle";
    path += (day < 10 ? "0" : "") + std::to_string(day) + ".txt";

    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}
}; // namespace dataset
