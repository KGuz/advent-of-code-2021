#include "advent.hh"
#include "utl.hh"

namespace {
auto to_bitset(const std::string& s) -> std::vector<bool> {
    return utl::to_vector(s | views::transform([](auto c) { return static_cast<bool>(c - '0'); }));
}

auto negate(const std::vector<bool>& bits) -> std::vector<bool> {
    return utl::to_vector(bits | views::transform([](const auto bit) { return !bit; }));
}

auto to_int(const std::vector<bool>& bits) -> int {
    return std::accumulate(
        bits.begin(), bits.end(), 0, [](int acc, int bit) { return (acc << 1) + bit; });
}

auto most_common_bits(const std::vector<std::vector<bool>>& bitsets) -> std::vector<bool> {
    auto ones = std::vector<int>(bitsets[0].size());
    for (const auto& b : bitsets) {
        std::transform(ones.begin(), ones.end(), b.begin(), ones.begin(), std::plus<>());
    }
    return utl::to_vector(
        ones | views::transform([&](const auto& b) { return b >= bitsets.size() - b; }));
}

auto least_common_bits(const std::vector<std::vector<bool>>& bitsets) -> std::vector<bool> {
    return negate(most_common_bits(bitsets));
}

auto reduce_common_bits(const std::vector<std::vector<bool>>& bitsets, auto tactics)
    -> std::vector<bool> {
    auto res = std::vector<std::vector<bool>>(bitsets);
    for (auto n = 0; res.size() > 1; ++n) {
        auto common_bits = tactics(res);
        auto filtered =
            res | views::filter([&](const auto& bits) { return bits[n] == common_bits[n]; });
        res = utl::to_vector(filtered);
    }
    return res[0];
}
} // namespace

auto advent::Day03::part_one(const std::string& input) -> std::string {
    auto bitsets = utl::to_vector(views::transform(utl::lines(input), to_bitset));

    auto gamma_rate = most_common_bits(bitsets);
    auto epsilon_rate = negate(gamma_rate);

    return std::to_string(to_int(gamma_rate) * to_int(epsilon_rate));
}

auto advent::Day03::part_two(const std::string& input) -> std::string {
    auto bitsets = utl::to_vector(views::transform(utl::lines(input), to_bitset));

    auto oxygen_rating = reduce_common_bits(bitsets, most_common_bits);
    auto scrubber_rating = reduce_common_bits(bitsets, least_common_bits);

    return std::to_string(to_int(oxygen_rating) * to_int(scrubber_rating));
}
