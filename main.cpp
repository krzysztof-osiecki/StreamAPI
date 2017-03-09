#include "stream.hpp"

int main() {
    std::vector<int> v = {1, -2, 3, -4};
    stream::stream<int> *testStream = new stream::stream<int>(v);
    stream::stream<int> *testStream2 = new stream::stream<int>(v);
    stream::stream<int> *testStream3 = new stream::stream<int>(v);
    stream::stream<int> *testStream4 = new stream::stream<int>(v);
    stream::stream<int> *testStream5 = new stream::stream<int>(v);
    stream::stream<int> *testStream6 = new stream::stream<int>(v);
    std::function<bool(int)> ff = [](int a) -> bool { return a > 0; };
    std::function<bool(int)> ff3 = [](int a) -> bool { return a >= 3; };
    std::function<double(int)> xa = [](int a) -> double { return a + 0.1; };
    testStream
            ->filter([](int a) -> bool { return a > 0; })
            ->filter(ff3)
            ->peek();
    testStream2
            ->filter(ff)
            ->map((std::function<double(int)>) ([](int a) -> double { return a + 0.1; }))
            ->peek();
    testStream3
            ->filter(ff)
            ->map(xa)
            ->peek();
    std::string str = testStream4
                              ->filter([](int a) -> bool { return a > 0; })
                              ->filter(ff3)
                              ->anyMatches() ? "TRUE" : "FALSE";
    std::cout << str << std::endl;
    std::cout << testStream5
            ->filter([](int a) -> bool { return a > 0; })
            ->filter(ff3)
            ->find() << std::endl;
    std::string strAll = testStream6
                                 ->filter([](int a) -> bool { return a > 0; })
                                 ->allMatch() ? "TRUE" : "FALSE";
    std::cout << strAll << std::endl;
    return 0;
}