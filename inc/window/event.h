#pragma once
#include "input.h"
/* -------------------------------------------------------------------------- */
/*                                 Event Types                                */
/* -------------------------------------------------------------------------- */
namespace gl::event {
struct Button {
    gl::input::Button button;
    gl::input::Action action;
    int modifiers;
};

struct Move {
    double x;
    double y;
};

struct Key {
    gl::input::Key key;
    gl::input::Action action;
    int modifiers;
};

struct Scroll {
    double x;
    double y;
};

struct Resize {
    int width;
    int height;
};

struct Focus {
    int focused;
};

struct Close {
    bool closed;
};

struct FrameBufferResize {
    int width;
    int height;
};

struct Refresh {
    bool refreshed;
};

struct Position {
    int x;
    int y;
};
} // namespace gl::event
