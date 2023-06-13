#include <stdexcept>

template<typename T>
class ABS {
private:
    T* _dataStack;
    unsigned int _currentSize;
    unsigned int _capacity;
    float _SCALE_FACTOR;

public:
    ABS();
    ABS(int capacity);
    ABS(const ABS& d);
    ABS& operator=(const ABS& d);
    ~ABS();

    void push(T data);
    T pop();
    T peek();
    unsigned int getSize();
    unsigned int getMaxCapacity();
    T* getData();
};

// =====================

template<typename T>
ABS<T>::ABS() {
    _capacity = 1;
    _currentSize = 0;
    _dataStack = new T[_capacity];
    _SCALE_FACTOR = 2.0;
}

template<typename T>
ABS<T>::ABS(int capacity) {
    _capacity = capacity;
    _currentSize = 0;
    _dataStack = new T[_capacity];
    _SCALE_FACTOR = 2.0;
}

template<typename T>
ABS<T>::ABS(const ABS &d) {
    _capacity = d._capacity;
    _currentSize = d._currentSize;
    _dataStack = new T[_capacity];
    _SCALE_FACTOR = 2.0;

    for (unsigned int i = 0; i < _currentSize; i++) {
        _dataStack[i] = d._dataStack[i];
    }
}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS &d) {
    if (this == &d) {
        return *this;
    }

    _capacity = d._capacity;
    _currentSize = d._currentSize;
    _SCALE_FACTOR = 2.0;

    delete[] _dataStack;
    _dataStack = new T[_capacity];

    for (unsigned int i = 0; i < _currentSize; i++) {
        _dataStack[i] = d._dataStack[i];
    }

    return *this;
}

template<typename T>
ABS<T>::~ABS() {
    delete[] _dataStack;
}

template<typename T>
void ABS<T>::push(T data) {
    if (_currentSize == _capacity) {
        _capacity *= _SCALE_FACTOR;
    }
    T* temp_dataStack = new T[_capacity];
    for (unsigned int i = 0; i < _currentSize; i++) {
        temp_dataStack[i] = _dataStack[i];
    }
    delete[] _dataStack;
    _dataStack = temp_dataStack;
    _dataStack[_currentSize] = data;
    _currentSize++;
}

template<typename T>
T ABS<T>::pop() {
    if (_currentSize == 0) {
        throw std::runtime_error("Stack is empty");
    }

    _currentSize--;
    if (static_cast<float>(_currentSize)/_capacity < 1/_SCALE_FACTOR){
        _capacity /= static_cast<int>(_SCALE_FACTOR);
    }
    T poppedElement = _dataStack[_currentSize];

    T* temp_dataStack = new T[_capacity];
    for (unsigned int i = 0; i < _currentSize; i++) {
        temp_dataStack[i] = _dataStack[i];
    }
    delete[] _dataStack;
    _dataStack = temp_dataStack;
    return poppedElement;
}

template<typename T>
T ABS<T>::peek() {
    if (_currentSize == 0) {
        throw std::runtime_error("Stack is empty");
    }

    return _dataStack[_currentSize - 1];
}

template<typename T>
unsigned int ABS<T>::getSize() {
    return _currentSize;
}

template<typename T>
unsigned int ABS<T>::getMaxCapacity() {
    return _capacity;
}

template<typename T>
T* ABS<T>::getData() {
    return _dataStack;
}
