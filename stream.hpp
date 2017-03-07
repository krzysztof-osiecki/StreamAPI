#ifndef STREAM_API
#define STREAM_API

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class streamAlreadyConsumedException {
};

template<class T>
class stream;

template<class T, class... Args>
class streamOperation;

template<class T>
class stream {

public:
    stream();

    stream(std::vector<T> *data);

    stream<T> *filter(std::function<bool(T)> predicate);

    std::vector<T> *toVector();

    template<class R>
    stream<R> *map(std::function<R(T)> mappingFunction);

    stream<T> *peek();

protected:
    stream(std::vector<T> *data, std::vector<streamOperation<bool(T)> *> *predicates);

    bool executePredicateOperation(streamOperation<bool(T)> *operation, T value);

    template<class R>
    R executeMappingOperation(streamOperation<R(T)> *operation, T value);

    void checkConsumed(bool consume);

private:
    std::vector<streamOperation<bool(T)> *> *predicates;
    std::vector<T> *underlyingVector;
    bool consumed;
};

template<class T, class... Args>
class streamOperation<T(Args...)> {
public:
    std::function<T(Args ...)> *fun;

    streamOperation(std::function<T(Args ...)> *fun) {
        this->fun = fun;
    }
};

template<class T>
stream<T>::stream(std::vector<T> *data, std::vector<streamOperation<bool(T)> *> *predicates) {
    this->underlyingVector = data;
    this->predicates = predicates;
    this->consumed = false;
}

template<class T>
stream<T>::stream(std::vector<T> *data) {
    this->underlyingVector = data;
    this->predicates = new std::vector<streamOperation<bool(T)> *>();
    this->consumed = false;
}

template<class T>
stream<T>::stream() {
    this->underlyingVector = new std::vector<T>();
    this->predicates = new std::vector<streamOperation<bool(T)> *>();
    this->consumed = false;
}

template<class T>
stream<T> *stream<T>::filter(std::function<bool(T)> predicate) {
    checkConsumed(false);
    auto *op = new streamOperation<bool(T)>(&predicate);
    predicates->push_back(op);
    return this;
}

template<class T>
template<class R>
stream<R> *stream<T>::map(std::function<R(T)> mappingFunction) {
    streamOperation<R(T)> *op = new streamOperation<R(T)>(&mappingFunction);
    std::vector<T> *filtered = this->toVector();
    std::vector<R> *result = new std::vector<R>();
    for (typename std::vector<T>::iterator it = filtered->begin();
         it != underlyingVector->end();) {
        T v = (*it);
        auto val = this->executeMappingOperation(op, v);
        result->push_back(val);
        ++it;
    }
    return new stream<R>(result);
}


template<class T>
std::vector<T> *stream<T>::toVector() {
    checkConsumed(true);
    for (typename std::vector<T>::iterator it = underlyingVector->begin(); it != underlyingVector->end();) {
        auto remove = false;
        T v = (*it);
        for (typename std::vector<streamOperation<bool(T)> *>::iterator oIt = predicates->begin();
             oIt != predicates->end(); ++oIt) {
            auto val = this->executePredicateOperation(*oIt, v);
            if (!val) {
                remove = true;
                break;
            }
        }
        if (remove) underlyingVector->erase(it);
        else ++it;
    }
    return underlyingVector;
}

template<class T>
stream<T> *stream<T>::peek() {
    for (typename std::vector<T>::iterator it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
        auto remove = false;
        T v = (*it);
        for (typename std::vector<streamOperation<bool(T)> *>::iterator oIt = predicates->begin();
             oIt != predicates->end(); ++oIt) {
            auto val = this->executePredicateOperation(*oIt, v);
            if (!val) {
                remove = true;
                break;
            }
        }
        if (!remove) std::cout << v << " ";
    }
    std::cout << std::endl;
    return this;
}

template<class T>
bool stream<T>::executePredicateOperation(streamOperation<bool(T)> *operation,
                                          T value) {
    auto function = (*operation->fun);
    return function(value);
}

template<class T>
template<class R>
R stream<T>::executeMappingOperation(streamOperation<R(T)> *operation,
                                     T value) {
    auto function = (*operation->fun);
    return function(value);
}

template<class T>
void stream<T>::checkConsumed(bool consume) {
    if (this->consumed) throw new streamAlreadyConsumedException();
    this->consumed = consume;
}

#endif
