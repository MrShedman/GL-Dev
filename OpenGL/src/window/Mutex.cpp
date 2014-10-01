#pragma once

#include "Mutex.hpp"
#include "MutexImpl.hpp"

Mutex::Mutex()
{
    m_mutexImpl = new priv::MutexImpl;
}

Mutex::~Mutex()
{
    delete m_mutexImpl;
}

void Mutex::lock()
{
    m_mutexImpl->lock();
}

void Mutex::unlock()
{
    m_mutexImpl->unlock();
}