#include <iostream>

#include "window/window.h"
int main(void) {
    gl::Window& window = gl::Window::init();
    window.title("Test Window");
    window.width(800);
    window.height(600);
    window.visible(true);

    window.onButton([&](gl::event::Button event) {
        if (event.button == gl::input::Button::Left &&
            event.action == gl::input::Action::Press) {
            std::cout << "Left mouse button pressed" << std::endl;
        }
    });

    window.onKey([&](gl::event::Key event) {
        if (event.key == gl::input::Key::Escape &&
            event.action == gl::input::Action::Press) {
            window.closed(true);
        }
    });

    window.awaitEvents();
    while (!window.closed()) {
        window.pollEvents();
        window.flush();
    }
    return 0;
}