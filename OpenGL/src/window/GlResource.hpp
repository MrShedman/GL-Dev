#pragma once

class GlResource
{
protected:

    GlResource();

    ~GlResource();

    static void ensureGlContext();
};