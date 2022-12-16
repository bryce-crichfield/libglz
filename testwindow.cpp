#include <iostream>

#include "window/window.h"

void testMultWindows() {
    gl::WindowFactory& factory = gl::WindowFactory::instance();

    gl::Window& w1 = factory.create();
    w1.title("w1");
    w1.width(300);
    w1.height(300);
    w1.isVisible(true);
    w1.makeCurrent();
    w1.awaitEvents();

    gl::Window& w2 = factory.create();
    w2.title("w2");
    w2.width(300);
    w2.height(300);
    w2.isVisible(true);
    w2.makeCurrent();
    w2.awaitEvents();
    auto closed = false;
    while (!closed) {
        w1.makeCurrent();
        w1.pollEvents();
        w2.makeCurrent();
        w2.pollEvents();

        w1.makeCurrent();
        w1.flush();
        w2.makeCurrent();
        w2.flush();
        closed = w1.isClosed() || w2.isClosed();
    }
}

void testCallbacks() {
    gl::WindowFactory& factory = gl::WindowFactory::instance();

    gl::Window& w1 = factory.create();

    w1.isVisible(true);
    w1.makeCurrent();
    w1.awaitEvents();
    w1.onMove([](gl::event::Move move) {
        std::cout << "mouse moved to " << move.x << ", " << move.y << std::endl;
    });

    while (!w1.isClosed()) {
        w1.pollEvents();
        w1.flush();
    }
}

int main(void) {
    testCallbacks();
    return 0;
}