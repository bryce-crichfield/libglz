cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)

function (module_define module_name)
    set(MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/${module_name})
    file(GLOB_RECURSE MODULE_SOURCES ${MODULE_DIR}/src/*.cpp)
    add_library(${module_name} STATIC ${MODULE_SOURCES})
    target_include_directories(${module_name} PUBLIC ${MODULE_DIR}/inc)
endfunction()

function (module_link_internal module_name library_name)
    target_include_directories(${module_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/${library_name}/inc/)
    target_link_libraries(${module_name} PUBLIC ${library_name})
endfunction()

function (module_link_imported module_name library_name)
    target_include_directories(${module_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/inc/${library_name})
    target_link_libraries(${module_name} PUBLIC ${library_name})
endfunction()

function(module_link_dynamic module_name library_name)
    target_link_libraries(${module_name} PUBLIC ${library_name})
endfunction()

function (module_test module_name test_name)
    set(MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/${module_name})
    add_executable(${test_name} ${MODULE_DIR}/test/${test_name}.cpp)
    target_include_directories(${test_name} PUBLIC ${MODULE_DIR}/inc)
    target_link_libraries(${test_name} PUBLIC ${module_name})
endfunction()

# Imported Libraries
add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/bin/libglfw3.a)

add_library(glad SHARED IMPORTED)
set_target_properties(glad PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/bin/libglad.a)

# Math Module
module_define(math)
module_test(math test_math)

# Window Module
module_define(window)
module_link_internal(window math)
module_link_imported(window glfw)
module_link_dynamic(window X11)
module_test(window test_window)


