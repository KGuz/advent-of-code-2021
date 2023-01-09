#pragma once

#include <tuple>

auto parse_arguments(int argc, char **argv) -> std::tuple<int, bool>;