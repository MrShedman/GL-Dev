#pragma once

#include "NonCopyable.hpp"
#include <cstdlib>

namespace priv
{
    class ThreadLocalImpl;
}


class ThreadLocal : NonCopyable
{
public:

    ThreadLocal(void* value = NULL);

    ~ThreadLocal();

    void setValue(void* value);

    void* getValue() const;

private:

    priv::ThreadLocalImpl* m_impl;
};