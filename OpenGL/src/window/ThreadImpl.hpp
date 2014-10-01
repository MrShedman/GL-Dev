#pragma once

#include "NonCopyable.hpp"
#include <windows.h>

class Thread;

namespace priv
{

class ThreadImpl : NonCopyable
{
public :

    ThreadImpl(Thread* owner);

    ~ThreadImpl();

    void wait();

    void terminate();

private :

    static unsigned int __stdcall entryPoint(void* userData);

    HANDLE m_thread;
    unsigned int m_threadId;
};

}