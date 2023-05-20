#include "s21_Vector.h"

template <class T>
s21_Vector<T>::s21_Vector() : 
    m_size(0U), m_capacity(0U), arr(nullptr) {}

template <class T>
s21_Vector<T>::s21_Vector(s21_Vector::size_type n) : 
    m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}