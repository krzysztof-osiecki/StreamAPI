#ifndef STREAM_API
#define STREAM_API

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

enum operationType {
    FILTER_OPERATION = 0,
    MAPPING_OPERATION = 1
};

enum executionType {
    IMMEDIATE = 0,
    LAZY = 1
};

template<class T>
class stream;

template<class T, class R>
class streamOperation;

template<class T>
using predicate = bool (*)(T a);

template<class T, class R>
using mappingFunction = R (*)(T a);

template<class T>
class stream {

public:
    stream();

    stream(std::vector<T> *data);

    stream<T> *filter(predicate<T> predicate);

    std::vector<T> *toVector();

    template <class R>
    stream<R> *map(std::function<R(T)> mappingFunction);

    void peek();

protected:
    std::pair<T, bool> executeOperation(std::vector<T> *result, streamOperation<T, T> *operation, T value);

private:
    std::vector<streamOperation<T, T> *> *operations;
    std::vector<T> *underlyingVector;
};

template<class T, class R>
class streamOperation {
public:
    int paramCount;
    predicate<T> *fun;
    mappingFunction<T, R> *mappingFun;
    operationType type;
    executionType exType;

    streamOperation(int paramCount, predicate<T> *fun, operationType type, executionType exType) {
        this->paramCount = paramCount;
        this->fun = fun;
        this->type = type;
        this->exType = exType;
    }
};


template<class T>
stream<T>::stream(std::vector<T> *data) {
    this->underlyingVector = data;
    this->operations = new std::vector<streamOperation<T, T> *>();
}

template<class T>
stream<T>::stream() {
    underlyingVector = new std::vector<T>();
    operations = new std::vector<streamOperation<T, T> *>();
}

template<class T>
stream<T> *stream<T>::filter(predicate<T> predicate) {
    auto *op = new streamOperation<T, T>(1, &predicate, operationType::FILTER_OPERATION, executionType::LAZY);
    operations->push_back(op);
    return this;
}

template<class T>
template<class R>
stream<R> *stream<T>::map(std::function<R(T)> mappingFunction) {
    auto *op = new streamOperation<T, R>(1, &mappingFunction, operationType::MAPPING_OPERATION, executionType::IMMEDIATE);
    operations->push_back(op);
    return this;
}

template<class T>
std::vector<T> *stream<T>::toVector() {
    std::vector<T> *result = new std::vector<T>();
    for (typename std::vector<T>::iterator it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
        T v = (*it);
        for (typename std::vector<streamOperation<T, T> *>::iterator oIt = operations->begin();
             oIt != operations->end(); ++oIt) {
            auto val = this->executeOperation(result, *oIt, v);
            if (!val.first) break;
            v = val.second;
        }
    }
    return result;
}

template<class T>
void stream<T>::peek() {
    std::vector<T> *vector = this->toVector();
    for (int i = 0; i < vector->size(); i++) {
        std::cout << vector->at(i) << " ";
    }
    std::cout << std::endl;
    delete (vector);
}

template<class T>
std::pair<T, bool> stream<T>::executeOperation(std::vector<T> *result, streamOperation<T, T> *operation, T value) {
    switch (operation->type) {
        case operationType::FILTER_OPERATION: {
            predicate<T> function = (*operation->fun);
            if (function(value)) {
                result->push_back(value);
                return std::make_pair(value, true);
            }
            return std::make_pair(value, false);
        }
        case operationType::MAPPING_OPERATION: {

        }
        default: {
            std::cout << "Unrecognized operation" << std::endl;
            return std::make_pair(NULL, false);
        }
    }
}

#endif
