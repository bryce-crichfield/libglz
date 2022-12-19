#include <iostream>

#include "window.h"


int main(void) {
    gl::WindowManager &manager = gl::WindowManager::instance();
    gl::Window &window = manager.create();
    window.title("Hello World");
    window.width(800);
    window.height(600);
    window.isVisible(true);
    window.awaitEvents();

    while (!window.isClosed()) {
        window.pollEvents();
        window.flush();
    }
    return 0;
}