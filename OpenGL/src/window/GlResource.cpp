#include "GlResource.hpp"
#include "GlContext.hpp"
#include "Mutex.hpp"
#include "Lock.hpp"


namespace
{
    // OpenGL resources counter and its mutex
    unsigned int count = 0;
    Mutex mutex;
}

GlResource::GlResource()
{
    {
        // Protect from concurrent access
        Lock lock(mutex);

        // If this is the very first resource, trigger the global context initialization
        if (count == 0)
            priv::GlContext::globalInit();

        // Increment the resources counter
        count++;
    }

    // Now make sure that there is an active OpenGL context in the current thread
    priv::GlContext::ensureContext();
}

GlResource::~GlResource()
{
    // Protect from concurrent access
    Lock lock(mutex);

    // Decrement the resources counter
    count--;

    // If there's no more resource alive, we can trigger the global context cleanup
    if (count == 0)
        priv::GlContext::globalCleanup();
}

void GlResource::ensureGlContext()
{
    priv::GlContext::ensureContext();
}