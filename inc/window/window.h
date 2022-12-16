#pragma once

#include "event.h"
#include <functional>
#include <glfw/glfw3.h>

/* -------------------------------------------------------------------------- */
/*                                   Window                                   */
/* -------------------------------------------------------------------------- */
namespace gl {
class Window {
  public:
  private:
    GLFWwindow* m_pointer;

    std::function<void(gl::event::Move)> m_move_callback;
    std::function<void(gl::event::Button)> m_button_callback;
    std::function<void(gl::event::Key)> m_key_callback;
    std::function<void(gl::event::Scroll)> m_scroll_callback;
    std::function<void(gl::event::Resize)> m_resize_callback;
    std::function<void(gl::event::Focus)> m_focus_callback;
    std::function<void(gl::event::Close)> m_close_callback;
    std::function<void(gl::event::FrameBufferResize)> m_framebuffer_resize_callback;
    std::function<void(gl::event::Position)> m_position_callback;

    Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

  public:
    static Window& init();
    ~Window();

    void awaitEvents();
    void pollEvents();
    void flush();

    void title(const char* title);

    int width();
    void width(int width);

    int height();
    void height(int height);

    int x();
    void x(int x);

    int y();
    void y(int y);

    bool visible();
    void visible(bool visible);

    bool resizable();
    void resizable(bool resizable);

    bool cursor();
    void cursor(bool cursor);

    void iconify(bool iconified);
    void maximize(bool maximized);
    void minimize(bool minimized);
    void focus(bool focused);

    bool closed();
    void closed(bool active);

    // Input Callbacks
    void onMove(std::function<void(gl::event::Move)> callback);
    void onButton(std::function<void(gl::event::Button)> callback);
    void onKey(std::function<void(gl::event::Key)> callback);
    void onScroll(std::function<void(gl::event::Scroll)> callback);

    // Window Callbacks
    void onResize(std::function<void(gl::event::Resize)> callback);
    void onFocus(std::function<void(gl::event::Focus)> callback);
    void onClose(std::function<void(gl::event::Close)> callback);
    void onFramebufferResize(std::function<void(gl::event::FrameBufferResize)> callback);
    void onPosition(std::function<void(gl::event::Position)> callback);
};
} // namespace gl
