#include "stream.hpp"
#include <ctime>
#include <chrono>

#define TEST_SIZE 10000
#define EXECUTIONS 100.0

template<typename TimeT = std::chrono::milliseconds>
struct measure {
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F &&func, Args &&... args) {
        auto start = std::chrono::steady_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<TimeT>
                (std::chrono::steady_clock::now() - start);
        return duration.count();
    }
};

void firstTest();

void singleFunctionTest(const std::vector<int> *baseVector);

void doubleFunctionTest(const std::vector<int> *baseVector);

std::vector<int> *evenOnlyNewList(std::vector<int> *vector) {
    std::vector<int> *result = new std::vector<int>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        if (*it % 2 == 0) { result->push_back(*it); }
    }
    return result;
}

std::vector<int> *divisibleBy3NewList(std::vector<int> *vector) {
    std::vector<int> *result = new std::vector<int>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        if (*it % 3 == 0) { result->push_back(*it); }
    }
    return result;
}

std::vector<int> *evenOnlyForINewList(std::vector<int> *vector) {
    std::vector<int> *result = new std::vector<int>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        int value = vector->at(i);
        if (value % 2 == 0) { result->push_back(value); }
    }
    return result;
}

std::vector<int> *divisibleBy3ForINewList(std::vector<int> *vector) {
    std::vector<int> *result = new std::vector<int>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        int value = vector->at(i);
        if (value % 3 == 0) { result->push_back(value); }
    }
    return result;
}


std::vector<int> *divisibleBy3WithRemoval(std::vector<int> *vector) {
    for (auto it = vector->begin(); it != vector->end();) {
        if (*it % 3 != 1) { vector->erase(it); } else { ++it; }
    }
    return vector;
}

std::vector<int> *evenOnlyWithRemoval(std::vector<int> *vector) {
    for (auto it = vector->begin(); it != vector->end();) {
        if (*it % 2 == 1) { vector->erase(it); } else { ++it; }
    }
    return vector;
}


std::vector<int> *evenOnlyNewListLambda(std::vector<int> *vector) {
    std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
    std::vector<int> *result = new std::vector<int>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        if (parity(*it) == 1) { result->push_back(*it); }
    }
    return result;
}

std::vector<int> *divisibleBy3NewListLambda(std::vector<int> *vector) {
    std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };
    std::vector<int> *result = new std::vector<int>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        if (divisibleBy3(*it) == 1) { result->push_back(*it); }
    }
    return result;
}

std::vector<int> *evenOnlyForINewListLambda(std::vector<int> *vector) {
    std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
    std::vector<int> *result = new std::vector<int>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        int value = vector->at(i);
        if (parity(value) == 1) { result->push_back(value); }
    }
    return result;
}

std::vector<int> *divisibleBy3ForINewListLambda(std::vector<int> *vector) {
    std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };
    std::vector<int> *result = new std::vector<int>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        int value = vector->at(i);
        if (divisibleBy3(value) == 1) { result->push_back(value); }
    }
    return result;
}


std::vector<int> *divisibleBy3WithRemovalLambda(std::vector<int> *vector) {
    std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
    std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };
    for (auto it = vector->begin(); it != vector->end();) {
        if (divisibleBy3(*it) == 0) { vector->erase(it); } else { ++it; }
    }
    return vector;
}

std::vector<int> *evenOnlyWithRemovalLambda(std::vector<int> *vector) {
    std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
    std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };
    for (auto it = vector->begin(); it != vector->end();) {
        if (parity(*it) == 0) { vector->erase(it); } else { ++it; }
    }
    return vector;
}


int main() {
    std::vector<int> *baseVector = new std::vector<int>();
    for (int i = 0; i < TEST_SIZE; i++) {
        baseVector->push_back(i);
    }
//    singleFunctionTest(baseVector);
    firstTest();

    return 0;
}

