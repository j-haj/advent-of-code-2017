#include <cctype>
#include <exception>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

class IntCodeProgram {
public:
    IntCodeProgram(const std::vector<int>& s) : ip_(0), state_(s) { }

    void SetStateAtPosition(std::size_t idx, int value) { state_[idx] = value; }
    int GetStateAtPosition(std::size_t idx) const { return state_[idx]; }
    bool IsTerminated() const { return state_[ip_] == 99; }
    void ResetMemory(const std::vector<int>& v) {
        for (std::size_t i = 0; i < v.size(); ++i) state_[i] = v[i];
    }

    const std::vector<int>& State() const { return state_; }
    void Step() {
        const int op = state_[ip_];
        const int arg1 = state_[state_[ip_ + 1]];
        const int arg2 = state_[state_[ip_ + 2]];
        const int dest = state_[ip_ + 3];
        switch (op) {
        case 1:
            state_[dest] = arg1 + arg2;
            break;
        case 2:
            state_[dest] = arg1 * arg2;
            break;
        default:
            std::cerr << "Unknown OpCode: " << op << '\n';
            std::terminate();
        }
        AdvanceInstructionPointer();

    }
    void Execute() {
        while (!IsTerminated()) Step();
    }
private:
    void AdvanceInstructionPointer() { ip_ += 4; }
    std::size_t ip_;
    std::vector<int> state_;
}; // class IntCodeProgram

struct InputSearch {

    InputSearch(const std::vector<int>& v) : initial_state(v) {}

    std::pair<int, int> Search(int target) const {
        for (int i = -100; i <= 100; ++i) {
            for (int j = -100; j <= 100; ++j) {
                IntCodeProgram p(initial_state);
                p.SetStateAtPosition(1, i);
                p.SetStateAtPosition(2, j);
                p.Execute();
                if (p.GetStateAtPosition(0) == target) return std::make_pair(i, j);
            }
        }
        return std::make_pair(-1, -1);
    }

    std::vector<int> initial_state;
}; // struct InputSearch

std::vector<int> parse_input(std::string& is) {
    std::vector<int> p;
    std::size_t idx = 0;
    std::stringstream buf;
    while (idx < is.size()) {
        buf << is[idx];
        while (idx + 1 < is.size() && is[idx+1] != ',') {
            idx++;
            buf << is[idx];
        }
        p.push_back(std::stoi(buf.str()));
        buf.str("");
        idx += 2;
    }
    return p;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i < v.size() - 1) os << ',';
    }

    return os;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::vector<int> p = parse_input(input);

    IntCodeProgram program(p);
    program.SetStateAtPosition(1, 12);
    program.SetStateAtPosition(2, 2);
    program.Execute();

    std::cout << "Part 1: " << program.GetStateAtPosition(0) << '\n';

    InputSearch searcher(p);
    const auto result = searcher.Search(19690720);
    std::cout << "Part 2: " << 100 * result.first + result.second << '\n';
    return 0;
}
