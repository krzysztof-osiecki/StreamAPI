#include "stream.hpp"
#include <ctime>
#include <chrono>

#define TEST_SIZE 10000000
#define EXECUTIONS 1000.0

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

void tripleFunctionTest(const std::vector<int> *baseVector);

void singleMappingFunctionTest(const std::vector<int> *baseVector);

void doubleMappingFunctionTest(const std::vector<int> *baseVector);

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

std::vector<double> *mapOnlyNewList(std::vector<int> *vector) {
    std::vector<double> *result = new std::vector<double>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        result->push_back(*it + 0.1);
    }
    return result;
}

std::vector<double> *mapOnlyForINewList(std::vector<int> *vector) {
    std::vector<double> *result = new std::vector<double>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        int value = vector->at(i);
        result->push_back(value + 0.1);
    }
    return result;
}

std::vector<double> *mapOnlyNewListLambda(std::vector<int> *vector) {
    std::function<double(int)> mapper = [](int a) -> double { return a + 0.1; };
    std::vector<double> *result = new std::vector<double>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        result->push_back(mapper(*it));
    }
    return result;
}

std::vector<double> *mapOnlyForINewListLambda(std::vector<int> *vector) {
    std::function<double(int)> mapper = [](int a) -> double { return a + 0.1; };
    std::vector<double> *result = new std::vector<double>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        int value = vector->at(i);
        result->push_back(mapper(value));
    }
    return result;
}


std::vector<int> *mapOnlyNewList(std::vector<double> *vector) {
    std::vector<int> *result = new std::vector<int>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        result->push_back((int &&) (*it - 0.1));
    }
    return result;
}

std::vector<int> *mapOnlyForINewList(std::vector<double> *vector) {
    std::vector<int> *result = new std::vector<int>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        double value = vector->at(i);
        result->push_back((int &&) (value - 0.1));
    }
    return result;
}

std::vector<int> *mapOnlyNewListLambda(std::vector<double> *vector) {
    std::function<int(double)> mapper = [](double a) -> int { return (int) (a - 0.1); };
    std::vector<int> *result = new std::vector<int>();
    for (auto it = vector->begin(); it != vector->end(); ++it) {
        result->push_back(mapper(*it));
    }
    return result;
}

std::vector<int> *mapOnlyForINewListLambda(std::vector<double> *vector) {
    std::function<int(double)> mapper = [](double a) -> int { return (int) (a - 0.1); };
    std::vector<int> *result = new std::vector<int>();
    for (unsigned i = 0; i < vector->size(); ++i) {
        double value = vector->at(i);
        result->push_back(mapper(value));
    }
    return result;
}


int main() {
    std::vector<int> *baseVector = new std::vector<int>();
    for (int i = 0; i < TEST_SIZE; i++) {
        baseVector->push_back(i);
    }
//    singleFunctionTest(baseVector);
//    doubleFunctionTest(baseVector);
//    tripleFunctionTest(baseVector);
//    singleMappingFunctionTest(baseVector);
//    doubleMappingFunctionTest(baseVector);
    firstTest();
    delete(baseVector);
    return 0;
}