void doubleFunctionTest(const std::vector<int> *baseVector) {
    std::cout << "Double execution test" << std::endl;
    std::vector<int> *newListVector = new std::vector<int>(*baseVector);
    std::vector<int> *forIVector = new std::vector<int>(*baseVector);
    std::vector<int> *removalListVector = new std::vector<int>(*baseVector);
    stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
    std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
    std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };

    std::cout << measure<>::execution([streamCase, parity, divisibleBy3]() -> void {
        streamCase->filter(parity)->filter(divisibleBy3)->toVector();
    }) << std::endl;
    std::cout << measure<>::execution([newListVector]() -> void {
        std::vector<int> *pVector = evenOnlyNewList(newListVector);
        divisibleBy3NewList(pVector);
    }) << std::endl;
    std::cout << measure<>::execution([removalListVector]() -> void {
        std::vector<int> *pVector = evenOnlyWithRemoval(removalListVector);
        divisibleBy3WithRemoval(pVector);
    }) << std::endl;
    std::cout << measure<>::execution([forIVector]() -> void {
        std::vector<int> *pVector = evenOnlyForINewList(forIVector);
        divisibleBy3ForINewList(pVector);
    }) << std::endl;
}

void singleFunctionTest(const std::vector<int> *baseVector) {
    long long int _1 = 0;
    long long int _2 = 0;
    long long int _3 = 0;
    long long int _4 = 0;
    long long int _5 = 0;
    long long int _6 = 0;
    long long int _7 = 0;
    std::cout << "Single execution test" << std::endl;
    for (int i = 0; i < EXECUTIONS; i++) {
        std::vector<int> *newListVector = new std::vector<int>(*baseVector);
        std::vector<int> *forIVector = new std::vector<int>(*baseVector);
        std::vector<int> *removalListVector = new std::vector<int>(*baseVector);
        std::vector<int> *newListVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *forIVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *removalListVectorLambda = new std::vector<int>(*baseVector);
        stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
        std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
        _1 += measure<>::execution([streamCase, parity]() -> void {
            streamCase->filter(parity)->toVector();
        });
        _2 += measure<>::execution(evenOnlyNewList, newListVector);
        _3 += measure<>::execution(evenOnlyWithRemoval, removalListVector);
        _4 += measure<>::execution(evenOnlyForINewList, forIVector);
        _5 += measure<>::execution(evenOnlyNewListLambda, newListVectorLambda);
        _6 += measure<>::execution(evenOnlyWithRemovalLambda, forIVectorLambda);
        _7 += measure<>::execution(evenOnlyForINewListLambda, removalListVectorLambda);
        delete (newListVector);
        delete (forIVector);
        delete (removalListVector);
        delete (newListVectorLambda);
        delete (forIVectorLambda);
        delete (removalListVectorLambda);
        delete (streamCase);
    }
    std::cout << _1 / EXECUTIONS << std::endl;
    std::cout << _2 / EXECUTIONS << std::endl;
    std::cout << _3 / EXECUTIONS << std::endl;
    std::cout << _4 / EXECUTIONS << std::endl;
    std::cout << _5 / EXECUTIONS << std::endl;
    std::cout << _6 / EXECUTIONS << std::endl;
    std::cout << _7 / EXECUTIONS << std::endl;


}


void firstTest() {
    std::vector<int> v = {1, -2, 3, -4};
    stream::stream<int> *testStream = new stream::stream<int>(v);
    stream::stream<int> *testStream2 = new stream::stream<int>(v);
    stream::stream<int> *testStream3 = new stream::stream<int>(v);
    stream::stream<int> *testStream4 = new stream::stream<int>(v);
    stream::stream<int> *testStream5 = new stream::stream<int>(v);
    stream::stream<int> *testStream6 = new stream::stream<int>(v);
    std::function<bool(int)> ff = [](int a) { return a > 0; };
    std::function<bool(int)> ff3 = [](int a) { return a >= 3; };
    std::function<double(int)> xa = [](int a) { return a + 0.1; };
//    auto xa = [](int a) -> double { return a + 0.1; }; NIE DZIALA
    auto a = ([v, &testStream](int a) { double costam = a + 0.1; testStream->peek(); v.at(0);
        int sa = 9;if(sa != 9)
        return costam; else return 1.9;});
    std::cout << a(1) << "ASD" << std::endl;
    testStream
            ->filter([](int a) { return a > 0; })
            ->filter(ff3)
            ->peek();
    testStream2
            ->filter(ff)
            ->map((std::function<double(int)>) ([](int a) { return a + 0.1; }))
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
}