#include "stream.hpp"

int main() {
    std::vector<int> v = {1, -2, 3, -4};
    stream<int> *testStream = new stream<int>(&v);
    stream<int> *testStream2 = new stream<int>(&v);
    stream<int> *testStream3 = new stream<int>(&v);
    std::function<bool(int)> ff = [](int a) -> bool { return a > 0; };
    std::function<bool(int)> ff3 = [](int a) -> bool { return a >= 3; };
    std::function<double(int)> xa = [](int a) -> double { return a + 0.1; };
    testStream
            ->filter([](int a) -> bool { return a > 0; })
            ->filter(ff3)
            ->peek();
    stream<double> *testStream4 = testStream2
            ->filter(ff)
            ->map((std::function<double(int)>) ([](int a) -> double { return a + 0.1; }))
            ->peek();
    testStream3
            ->filter(ff)
            ->map(xa)
            ->peek();
    return 0;
}