////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include "GlContext.hpp"
#include "OpenGL.hpp"
#include <windows.h>

namespace priv
{

class WglContext : public GlContext
{
public:
	  
    WglContext(WglContext* shared);

	WglContext(WglContext* shared, const ContextSettings& settings, const WindowImplWin32* owner, unsigned int bitsPerPixel);

    WglContext(WglContext* shared, const ContextSettings& settings, unsigned int width, unsigned int height);

    ~WglContext();

    virtual bool makeCurrent();

    virtual void display();

    virtual void setVerticalSyncEnabled(bool enabled);

private:

    void createContext(WglContext* shared, unsigned int bitsPerPixel, const ContextSettings& settings);

    HWND  m_window;        ///< Window to which the context is attached
    HDC   m_deviceContext; ///< Device context associated to the context
    HGLRC m_context;       ///< OpenGL context
    bool  m_ownsWindow;    ///< Do we own the target window?
};

}