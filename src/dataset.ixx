module;
#include <cassert>
#include <fstream>
#include <string>

export module dataset;
using namespace std;

export struct Dataset {
    static auto get(int day, bool example) -> string {
        assert(day > 0 and day < 26);

        auto path = string("../dataset/");
        path += example ? "example" : "puzzle";
        path += (day < 10 ? "0" : "") + to_string(day) + ".txt";

        auto f = ifstream(path);
        return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    }
};
