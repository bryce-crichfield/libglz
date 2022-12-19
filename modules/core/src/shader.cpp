#include <string>
#include "gl/platform.h"
#include "gl/shader.h"
#include <iostream>
gl::Shader::Shader(gl::ShaderType type) {

    m_pointer = glCreateShader((GLenum)type);
}

gl::Shader::~Shader() {
    std::cout << "DESTROYING" << std::endl;
    glDeleteShader(m_pointer);
}

void gl::Shader::source(std::string& code) {
    glShaderSource(m_pointer, 1, (const GLchar* const*)code.c_str(), NULL);
}

void gl::Shader::compile() {
    glCompileShader(m_pointer);
    GLint success;
    glGetShaderiv(m_pointer, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw gl::error::CompileError(infoLog());
    }
}

std::string gl::Shader::infoLog() {
    GLint length;
    glGetShaderiv(m_pointer, GL_INFO_LOG_LENGTH, &length);
    std::string log(length, ' ');
    glGetShaderInfoLog(m_pointer, length, NULL, log.data());
    return log;
}