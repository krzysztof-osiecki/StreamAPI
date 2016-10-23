
#include "stream.hpp"

int main() {
    std::vector<int> v = {1, -2, 3, -4};
    stream<int> *testStream = new stream<int>(&v);
    auto f = [](int a) -> double { return a + 0.1; };
    double s = f(42);
    std::cout<<s<<std::endl;
    testStream
            ->filter([](int a) -> bool { return a > 0; })
            ->peek();
    std::function<double(int)> xa = [](int a) -> double { return a + 0.1; };
    std::vector<int> *pVector = testStream
            ->filter([](int a) -> bool { return a > 0; })
            ->map(xa)
            ->toVector();
    return 0;
}