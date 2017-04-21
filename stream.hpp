#ifndef STREAM_API
#define STREAM_API

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <forward_list>
#include <list>

namespace stream {

    class streamAlreadyConsumedException {
    };

    template<class T>
    class stream;

    template<class T, class... Args>
    class streamOperation;

    template<class T>
    class stream {

    public:

        /**
         * Konstruktor tworzacy strumien z instancji std::vector
         *
         * @param data wektor ktory zostanie opakowany strumieniem
         */
        stream(const std::vector<T> &data);

        /**
         * Konstruktor tworzacy strumien z instancji std::deque
         *
         * @param data wektor ktory zostanie opakowany strumieniem
         */
        stream(const std::deque<T> &data);

        /**
         * Konstruktor tworzacy strumien z instancji std::forward_list
         *
         * @param data wektor ktory zostanie opakowany strumieniem
         */
        stream(const std::forward_list<T> &data);

        /**
         * Konstruktor tworzacy strumien z instancji std::list
         *
         * @param data wektor ktory zostanie opakowany strumieniem
         */
        stream(const std::list<T> &data);

        /**
         * Konstruktor tworzacy strumien z instancji std::vector, w odroznieniu
         * od drugiego kostruktora ten nie tworzy kopii przyjetych danych i moze je modyfikowac
         *
         * @param data wektor ktory zostanie opakowany strumieniem
        */
        stream(std::vector<T> *data);

        /**
         * Konstruktor tworzacy strumien z instancji tablicy
         *
         * @param data wektor ktory zostanie opakowany strumieniem
         */
        stream(T data[], int length);

        /**
         * Operacja nakladajaca na strumien filtr okreslony zadana funkcja.
         * Operacja nieterminalna
         *
         * @param predicate predykat okreslajacy warunek konieczny do znalezienia sie w wynikowym strumieniu
         * @return strumien z zaaplikowana funkcja filtrujaca
         */
        stream<T> *filter(std::function<bool(T)> predicate);

        /**
         * Operacja konwerujaca strumien, do typu wskazanego przez funkcje mapujaca, poprzez
         * zaaplikowanie jej do kazdego elementu strumienia.
         * Operacja terminalna
         *
         * @tparam R typ nowego strumienia
         * @param mappingFunction funkcja mapujaca
         * @return nowy strumien z elementami bedacymi wynikiem funkcji mapujacej
         */
        template<class R>
        stream<R> *map(std::function<R(T)> mappingFunction);

        /**
         * Operacja redukcji strumienia. Wskazana funkcja bedzie wywolywana na
         * elementach strumienia, w postaci fun(poprzedni_wynik, aktualny_element),
         * az do wyczerpania elementow.
         * Operacja terminalna
         *
         * @param reductorFunction funkcja odpowiadajaca za redukcje elementow
         * @return zredukowana wartosc ostatniego wykonania funkcji
         */
        T reduce(std::function<T(T, T)> reductorFunction);

        /**
         * Operacja aplikuje zadana funkcje do kazdego elementu strumienia
         * Operacja terminalna
         *
         * @param exectutionFunction funkcja do wykonania na kazdym elemencie
         */
        void foreach(std::function<void(T)> exectutionFunction);

        /**
         * Operacja okreslajaca czy wszystkie elementy danego strumienia spelniaja
         * zaaplikowane do niego predykaty operacji filter.
         * Operacja terminalna
         *
         * @return true jesli operacje filter nie wykluczyly zadnego z elementow strumienia
         *         false w pozostalych przypadkach
         */
        bool allMatch();

        /**
         * Operacja okreslajaca czy choc jeden element danego strumienia spelnia
         * zaaplikowane do niego predykaty operacji filter.
         * Operacja terminalna
         *
         * @return true jesli operacje filter pozostawily choc jeden element strumienia
         *         false w pozostalych przypadkach
         */
        bool anyMatches();

        /**
         * Operacja znajdujaca pierwszy element strumienia.
         * Operacja terminalna
         *
         * @return znaleziony element, NULL dla pustego strumienia
         */
        T find();

