#pragma once

#include "ThreadLocal.hpp"

template <typename T>
class ThreadLocalPtr : private ThreadLocal
{
public:

    ThreadLocalPtr(T* value = NULL);

    T& operator *() const;

    T* operator ->() const;

    operator T*() const;

    ThreadLocalPtr<T>& operator =(T* value);

    ThreadLocalPtr<T>& operator =(const ThreadLocalPtr<T>& right);
};

#include "ThreadLocalPtr.inl"