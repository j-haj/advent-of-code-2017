#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

long long compute_fuel_cost(long long weight) {
    return std::max(static_cast<long long>(weight / 3) - 2, 0LL);
}

long long total_fuel_requirements(const  std::vector<long long>& v,
                                  bool include_fuel_weight) {
    std::vector<long long> fuel_reqs(v.size());
    for (std::size_t i = 0; i < v.size(); ++i) {
        long long fuel = compute_fuel_cost(v[i]);
        long long weight = fuel;
        if (include_fuel_weight) {
            while (fuel > 0) {
                fuel = compute_fuel_cost(fuel);
                weight += fuel;
            }
        }
        fuel_reqs[i] = weight;
    }
    return std::accumulate(std::begin(fuel_reqs), std::end(fuel_reqs), 0);
}

int main() {
    std::vector<long long> input;
    for (std::string line; std::getline(std::cin, line);) {
        input.push_back(std::stol(line));
    }
    std::cout << "Part 1: " << total_fuel_requirements(input, false) << '\n'
              << "Part 2: " << total_fuel_requirements(input, true) <<  '\n';
    return 0;
}