        /**
         * Operacja uzytkowa, przechodzi strumien wypisujac jego zawartosc
         * na standardowe wyjscie.
         * Operacja nieterminalna
         *
         * @return ten sam strumien wejsciowy
         */
        stream<T> *peek();

        /**
         * Operacja powrotu ze strumienia do std::vector. Aplikowane sa wszsytkie
         * operacje filter i zwracany nowy obiekt vectora.
         * Operacja terminalna
         *
         * @return std::vector zawierajacy elementy strumienia
         */
        std::vector<T> *toVector();

        /**
         * Operacja powrotu ze strumienia do std::deque. Aplikowane sa wszsytkie
         * operacje filter i zwracany nowy obiekt deque.
         * Operacja terminalna
         *
         * @return std::deque zawierajacy elementy strumienia
         */
        std::deque<T> *toDeque();

        /**
         * Operacja powrotu ze strumienia do std::forward_list. Aplikowane sa wszsytkie
         * operacje filter i zwracany nowy obiekt forward_list.
         * Operacja terminalna
         *
         * @return std::forward_list zawierajacy elementy strumienia
         */
        std::forward_list<T> *toForwardList();

        /**
         * Operacja powrotu ze strumienia do std::list. Aplikowane sa wszsytkie
         * operacje filter i zwracany nowy obiekt listy.
         * Operacja terminalna
         *
         * @return std::list zawierajacy elementy strumienia
         */
        std::list<T> *toList();

        ~stream();

    protected:

        void checkConsumed(bool consume);

        template<class R>
        std::vector<R> *toVector(std::function<R(T)> mappingFunction);

    private:
        std::vector<streamOperation<bool(T)> *> *predicates;
        std::vector<T> *underlyingVector;
        bool consumed;
    };

    template<class T, class... Args>
    class streamOperation<T(Args...)> {
    public:
        std::function<T(Args ...)> *fun;

        ~streamOperation() {
            delete (fun);
        }

        streamOperation(std::function<T(Args ...)> *fun) {
            this->fun = fun;
        }
    };

    template<class T>
    stream<T>::stream(const std::vector<T> &data) {
        this->underlyingVector = new std::vector<T>(data);
        this->predicates = new std::vector<streamOperation<bool(T)> *>();
        this->consumed = false;
    }

    template<class T>
    stream<T>::stream(std::vector<T> *data) {
        this->underlyingVector = data;
        this->predicates = new std::vector<streamOperation<bool(T)> *>();
        this->consumed = false;
    }

    template<class T>
    stream<T>::stream(const std::deque<T> &data) {
        this->underlyingVector = new std::vector<T>(data.begin(), data.end());
        this->predicates = new std::vector<streamOperation<bool(T)> *>();
        this->consumed = false;
    }

    template<class T>
    stream<T>::stream(const std::forward_list<T> &data) {
        this->underlyingVector = new std::vector<T>(data.begin(), data.end());
        this->predicates = new std::vector<streamOperation<bool(T)> *>();
        this->consumed = false;
    }

    template<class T>
    stream<T>::stream(const std::list<T> &data) {
        this->underlyingVector = new std::vector<T>(data.begin(), data.end());
        this->predicates = new std::vector<streamOperation<bool(T)> *>();
        this->consumed = false;
    }

