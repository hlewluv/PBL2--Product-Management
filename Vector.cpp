#include "Vector.h"
#include "MatHang.h"
#include "PhieuNhap.h"


template<typename T>
Vector<T>::Vector() {
    this->p = nullptr;
    this->size = 0;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] p;
}

template<typename T>
T& Vector<T>::operator[](const int& index) {
    if (index >= size || index < 0) {
        return p[0];
    }
    return p[index];
}

template<typename T>
void Vector<T>::push_back(const T& temp) {
    T* new_p = new T[size + 1];
    for (int i = 0; i < size; i++) {
        new_p[i] = p[i];
    }
    new_p[size] = temp;
    delete[] p;
    p = new_p;
    size++;
}

template<typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        T* new_p = new T[size - 1];
        for (int i = 0; i < size - 1; i++) {
            new_p[i] = p[i];
        }
        delete[] p;
        p = new_p;
        size--;
    }
}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    if (this != &v) {
        delete[] p;
        size = v.size;
        p = new T[size];
        for (int i = 0; i < size; i++) {
            p[i] = v.p[i];
        }
    }
    return *this;
}

template<typename T>
void Vector<T>::erase(const int& index) {
    if (index >= 0 && index < size) {
        for (int i = index; i < size - 1; i++) {
            p[i] = p[i + 1];
        }
        size--;
    }
}

template<typename T>
int Vector<T>::getSize() const {
    return size;
}

template class Vector<MatHang>;
template class Vector<PhieuNhap>;