void tripleFunctionTest(const std::vector<int> *baseVector) {
    std::cout << "Triple execution test" << std::endl;

    long long int _1 = 0;
    long long int _2 = 0;
    long long int _4 = 0;
    long long int _5 = 0;
    long long int _6 = 0;
    for (int i = 0; i < EXECUTIONS; i++) {
        std::vector<int> *newListVector = new std::vector<int>(*baseVector);
        std::vector<int> *forIVector = new std::vector<int>(*baseVector);
        std::vector<int> *newListVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *forIVectorLambda = new std::vector<int>(*baseVector);
        stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
        std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
        std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };
        _1 += measure<>::execution([streamCase, parity, divisibleBy3]() -> void {
            delete (streamCase->filter(parity)->filter(divisibleBy3)->filter(parity)->toVector());
        });
        _2 += measure<>::execution([newListVector]() -> void {
            std::vector<int> *pVector = evenOnlyNewList(newListVector);
            std::vector<int> *list = divisibleBy3NewList(pVector);
            std::vector<int> *newList = evenOnlyNewList(list);
            delete (pVector);
            delete (list);
            delete (newList);
        });
        _4 += measure<>::execution([forIVector]() -> void {
            std::vector<int> *pVector = evenOnlyForINewList(forIVector);
            std::vector<int> *list = divisibleBy3ForINewList(pVector);
            std::vector<int> *newList = evenOnlyForINewList(list);
            delete (pVector);
            delete (list);
            delete (newList);
        });
        _5 += measure<>::execution([newListVectorLambda]() -> void {
            std::vector<int> *pVector = evenOnlyNewListLambda(newListVectorLambda);
            std::vector<int> *list = divisibleBy3NewListLambda(pVector);
            std::vector<int> *newList = evenOnlyNewListLambda(list);
            delete (pVector);
            delete (list);
            delete (newList);
        });
        _6 += measure<>::execution([forIVectorLambda]() -> void {
            std::vector<int> *pVector = evenOnlyForINewListLambda(forIVectorLambda);
            std::vector<int> *list = divisibleBy3ForINewListLambda(pVector);
            std::vector<int> *newList = evenOnlyForINewListLambda(list);
            delete (pVector);
            delete (list);
            delete (newList);
        });
        delete (newListVector);
        delete (forIVector);
        delete (newListVectorLambda);
        delete (forIVectorLambda);
        delete (streamCase);
    }
    std::cout << _1 / EXECUTIONS << std::endl;
    std::cout << _2 / EXECUTIONS << std::endl;
    std::cout << _4 / EXECUTIONS << std::endl;
    std::cout << _5 / EXECUTIONS << std::endl;
    std::cout << _6 / EXECUTIONS << std::endl;
}

void doubleFunctionTest(const std::vector<int> *baseVector) {
    std::cout << "Double execution test" << std::endl;

    long long int _1 = 0;
    long long int _2 = 0;
    long long int _4 = 0;
    long long int _5 = 0;
    long long int _6 = 0;
    for (int i = 0; i < EXECUTIONS; i++) {
        std::vector<int> *newListVector = new std::vector<int>(*baseVector);
        std::vector<int> *forIVector = new std::vector<int>(*baseVector);
        std::vector<int> *newListVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *forIVectorLambda = new std::vector<int>(*baseVector);
        stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
        std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
        std::function<bool(int)> divisibleBy3 = [](int a) -> bool { return (bool) (a % 3); };
        _1 += measure<>::execution([streamCase, parity, divisibleBy3]() -> void {
            delete (streamCase->filter(parity)->filter(divisibleBy3)->toVector());
        });
        _2 += measure<>::execution([newListVector]() -> void {
            std::vector<int> *pVector = evenOnlyNewList(newListVector);
            std::vector<int> *list = divisibleBy3NewList(pVector);
            delete (pVector);
            delete (list);
        });
        _4 += measure<>::execution([forIVector]() -> void {
            std::vector<int> *pVector = evenOnlyForINewList(forIVector);
            std::vector<int> *list = divisibleBy3ForINewList(pVector);
            delete (pVector);
            delete (list);
        });
        _5 += measure<>::execution([newListVectorLambda]() -> void {
            std::vector<int> *pVector = evenOnlyNewListLambda(newListVectorLambda);
            std::vector<int> *list = divisibleBy3NewListLambda(pVector);
            delete (pVector);
            delete (list);
        });
        _6 += measure<>::execution([forIVectorLambda]() -> void {
            std::vector<int> *pVector = evenOnlyForINewListLambda(forIVectorLambda);
            std::vector<int> *list = divisibleBy3ForINewListLambda(pVector);
            delete (pVector);
            delete (list);
        });
        delete (newListVector);
        delete (forIVector);
        delete (newListVectorLambda);
        delete (forIVectorLambda);
        delete (streamCase);
    }
    std::cout << _1 / EXECUTIONS << std::endl;
    std::cout << _2 / EXECUTIONS << std::endl;
    std::cout << _4 / EXECUTIONS << std::endl;
    std::cout << _5 / EXECUTIONS << std::endl;
    std::cout << _6 / EXECUTIONS << std::endl;
}

