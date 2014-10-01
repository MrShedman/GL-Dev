#pragma once

#include "NonCopyable.hpp"
#include <windows.h>

namespace priv
{

class MutexImpl : NonCopyable
{
public :

    MutexImpl();

    ~MutexImpl();

    void lock();

    void unlock();

private :

    CRITICAL_SECTION m_mutex; ///< Win32 handle of the mutex
};

}