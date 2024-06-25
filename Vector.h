#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

template<typename T>
class Vector {
private:
    T *p;
    int size;

public:
    Vector();
    ~Vector();
    
    void push_back(const T&);
    void pop_back();
    T& operator[](const int&);
    Vector<T>& operator=(const Vector<T>&);
    void erase(const int&);
    int getSize() const;
}; 

#endif // VECTOR_H

