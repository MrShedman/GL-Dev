#pragma once

#include "Config.h"
#include "ContextSettings.hpp"
#include "NonCopyable.hpp"

namespace priv
{
class WindowImplWin32;

class GlContext : NonCopyable
{
public:

    static void globalInit();

    static void globalCleanup();

    static void ensureContext();

    static GlContext* create();

	static GlContext* create(const ContextSettings& settings, const WindowImplWin32* owner, unsigned int bitsPerPixel);

    static GlContext* create(const ContextSettings& settings, unsigned int width, unsigned int height);

public:

    virtual ~GlContext();

    const ContextSettings& getSettings() const;

    bool setActive(bool active);

    virtual void display() = 0;

    virtual void setVerticalSyncEnabled(bool enabled) = 0;

protected :

    GlContext();

    virtual bool makeCurrent() = 0;

    static int evaluateFormat(unsigned int bitsPerPixel, const ContextSettings& settings, int colorBits, int depthBits, int stencilBits, int antialiasing);

    ContextSettings m_settings;

private:

    void initialize();
};

}