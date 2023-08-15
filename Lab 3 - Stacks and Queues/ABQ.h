#pragma once
#include <stdexcept>

template<typename T>
class ABQ {
private:
    T* _dataQueue;
    unsigned int _currentSize;
    unsigned int _capacity;
    float _SCALE_FACTOR;

public:
    ABQ();
    ABQ(int capacity);
    ABQ(const ABQ& q);
    ABQ& operator=(const ABQ& q);
    ~ABQ();

    void enqueue(T data);
    T dequeue();
    T peek();
    unsigned int getSize();
    unsigned int getMaxCapacity();
    T* getData();
};

// =====================

template<typename T>
ABQ<T>::ABQ() {
    _capacity = 1;
    _currentSize = 0;
    _dataQueue = new T[_capacity];
    _SCALE_FACTOR = 2.0f;
}

template<typename T>
ABQ<T>::ABQ(int capacity) {
    _capacity = capacity;
    _currentSize = 0;
    _dataQueue = new T[_capacity];
    _SCALE_FACTOR = 2.0f;
}

template<typename T>
ABQ<T>::ABQ(const ABQ& q) {
    _capacity = q._capacity;
    _currentSize = q._currentSize;
    _dataQueue = new T[_capacity];
    _SCALE_FACTOR = q._SCALE_FACTOR;

    for (unsigned int i = 0; i < _currentSize; i++) {
        _dataQueue[i] = q._dataQueue[i];
    }
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& q) {
    if (this == &q) {
        return *this;
    }

    _capacity = q._capacity;
    _currentSize = q._currentSize;
    _SCALE_FACTOR = q._SCALE_FACTOR;

    delete[] _dataQueue;
    _dataQueue = new T[_capacity];

    for (unsigned int i = 0; i < _currentSize; i++) {
        _dataQueue[i] = q._dataQueue[i];
    }

    return *this;
}

template<typename T>
ABQ<T>::~ABQ() {
    delete[] _dataQueue;
}

template<typename T>
void ABQ<T>::enqueue(T data) {
    if (_currentSize == _capacity) {
        _capacity *= _SCALE_FACTOR;
        T* temp_dataQueue = new T[_capacity];
        for (unsigned int i = 0; i < _currentSize; i++) {
            temp_dataQueue[i] = _dataQueue[i];
        }
        delete[] _dataQueue;
        _dataQueue = temp_dataQueue;
    }

    _dataQueue[_currentSize] = data;
    _currentSize++;
}

template<typename T>
T ABQ<T>::dequeue() {
    if (_currentSize == 0) {
        throw std::runtime_error("Queue is empty");
    }

    T dequeuedElement = _dataQueue[0];

    for (unsigned int i = 1; i < _currentSize; i++) {
        _dataQueue[i - 1] = _dataQueue[i];
    }

    _currentSize--;

    if (static_cast<float>(_currentSize) / _capacity < 1 / _SCALE_FACTOR) {
        _capacity /= static_cast<int>(_SCALE_FACTOR);
        T* temp_dataQueue = new T[_capacity];
        for (unsigned int i = 0; i < _currentSize; i++) {
            temp_dataQueue[i] = _dataQueue[i];
        }
        delete[] _dataQueue;
        _dataQueue = temp_dataQueue;
    }

    return dequeuedElement;
}

template<typename T>
T ABQ<T>::peek() {
    if (_currentSize == 0) {
        throw std::runtime_error("Queue is empty");
    }

    return _dataQueue[0];
}

template<typename T>
unsigned int ABQ<T>::getSize() {
    return _currentSize;
}

template<typename T>
unsigned int ABQ<T>::getMaxCapacity() {
    return _capacity;
}

template<typename T>
T* ABQ<T>::getData() {
    return _dataQueue;
}
