#include "window/window.h"
#include <glfw/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <string>

/* -------------------------------------------------------------------------- */
/*                               Window Factory                               */
/* -------------------------------------------------------------------------- */

gl::WindowFactory::WindowFactory() {
    auto errorCallback = [](int error, const char* description) {
        std::cout << "GLFW Error: " << description << std::endl;
    };
    glfwSetErrorCallback(errorCallback);

    glfwInit();
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }
}

gl::WindowFactory::~WindowFactory() {
    glfwTerminate();
    glfwSetErrorCallback(NULL);
}

static gl::WindowFactory* window_factory_instance;
gl::WindowFactory& gl::WindowFactory::instance() {
    if (!window_factory_instance) {
        window_factory_instance = new gl::WindowFactory();
    }
    return *window_factory_instance;
}

gl::Window& gl::WindowFactory::create() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    auto pointer = glfwCreateWindow(300, 300, "", NULL, NULL);
    if (!pointer) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    return *(new gl::Window(pointer));
}

/* -------------------------------------------------------------------------- */
/*                                   Window                                   */
/* -------------------------------------------------------------------------- */

gl::Window::Window(GLFWwindow* pointer) {
    m_pointer = pointer;
    glfwSetWindowUserPointer(m_pointer, this);
}

gl::Window::~Window() {
    glfwDestroyWindow((GLFWwindow*)m_pointer);
}

/* -------------------------------------------------------------------------- */
/*                              Member Functions                              */
/* -------------------------------------------------------------------------- */

void gl::Window::makeCurrent() {
    glfwMakeContextCurrent((GLFWwindow*)m_pointer);
}

void gl::Window::awaitEvents() {
    glfwWaitEvents();
}

void gl::Window::pollEvents() {
    glfwPollEvents();
}

void gl::Window::flush() {
    glfwSwapBuffers(m_pointer);
}

/* -------------------------------------------------------------------------- */
/*                                 Properties                                 */
/* -------------------------------------------------------------------------- */

std::string gl::Window::title() {
    return m_title;
}

void gl::Window::title(std::string title) {
    m_title = title;
    glfwSetWindowTitle(m_pointer, title.c_str());
}

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
/*                                    Flags                                   */
/* -------------------------------------------------------------------------- */

bool gl::Window::isVisible() {
    return glfwGetWindowAttrib(m_pointer, GLFW_VISIBLE);
}

void gl::Window::isVisible(bool enable) {
    enable ? glfwShowWindow(m_pointer) : glfwHideWindow(m_pointer);
}

bool gl::Window::isResizable() {
    return glfwGetWindowAttrib(m_pointer, GLFW_RESIZABLE);
}

void gl::Window::isResizable(bool enable) {
    glfwSetWindowAttrib(m_pointer, GLFW_RESIZABLE, enable);
}

bool gl::Window::isMaximized() {
    return glfwGetWindowAttrib(m_pointer, GLFW_MAXIMIZED);
}

void gl::Window::isMaximized(bool enable) {
    enable ? glfwMaximizeWindow(m_pointer) : glfwRestoreWindow(m_pointer);
}

bool gl::Window::isMinimized() {
    return glfwGetWindowAttrib(m_pointer, GLFW_ICONIFIED);
}

void gl::Window::isMinimized(bool enable) {
    enable ? glfwIconifyWindow(m_pointer) : glfwRestoreWindow(m_pointer);
}

bool gl::Window::isFocused() {
    return glfwGetWindowAttrib(m_pointer, GLFW_FOCUSED);
}
void gl::Window::isFocused(bool enable) {
    enable ? glfwFocusWindow(m_pointer) : glfwFocusWindow(NULL);
}

bool gl::Window::isClosed() {
    return glfwWindowShouldClose(m_pointer);
}

void gl::Window::isClosed(bool enable) {
    if (enable) glfwSetWindowShouldClose(m_pointer, true);
}

bool gl::Window::hasCursor() {
    return glfwGetInputMode(m_pointer, GLFW_CURSOR);
}

