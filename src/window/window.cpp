#include "window/window.h"

#include <glfw/glfw3.h>

#include <cstdlib>
#include <iostream>
/* -------------------------------------------------------------------------- */
static gl::Window* m_instance;
gl::Window& gl::Window::init() {
    if (!m_instance)
        m_instance = new gl::Window();
    else {
        std::cout << "Window already exists" << std::endl;
        exit(1);
    }
    return *m_instance;
}
/* -------------------------------------------------------------------------- */
gl::Window::Window() {
    auto errorCallback = [](int error, const char* description) {
        std::cout << "GLFW Error: " << description << std::endl;
    };
    glfwSetErrorCallback(errorCallback);

    glfwInit();
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    m_pointer = glfwCreateWindow(300, 300, "", NULL, NULL);
    if (!m_pointer) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent((GLFWwindow*)m_pointer);
}
/* -------------------------------------------------------------------------- */
gl::Window::~Window() {
    glfwDestroyWindow((GLFWwindow*)m_pointer);
    glfwTerminate();
    glfwSetErrorCallback(NULL);
}
/* -------------------------------------------------------------------------- */
void gl::Window::awaitEvents() {
    glfwWaitEvents();
}
/* -------------------------------------------------------------------------- */
void gl::Window::pollEvents() {
    glfwPollEvents();
}
/* -------------------------------------------------------------------------- */
void gl::Window::flush() {
    glfwSwapBuffers(m_pointer);
}
/* -------------------------------------------------------------------------- */
void gl::Window::title(const char* title) {
    glfwSetWindowTitle(m_pointer, title);
}
/* -------------------------------------------------------------------------- */
int gl::Window::width() {
    int width;
    glfwGetWindowSize(m_pointer, &width, NULL);
    return width;
}
void gl::Window::width(int width) {
    int height;
    glfwGetWindowSize(m_pointer, NULL, &height);
    glfwSetWindowSize(m_pointer, width, height);
}
/* -------------------------------------------------------------------------- */
int gl::Window::height() {
    int height;
    glfwGetWindowSize(m_pointer, NULL, &height);
    return height;
}
void gl::Window::height(int height) {
    int width;
    glfwGetWindowSize(m_pointer, &width, NULL);
    glfwSetWindowSize(m_pointer, width, height);
}
/* -------------------------------------------------------------------------- */
int gl::Window::x() {
    int x;
    glfwGetWindowPos(m_pointer, &x, NULL);
    return x;
}
void gl::Window::x(int x) {
    int y;
    glfwGetWindowPos(m_pointer, NULL, &y);
    glfwSetWindowPos(m_pointer, x, y);
}
/* -------------------------------------------------------------------------- */
int gl::Window::y() {
    int y;
    glfwGetWindowPos(m_pointer, NULL, &y);
    return y;
}
void gl::Window::y(int y) {
    int x;
    glfwGetWindowPos(m_pointer, &x, NULL);
    glfwSetWindowPos(m_pointer, x, y);
}
/* -------------------------------------------------------------------------- */
bool gl::Window::visible() {
    return glfwGetWindowAttrib(m_pointer, GLFW_VISIBLE);
}
void gl::Window::visible(bool visible) {
    if (visible) {
        glfwShowWindow(m_pointer);
    } else {
        glfwHideWindow(m_pointer);
    }
}
/* -------------------------------------------------------------------------- */
bool gl::Window::resizable() {
    return glfwGetWindowAttrib(m_pointer, GLFW_RESIZABLE);
}
void gl::Window::resizable(bool resizable) {
    glfwSetWindowAttrib(m_pointer, GLFW_RESIZABLE, resizable);
}
/* -------------------------------------------------------------------------- */
void gl::Window::iconify(bool iconified) {
    if (iconified) {
        glfwIconifyWindow(m_pointer);
    } else {
        glfwRestoreWindow(m_pointer);
    }
}
/* -------------------------------------------------------------------------- */
void gl::Window::maximize(bool maximized) {
    if (maximized) {
        glfwMaximizeWindow(m_pointer);
    } else {
        glfwRestoreWindow(m_pointer);
    }
}
/* -------------------------------------------------------------------------- */
void gl::Window::minimize(bool minimized) {
    if (minimized) {
        glfwIconifyWindow(m_pointer);
    } else {
        glfwRestoreWindow(m_pointer);
    }
}
/* -------------------------------------------------------------------------- */
void gl::Window::focus(bool focused) {
    if (focused) {
        glfwFocusWindow(m_pointer);
    } else {
        glfwFocusWindow(NULL);
    }
}
/* -------------------------------------------------------------------------- */
bool gl::Window::closed() {
    return glfwWindowShouldClose(m_pointer);
}
void gl::Window::closed(bool closed) {
    glfwSetWindowShouldClose(m_pointer, true);
}
/* -------------------------------------------------------------------------- */
/*                               Input Callbacks                              */
/* -------------------------------------------------------------------------- */
void gl::Window::onMove(std::function<void(gl::event::Move)> callback) {
    m_instance->m_move_callback = callback;
    glfwSetCursorPosCallback(m_pointer, [](GLFWwindow* window, double x, double y) {
        gl::event::Move event = {.x = x, .y = y};
        m_instance->m_move_callback(event);
    });
}
/* -------------------------------------------------------------------------- */
void gl::Window::onButton(std::function<void(gl::event::Button)> callback) {
    m_instance->m_button_callback = callback;
    auto buttonCallback = [](GLFWwindow* window, int button, int action, int mods) {
        gl::event::Button event = {
            .button = gl::input::Button(button),
            .action = gl::input::Action(action),
            .modifiers = mods,
        };
        m_instance->m_button_callback(event);
    };
    glfwSetMouseButtonCallback(m_pointer, buttonCallback);
}
/* -------------------------------------------------------------------------- */
void gl::Window::onKey(std::function<void(gl::event::Key)> callback) {
    m_instance->m_key_callback = callback;
    auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        gl::event::Key event = {
            .key = gl::input::Key(key),
            .action = gl::input::Action(action),
            .modifiers = mods,
        };
        m_instance->m_key_callback(event);
    };
    glfwSetKeyCallback(m_pointer, keyCallback);
}
/* -------------------------------------------------------------------------- */
void gl::Window::onScroll(std::function<void(gl::event::Scroll)> callback) {
    m_instance->m_scroll_callback = callback;
    auto scrollCallback = [](GLFWwindow* window, double x, double y) {
        gl::event::Scroll event = {.x = x, .y = y};
        m_instance->m_scroll_callback(event);
    };
    glfwSetScrollCallback(m_pointer, scrollCallback);
}
/* -------------------------------------------------------------------------- */
/*                               Window Callback                              */
/* -------------------------------------------------------------------------- */
void gl::Window::onResize(std::function<void(gl::event::Resize)> callback) {
    m_instance->m_resize_callback = callback;
    auto resizeCallback = [](GLFWwindow* window, int width, int height) {
        gl::event::Resize event = {.width = width, .height = height};
        m_instance->m_resize_callback(event);
    };
    glfwSetWindowSizeCallback(m_pointer, resizeCallback);
}
/* -------------------------------------------------------------------------- */
void gl::Window::onFocus(std::function<void(gl::event::Focus)> callback) {
    m_instance->m_focus_callback = callback;
    auto focusCallback = [](GLFWwindow* window, int focused) {
        gl::event::Focus event = {.focused = focused};
        m_instance->m_focus_callback(event);
    };
    glfwSetWindowFocusCallback(m_pointer, focusCallback);
}
/* -------------------------------------------------------------------------- */
void gl::Window::onClose(std::function<void(gl::event::Close)> callback) {
    m_instance->m_close_callback = callback;
    auto closeCallback = [](GLFWwindow* window) {
        gl::event::Close event = {};
        m_instance->m_close_callback(event);
    };
    glfwSetWindowCloseCallback(m_pointer, closeCallback);
}
/* -------------------------------------------------------------------------- */
void gl::Window::onFramebufferResize(std::function<void(gl::event::FrameBufferResize)> callback) {
    m_instance->m_framebuffer_resize_callback = callback;
    auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height) {
        gl::event::FrameBufferResize event = {.width = width, .height = height};
        m_instance->m_framebuffer_resize_callback(event);
    };
    glfwSetFramebufferSizeCallback(m_pointer, framebufferResizeCallback);
}
/* -------------------------------------------------------------------------- */
void gl::Window::onPosition(std::function<void(gl::event::Position)> callback) {
    m_instance->m_position_callback = callback;
    auto positionCallback = [](GLFWwindow* window, int x, int y) {
        gl::event::Position event = {.x = x, .y = y};
        m_instance->m_position_callback(event);
    };
    glfwSetWindowPosCallback(m_pointer, positionCallback);
}
/* -------------------------------------------------------------------------- */