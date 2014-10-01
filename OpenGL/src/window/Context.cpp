#include "Context.hpp"
#include "GlContext.hpp"

Context::Context()
{
    m_context = priv::GlContext::create();
    setActive(true);
}

Context::~Context()
{
    delete m_context;
}

bool Context::setActive(bool active)
{
    return m_context->setActive(active);
}

Context::Context(const ContextSettings& settings, unsigned int width, unsigned int height)
{
    m_context = priv::GlContext::create(settings, width, height);
    setActive(true);
}
