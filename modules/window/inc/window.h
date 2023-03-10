#pragma once
#include "event.h"
#include <functional>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

/* -------------------------------------------------------------------------- */
/*                                   Window                                   */
/* -------------------------------------------------------------------------- */
namespace gl {
class WindowManager;
class Window;

// Singleton object responsible for the lifetime of all windows
// and the underlying windowing context.  Windows cannot be created
// or exist outside the lifetime of this object.
class WindowManager {
  private:
    WindowManager();
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

  public:
    // Returns a pointer to the singleton instance of the WindowManager
    // object. The pointer may be shared by others.
    static WindowManager& instance();
    ~WindowManager();
    Window& create();
};

class Window {
  private:
    GLFWwindow* m_pointer;
    std::string m_title = std::string("");
    std::function<void(gl::event::Move)> m_move_callback;
    std::function<void(gl::event::Button)> m_button_callback;
    std::function<void(gl::event::Key)> m_key_callback;
    std::function<void(gl::event::Scroll)> m_scroll_callback;
    std::function<void(gl::event::Resize)> m_resize_callback;
    std::function<void(gl::event::Focus)> m_focus_callback;
    std::function<void(gl::event::Close)> m_close_callback;
    std::function<void(gl::event::FrameBufferResize)> m_framebuffer_resize_callback;
    std::function<void(gl::event::Position)> m_position_callback;
    Window() = delete;
    friend class WindowManager;

    Window(GLFWwindow* pointer);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

  public:
    ~Window();
    /* --------------------------------- Methods -------------------------------- */
    void makeCurrent();
    void awaitEvents();
    void pollEvents();
    void flush();
    /* ------------------------------- Properties ------------------------------- */
    std::string title();
    void title(std::string title);
    int width();
    void width(int width);
    int height();
    void height(int height);
    int x();
    void x(int x);
    int y();
    void y(int y);
    /* ---------------------------------- Flags --------------------------------- */
    bool isVisible();
    void isVisible(bool enable);
    bool isResizable();
    void isResizable(bool enable);
    bool isIconified();
    void isIconified(bool enable);
    bool isMaximized();
    void isMaximized(bool enable);
    bool isMinimized();
    void isMinimized(bool enable);
    bool isFocused();
    void isFocused(bool enable);
    bool isClosed();
    void isClosed(bool enable);
    bool hasCursor();
    void hasCursor(bool enable);
    bool isDecorated();
    void isDecorated(bool enable);
    /* ----------------------------- Input Callbacks ---------------------------- */
    void onMove(std::function<void(gl::event::Move)> callback);
    void onButton(std::function<void(gl::event::Button)> callback);
    void onKey(std::function<void(gl::event::Key)> callback);
    void onScroll(std::function<void(gl::event::Scroll)> callback);
    /* ---------------------------- Window Callbacks ---------------------------- */
    void onResize(std::function<void(gl::event::Resize)> callback);
    void onFocus(std::function<void(gl::event::Focus)> callback);
    void onClose(std::function<void(gl::event::Close)> callback);
    void onFramebufferResize(std::function<void(gl::event::FrameBufferResize)> callback);
    void onPosition(std::function<void(gl::event::Position)> callback);
};
} // namespace gl