void singleFunctionTest(const std::vector<int> *baseVector) {
    long long int _1 = 0;
    long long int _2 = 0;
    long long int _4 = 0;
    long long int _5 = 0;
    long long int _7 = 0;
    std::cout << "Single execution test" << std::endl;
    for (int i = 0; i < EXECUTIONS; i++) {
        std::vector<int> *newListVector = new std::vector<int>(*baseVector);
        std::vector<int> *forIVector = new std::vector<int>(*baseVector);
        std::vector<int> *newListVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *forIVectorLambda = new std::vector<int>(*baseVector);
        stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
        std::function<bool(int)> parity = [](int a) -> bool { return (bool) (a % 2); };
        _1 += measure<>::execution([streamCase, parity]() -> void {
            delete (streamCase->filter(parity)->toVector());
        });
        _2 += measure<>::execution([newListVector]() -> void {
            delete (evenOnlyNewList(newListVector));
        });
        _4 += measure<>::execution([forIVector]() -> void {
            delete (evenOnlyForINewList(forIVector));
        });
        _5 += measure<>::execution([newListVectorLambda]() -> void {
            delete (evenOnlyNewListLambda(newListVectorLambda));
        });
        _7 += measure<>::execution([forIVectorLambda]() -> void {
            delete (evenOnlyForINewListLambda(forIVectorLambda));
        });
        delete (newListVector);
        delete (forIVector);
        delete (newListVectorLambda);
        delete (forIVectorLambda);
        delete (streamCase);
    }
    std::cout << _1 / EXECUTIONS << std::endl;
    std::cout << _2 / EXECUTIONS << std::endl;
    std::cout << _4 / EXECUTIONS << std::endl;
    std::cout << _5 / EXECUTIONS << std::endl;
    std::cout << _7 / EXECUTIONS << std::endl;
}

void singleMappingFunctionTest(const std::vector<int> *baseVector) {
    long long int _1 = 0;
    long long int _2 = 0;
    long long int _4 = 0;
    long long int _5 = 0;
    long long int _7 = 0;
    std::cout << "Single mapping execution test" << std::endl;
    for (int i = 0; i < EXECUTIONS; i++) {
        std::vector<int> *newListVector = new std::vector<int>(*baseVector);
        std::vector<int> *forIVector = new std::vector<int>(*baseVector);
        std::vector<int> *newListVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *forIVectorLambda = new std::vector<int>(*baseVector);
        stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
        std::function<double(int)> mapper = [](int a) -> double { return a + 0.1; };
        _1 += measure<>::execution([streamCase, mapper]() -> void {
            stream::stream<double> *pStream = streamCase->map(mapper);
            delete (pStream->toVector());
            delete (pStream);
        });
        _2 += measure<>::execution([newListVector]() -> void {
            delete (mapOnlyNewList(newListVector));
        });
        _4 += measure<>::execution([forIVector]() -> void {
            delete (mapOnlyForINewList(forIVector));
        });
        _5 += measure<>::execution([newListVectorLambda]() -> void {
            delete (mapOnlyNewListLambda(newListVectorLambda));
        });
        _7 += measure<>::execution([forIVectorLambda]() -> void {
            delete (mapOnlyForINewListLambda(forIVectorLambda));
        });
        delete (newListVector);
        delete (forIVector);
        delete (newListVectorLambda);
        delete (forIVectorLambda);
        delete (streamCase);
    }
    std::cout << _1 / EXECUTIONS << std::endl;
    std::cout << _2 / EXECUTIONS << std::endl;
    std::cout << _4 / EXECUTIONS << std::endl;
    std::cout << _5 / EXECUTIONS << std::endl;
    std::cout << _7 / EXECUTIONS << std::endl;
}

