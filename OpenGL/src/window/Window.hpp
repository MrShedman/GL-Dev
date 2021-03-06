#pragma once

#include "ContextSettings.hpp"
#include "VideoMode.hpp"
#include "WindowStyle.hpp"
#include "GlResource.hpp"
#include "math\Vector.h"
#include "Clock.h"
#include "NonCopyable.hpp"
#include "Config.h"
#include "OpenGL.hpp"

namespace priv
{
    class GlContext;
	class WindowImplWin32;
}

class Event;

class Window : GlResource, NonCopyable
{
public:

    Window();

    Window(VideoMode mode, const std::string& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings());

    explicit Window(WindowHandle handle, const ContextSettings& settings = ContextSettings());

    virtual ~Window();

    void create(VideoMode mode, const std::string& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings());

    void create(WindowHandle handle, const ContextSettings& settings = ContextSettings());

	void bindAsRenderTarget() const;

    void close();

    bool isOpen() const;

    const ContextSettings& getSettings() const;

    bool pollEvent(Event& event);

    bool waitEvent(Event& event);

    Vector2i getPosition() const;

    void setPosition(const Vector2i& position);

    Vector2i getSize() const;

	Vector2i getCentre() const;

	float getAspect() const;

    void setSize(const Vector2i& size);

    void setTitle(const std::string& title);

    void setIcon(unsigned int width, unsigned int height, const Uint8* pixels);

    void setVisible(bool visible);

    void setVerticalSyncEnabled(bool enabled);

    void setMouseCursorVisible(bool visible);

    void setKeyRepeatEnabled(bool enabled);

    void setFramerateLimit(unsigned int limit);

    bool setActive(bool active = true) const;

    void display();

	bool switchToFullscreen(const VideoMode& mode);

	bool switchToWindowed(const VideoMode& mode, Uint32 style, bool useLastSizeAndPosition);

	bool isFullscreen() const;

	void setRawMouseInput(bool flag);

	void setClippedCursor(bool clipped);

	void setDragDropAllowed(bool flag);

	bool isDragDropAllowed() const;

    WindowHandle getSystemHandle() const;

protected:

    virtual void onCreate();

    virtual void onResize();

private:

    bool filterEvent(const Event& event);

    void initialize();

	priv::WindowImplWin32*	m_impl;           ///< Platform-specific implementation of the window
    priv::GlContext*		m_context;        ///< Platform-specific implementation of the OpenGL context
    Clock					m_clock;          ///< Clock for measuring the elapsed time between frames
    Time					m_frameTimeLimit; ///< Current framerate limit
    Vector2i				m_size;           ///< Current size of the window
};