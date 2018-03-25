#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

int matching_sum(const std::string& digits) {
  size_t n = digits.size();
  int sum{0};
  for (size_t i = 0; i < n; ++i) {
    if (i < n - 1 && (digits[i] == digits[i + 1]))
      sum += digits[i] - '0';
    else if (i == n - 1 && (digits[n - 1] == digits[0]))
      sum += digits[n - 1] - '0';
  }
  return sum;
}

void run_tests() {
  std::unordered_map<std::string, int> tests = {
      {"1111", 4}, {"1234", 0}, {"91212129", 9}, {"1122", 3}};
  for (const auto& p : tests) {
    const auto expected = p.second;
    const auto actual = matching_sum(p.first);
    if (actual == expected) {
      std::cout << "[PASS]: " << p.first << '\n';
    } else {
      std::cout << "[FAIL]: " << p.first << '\n';
      std::cout << "\tExpected: " << expected << '\n'
                << "\tGot: " << actual << '\n';
    }
  }
}

int main(int argc, char* argv[]) {
  std::string input;
  std::cin >> input;
  std::cout << "Answer: " << matching_sum(input) << '\n';
  return 0;
}
