#pragma once

#include "NonCopyable.hpp"
#include <cstdlib>

namespace priv
{
    class ThreadImpl;
    struct ThreadFunc;
}

class Thread : NonCopyable
{
public :

    template <typename F>
    Thread(F function);

    template <typename F, typename A>
    Thread(F function, A argument);

    template <typename C>
    Thread(void(C::*function)(), C* object);

    ~Thread();

    void launch();

    void wait();

    void terminate();

private :

    friend class priv::ThreadImpl;

    void run();

    priv::ThreadImpl* m_impl;
    priv::ThreadFunc* m_entryPoint; 
};

#include "Thread.inl"