void gl::Window::hasCursor(bool enable) {
    glfwSetInputMode(m_pointer, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

bool gl::Window::isDecorated() {
    return glfwGetWindowAttrib(m_pointer, GLFW_DECORATED);
}

void gl::Window::isDecorated(bool enable) {
    glfwSetWindowAttrib(m_pointer, GLFW_DECORATED, enable);
}

/* -------------------------------------------------------------------------- */
/*                               Input Callbacks                              */
/* -------------------------------------------------------------------------- */

void gl::Window::onMove(std::function<void(gl::event::Move)> callback) {
    m_move_callback = callback;
    auto moveCallback = [](GLFWwindow* window, double x, double y) {
        gl::event::Move event = {.x = x, .y = y};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_move_callback(event);
    };
    glfwSetCursorPosCallback(m_pointer, moveCallback);
}

void gl::Window::onButton(std::function<void(gl::event::Button)> callback) {
    m_button_callback = callback;
    auto buttonCallback = [](GLFWwindow* window, int button, int action, int mods) {
        gl::event::Button event = {
            .button = gl::input::Button(button),
            .action = gl::input::Action(action),
            .modifiers = mods,
        };
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_button_callback(event);
    };
    glfwSetMouseButtonCallback(m_pointer, buttonCallback);
}

void gl::Window::onKey(std::function<void(gl::event::Key)> callback) {
    m_key_callback = callback;
    auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        gl::event::Key event = {
            .key = gl::input::Key(key),
            .action = gl::input::Action(action),
            .modifiers = mods,
        };
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_key_callback(event);
    };
    glfwSetKeyCallback(m_pointer, keyCallback);
}

void gl::Window::onScroll(std::function<void(gl::event::Scroll)> callback) {
    m_scroll_callback = callback;
    auto scrollCallback = [](GLFWwindow* window, double x, double y) {
        gl::event::Scroll event = {.x = x, .y = y};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_scroll_callback(event);
    };
    glfwSetScrollCallback(m_pointer, scrollCallback);
}

/* -------------------------------------------------------------------------- */
/*                               Window Callback                              */
/* -------------------------------------------------------------------------- */

void gl::Window::onResize(std::function<void(gl::event::Resize)> callback) {
    m_resize_callback = callback;
    auto resizeCallback = [](GLFWwindow* window, int width, int height) {
        gl::event::Resize event = {.width = width, .height = height};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_resize_callback(event);
    };
    glfwSetWindowSizeCallback(m_pointer, resizeCallback);
}

void gl::Window::onFocus(std::function<void(gl::event::Focus)> callback) {
    m_focus_callback = callback;
    auto focusCallback = [](GLFWwindow* window, int focused) {
        gl::event::Focus event = {.focused = focused};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_focus_callback(event);
    };
    glfwSetWindowFocusCallback(m_pointer, focusCallback);
}

void gl::Window::onClose(std::function<void(gl::event::Close)> callback) {
    m_close_callback = callback;
    auto closeCallback = [](GLFWwindow* window) {
        gl::event::Close event = {};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_close_callback(event);
    };
    glfwSetWindowCloseCallback(m_pointer, closeCallback);
}

void gl::Window::onFramebufferResize(std::function<void(gl::event::FrameBufferResize)> callback) {
    m_framebuffer_resize_callback = callback;
    auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height) {
        gl::event::FrameBufferResize event = {.width = width, .height = height};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_framebuffer_resize_callback(event);
    };
    glfwSetFramebufferSizeCallback(m_pointer, framebufferResizeCallback);
}

void gl::Window::onPosition(std::function<void(gl::event::Position)> callback) {
    m_position_callback = callback;
    auto positionCallback = [](GLFWwindow* window, int x, int y) {
        gl::event::Position event = {.x = x, .y = y};
        gl::Window* self = (gl::Window*)glfwGetWindowUserPointer(window);
        self->m_position_callback(event);
    };
    glfwSetWindowPosCallback(m_pointer, positionCallback);
}