#pragma once

#include "NonCopyable.hpp"
#include <windows.h>

namespace priv
{

class ThreadLocalImpl : NonCopyable
{
public:

    ThreadLocalImpl();

    ~ThreadLocalImpl();

    void setValue(void* value);

    void* getValue() const;

private:

    DWORD m_index;
};

}