void doubleMappingFunctionTest(const std::vector<int> *baseVector) {
    long long int _1 = 0;
    long long int _2 = 0;
    long long int _4 = 0;
    long long int _5 = 0;
    long long int _7 = 0;
    std::cout << "Double mapping execution test" << std::endl;
    for (int i = 0; i < EXECUTIONS; i++) {
        std::vector<int> *newListVector = new std::vector<int>(*baseVector);
        std::vector<int> *forIVector = new std::vector<int>(*baseVector);
        std::vector<int> *newListVectorLambda = new std::vector<int>(*baseVector);
        std::vector<int> *forIVectorLambda = new std::vector<int>(*baseVector);
        stream::stream<int> *streamCase = new stream::stream<int>(*baseVector);
        std::function<double(int)> mapper = [](int a) -> double { return a + 0.1; };
        std::function<int(double)> reverseMapper = [](double a) -> int { return (int) (a - 0.1); };
        _1 += measure<>::execution([streamCase, reverseMapper, mapper]() -> void {
            stream::stream<double> *pStream = streamCase->map(mapper);
            stream::stream<int> *map = pStream->map(reverseMapper);
            delete (map->toVector());
            delete (pStream);
            delete (map);
        });
        _2 += measure<>::execution([newListVector]() -> void {
            std::vector<double> *pVector = mapOnlyNewList(newListVector);
            delete (mapOnlyNewList(pVector));
            delete (pVector);
        });
        _4 += measure<>::execution([forIVector]() -> void {
            std::vector<double> *pVector = mapOnlyForINewList(forIVector);
            delete (mapOnlyForINewList(pVector));
            delete (pVector);
        });
        _5 += measure<>::execution([newListVectorLambda]() -> void {
            std::vector<double> *pVector = mapOnlyNewListLambda(newListVectorLambda);
            delete (mapOnlyNewListLambda(pVector));
            delete (pVector);
        });
        _7 += measure<>::execution([forIVectorLambda]() -> void {
            std::vector<double> *pVector = mapOnlyForINewListLambda(forIVectorLambda);
            delete (mapOnlyForINewListLambda(pVector));
            delete (pVector);
        });
        delete (newListVector);
        delete (forIVector);
        delete (newListVectorLambda);
        delete (forIVectorLambda);
        delete (streamCase);
    }
    std::cout << _1 / EXECUTIONS << std::endl;
    std::cout << _2 / EXECUTIONS << std::endl;
    std::cout << _4 / EXECUTIONS << std::endl;
    std::cout << _5 / EXECUTIONS << std::endl;
    std::cout << _7 / EXECUTIONS << std::endl;
}


void firstTest() {
    std::vector<int> v = {1, -2, 3, -4};
    std::deque<int> d = {1, -2, 3, -4};
    std::list<int> l = {1, -2, 3, -4};
    std::forward_list<int> fl = {1, -2, 3, -4};
    int array[5] = {1, -2, 3, -4};
    stream::stream<int> *testStream = new stream::stream<int>(v);
    stream::stream<int> *testStream2 = new stream::stream<int>(d);
    stream::stream<int> *testStream3 = new stream::stream<int>(l);
    stream::stream<int> *testStream4 = new stream::stream<int>(fl);
    stream::stream<int> *testStream5 = new stream::stream<int>(v);
    stream::stream<int> *testStream6 = new stream::stream<int>(array, 5);
    std::function<bool(int)> ff = [](int a) { return a > 0; };
    std::function<bool(int)> ff3 = [](int a) { return a >= 3; };
    std::function<double(int)> xa = [](int a) { return a + 0.1; };
//    auto xa = [](int a) -> double { return a + 0.1; };
    testStream
            ->filter([](int a) { return a > 0; })
            ->filter(ff3)
            ->peek();
    testStream2
            ->filter(ff)
            ->map(([](int a) { return a + 0.1; }))
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