cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(libglz STATIC ${SOURCES})
target_include_directories(libglz PUBLIC "inc")
target_include_directories(libglz PUBLIC "lib/inc")
target_link_libraries(libglz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/bin/libglfw3.a X11 GL)
target_link_directories(libglz PUBLIC "lib/bin")

add_executable(testmath "testmath.cpp")
target_include_directories(testmath PUBLIC "inc")
target_link_libraries(testmath PUBLIC libglz)

add_executable(testwindow "testwindow.cpp")
target_include_directories(testwindow PUBLIC "inc")
target_link_libraries(testwindow PUBLIC libglz)