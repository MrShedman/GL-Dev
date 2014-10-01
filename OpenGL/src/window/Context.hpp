#pragma once

#include "GlResource.hpp"
#include "ContextSettings.hpp"
#include "NonCopyable.hpp"



namespace priv
{
    class GlContext;
}

class Context : GlResource, NonCopyable
{
public:

    Context();

    ~Context();

    bool setActive(bool active);

public:

    Context(const ContextSettings& settings, unsigned int width, unsigned int height);

private:
	  
    priv::GlContext* m_context;
};