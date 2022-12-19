#include "m4.h"
#include "v2.h"
#include <iostream> 

using namespace gl;

int main(void) {
    gl::v2 a(1, 2);
    gl::v3 b(a, 1);
    gl::v4 c(a, 1, 1);
    std::cout << c.to_string() << std::endl;
    return 0;
}