#include "ThreadLocalImpl.hpp"

namespace priv
{
ThreadLocalImpl::ThreadLocalImpl()
{
    m_index = TlsAlloc();
}

ThreadLocalImpl::~ThreadLocalImpl()
{
    TlsFree(m_index);
}

void ThreadLocalImpl::setValue(void* value)
{
    TlsSetValue(m_index, value);
}

void* ThreadLocalImpl::getValue() const
{
    return TlsGetValue(m_index);
}

}