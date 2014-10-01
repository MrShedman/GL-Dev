#include "MutexImpl.hpp"



namespace priv
{

MutexImpl::MutexImpl()
{
    InitializeCriticalSection(&m_mutex);
}

MutexImpl::~MutexImpl()
{
    DeleteCriticalSection(&m_mutex);
}

void MutexImpl::lock()
{
    EnterCriticalSection(&m_mutex);
}


void MutexImpl::unlock()
{
    LeaveCriticalSection(&m_mutex);
}

}