    template<class T>
    stream<T>::stream(T data[], int length) {
        this->underlyingVector = new std::vector<T>(data, data + length);
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
    T stream<T>::find() {
        std::vector<T> *pVector = this->toVector();
        return pVector->empty() ? NULL : pVector->front();
    }

    template<class T>
    bool stream<T>::anyMatches() {
        return !toVector()->empty();
    }

    template<class T>
    bool stream<T>::allMatch() {
        unsigned int fullSize = underlyingVector->size();
        return toVector()->size() == fullSize;
    }

    template<class T>
    template<class R>
    stream<R> *stream<T>::map(std::function<R(T)> mappingFunction) {
        return new stream<R>(toVector(mappingFunction));
    }

    template<class T>
    T stream<T>::reduce(std::function<T(T, T)> reductorFunction) {
        std::vector<T> *filtered = toVector();
        auto previousVal = filtered->front();
        for (typename std::vector<T>::iterator it = filtered->begin() + 1; it != filtered->end(); ++it) {
            previousVal = reductorFunction(previousVal, (*it));
        }
        return previousVal;
    }

    template<class T>
    void stream<T>::foreach(std::function<void(T)> exectutionFunction) {
        std::vector<T> *filtered = toVector();
        for (typename std::vector<T>::iterator it = filtered->begin();
             it != filtered->end();) {
            T v = (*it);
            exectutionFunction(v);
            ++it;
        }
    }

    template<class T>
    std::vector<T> *stream<T>::toVector() {
        checkConsumed(true);
        if (predicates->empty()) {
            return new std::vector<T>(underlyingVector->begin(), underlyingVector->end());
        }
        std::vector<T> *result = new std::vector<T>();
        for (auto it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
            bool keep = true;
            T v = (*it);
            for (auto oIt = predicates->begin(); oIt != predicates->end(); ++oIt) {
                if (!(*(*oIt)->fun)(v)) {
                    keep = false;
                    break;
                }
            }
            if (keep)
                result->push_back(v);
        }
        return result;
    }

    template<class T>
    template<class R>
    std::vector<R> *stream<T>::toVector(std::function<R(T)> mappingFunction) {
        checkConsumed(true);
        std::vector<R> *result = new std::vector<R>();
        for (auto it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
            bool keep = true;
            T v = (*it);
            for (auto oIt = predicates->begin(); oIt != predicates->end(); ++oIt) {
                if (!(*(*oIt)->fun)(v)) {
                    keep = false;
                    break;
                }
            }
            if (keep)
                result->push_back(mappingFunction(v));
        }
        return result;
    }

    template<class T>
    std::deque<T> *stream<T>::toDeque() {
        checkConsumed(true);
        std::deque<T> *result = new std::deque<T>();

        for (auto it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
            bool keep = true;
            T v = (*it);
            for (auto oIt = predicates->begin(); oIt != predicates->end(); ++oIt) {
                auto val = (*(*oIt)->fun)(v);;
                if (!val) {
                    keep = false;
                    break;
                }
            }
            if (keep) result->push_back(v);
        }
        return result;
    }

    template<class T>
    std::forward_list<T> *stream<T>::toForwardList() {
        checkConsumed(true);
        std::forward_list<T> *result = new std::forward_list<T>();

        for (auto it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
            bool keep = true;
            T v = (*it);
            for (auto oIt = predicates->begin(); oIt != predicates->end(); ++oIt) {
                auto val = (*(*oIt)->fun)(v);;
                if (!val) {
                    keep = false;
                    break;
                }
            }
            if (keep) result->push_front(v);
        }
        return result;
    }

    template<class T>
    std::list<T> *stream<T>::toList() {
        checkConsumed(true);
        std::list<T> *result = new std::list<T>();

        for (auto it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
            bool keep = true;
            T v = (*it);
            for (auto oIt = predicates->begin(); oIt != predicates->end(); ++oIt) {
                if (!(*(*oIt)->fun)(v)) {
                    keep = false;
                    break;
                }
            }
            if (keep) result->push_back(v);
        }
        return result;
    }


    template<class T>
    stream<T> *stream<T>::peek() {
        for (auto it = underlyingVector->begin(); it != underlyingVector->end(); ++it) {
            auto keep = true;
            T v = (*it);
            for (auto oIt = predicates->begin(); oIt != predicates->end(); ++oIt) {
                auto val = (*(*oIt)->fun)(v);;
                if (!val) {
                    keep = false;
                    break;
                }
            }
            if (keep) std::cout << v << " ";
        }
        std::cout << std::endl;
        return this;
    }

    template<class T>
    void stream<T>::checkConsumed(bool consume) {
        if (this->consumed) throw new streamAlreadyConsumedException();
        this->consumed = consume;
    }

    template<class T>
    stream<T>::~stream() {
        delete (underlyingVector);
        for (auto &predicate : *predicates) delete (predicate);
        delete (predicates);
    }
}

#endif
