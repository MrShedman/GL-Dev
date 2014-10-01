#pragma once

#include "NonCopyable.hpp"

namespace priv
{
    class MutexImpl;
}

class Mutex : NonCopyable
{
public :

    Mutex();

    ~Mutex();

    void lock();

    void unlock();

private:

    priv::MutexImpl* m_mutexImpl;
};