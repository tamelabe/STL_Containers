#include "s21_vector.h"

template <class T>
s21::Vector<T>::Vector() : 
    m_size(0U), m_capacity(0U), storage(nullptr) {}

template <class T>
s21::Vector<T>::Vector(s21::Vector<T>::size_type n) : 
    m_size(n), m_capacity(n), storage(n ? new T[n] : nullptr)
{
    for (Vector::size_type i = 0; i < n; i++)
        this->storage[i] = T();
}

template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::size() const noexcept
{
    return m_size;
}

template <class T>
T * s21::Vector<T>::data()
{
    return storage;
}