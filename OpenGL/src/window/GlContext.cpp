#include "GlContext.hpp"
#include "ThreadLocalPtr.hpp"
#include "Mutex.hpp"
#include "Lock.hpp"
#include "OpenGL.hpp"
#include "glext.h"
#include <set>
#include <cstdlib>
#include <cassert>
#include "WglContext.hpp"

typedef priv::WglContext ContextType;


namespace
{
    // This per-thread variable holds the current context for each thread
    ThreadLocalPtr<priv::GlContext> currentContext(NULL);

    // The hidden, inactive context that will be shared with all other contexts
    ContextType* sharedContext = NULL;

    // Internal contexts
    ThreadLocalPtr<priv::GlContext> internalContext(NULL);
    std::set<priv::GlContext*> internalContexts;
    Mutex internalContextsMutex;

    // Check if the internal context of the current thread is valid
    bool hasInternalContext()
    {
        // The internal context can be null...
        if (!internalContext)
            return false;

        // ... or non-null but deleted from the list of internal contexts
        Lock lock(internalContextsMutex);
        return internalContexts.find(internalContext) != internalContexts.end();
    }

    // Retrieve the internal context for the current thread
    priv::GlContext* getInternalContext()
    {
        if (!hasInternalContext())
        {
            internalContext = priv::GlContext::create();
            Lock lock(internalContextsMutex);
            internalContexts.insert(internalContext);
        }

        return internalContext;
    }
}

namespace priv
{

	void GlContext::globalInit()
	{
		// Create the shared context
		sharedContext = new ContextType(NULL);
		sharedContext->initialize();

		// This call makes sure that:
		// - the shared context is inactive (it must never be)
		// - another valid context is activated in the current thread
		sharedContext->setActive(false);
	}

	void GlContext::globalCleanup()
	{
		// Destroy the shared context
		delete sharedContext;
		sharedContext = NULL;

		// Destroy the internal contexts
		Lock lock(internalContextsMutex);
		for (std::set<GlContext*>::iterator it = internalContexts.begin(); it != internalContexts.end(); ++it)
			delete *it;
		internalContexts.clear();
	}

	void GlContext::ensureContext()
	{
		// If there's no active context on the current thread, activate an internal one
		if (!currentContext)
			getInternalContext()->setActive(true);
	}

	GlContext* GlContext::create()
	{
		GlContext* context = new ContextType(sharedContext);
		context->initialize();

		return context;
	}

	GlContext* GlContext::create(const ContextSettings& settings, const WindowImplWin32* owner, unsigned int bitsPerPixel)
	{
		// Make sure that there's an active context (context creation may need extensions, and thus a valid context)
		ensureContext();

		// Create the context
		GlContext* context = new ContextType(sharedContext, settings, owner, bitsPerPixel);
		context->initialize();

		return context;
	}

	GlContext* GlContext::create(const ContextSettings& settings, unsigned int width, unsigned int height)
	{
		// Make sure that there's an active context (context creation may need extensions, and thus a valid context)
		ensureContext();

		// Create the context
		GlContext* context = new ContextType(sharedContext, settings, width, height);
		context->initialize();

		return context;
	}

	GlContext::~GlContext()
	{
		// Deactivate the context before killing it, unless we're inside Cleanup()
		if (sharedContext)
			setActive(false);
	}

	const ContextSettings& GlContext::getSettings() const
	{
		return m_settings;
	}

	bool GlContext::setActive(bool active)
	{
		if (active)
		{
			if (this != currentContext)
			{
				// Activate the context
				if (makeCurrent())
				{
					// Set it as the new current context for this thread
					currentContext = this;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				// This context is already the active one on this thread, don't do anything
				return true;
			}
		}
		else
		{
			if (this == currentContext)
			{
				// To deactivate the context, we actually activate another one so that we make
				// sure that there is always an active context for subsequent graphics operations
				return getInternalContext()->setActive(true);
			}
			else
			{
				// This context is not the active one on this thread, don't do anything
				return true;
			}
		}
	}

	GlContext::GlContext()
	{
		// Nothing to do
	}

	int GlContext::evaluateFormat(unsigned int bitsPerPixel, const ContextSettings& settings, int colorBits, int depthBits, int stencilBits, int antialiasing)
	{
		return std::abs(static_cast<int>(bitsPerPixel - colorBits)) +
			std::abs(static_cast<int>(settings.depthBits - depthBits)) +
			std::abs(static_cast<int>(settings.stencilBits - stencilBits)) +
			std::abs(static_cast<int>(settings.antialiasingLevel - antialiasing));
	}

	void GlContext::initialize()
	{
		// Activate the context
		setActive(true);

		// Retrieve the context version number
		const GLubyte* version = glGetString(GL_VERSION);
		if (version)
		{
			// The beginning of the returned string is "major.minor" (this is standard)
			m_settings.majorVersion = version[0] - '0';
			m_settings.minorVersion = version[2] - '0';
		}
		else
		{
			// Can't get the version number, assume 2.0
			m_settings.majorVersion = 2;
			m_settings.minorVersion = 0;
		}

		// Enable antialiasing if needed
		if (m_settings.antialiasingLevel > 0)
			glEnable(GL_MULTISAMPLE_ARB);
	}
}