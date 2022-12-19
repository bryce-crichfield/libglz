#include "gl/platform.h"
#include "gl/program.h"
#include <string>
gl::Program::Program() {
    m_pointer = glCreateProgram();
}

gl::Program::~Program() {
    glDeleteProgram(m_pointer);
}

// void gl::Program::attach(const gl::Shader& shader) {
//     glAttachShader(m_pointer, shader.m_pointer);
// }

void gl::Program::link() {
    glLinkProgram(m_pointer);
    GLint success;
    glGetProgramiv(m_pointer, GL_LINK_STATUS, &success);
    if (!success) {
        throw gl::error::LinkError(infoLog());
    }
    glValidateProgram(m_pointer);
    glGetProgramiv(m_pointer, GL_VALIDATE_STATUS, &success);
    if (!success) {
        throw gl::error::ValidateError(infoLog());
    }
}

std::string gl::Program::infoLog() {
    GLint length;
    glGetProgramiv(m_pointer, GL_INFO_LOG_LENGTH, &length);
    std::string log(length, ' ');
    glGetProgramInfoLog(m_pointer, length, NULL, log.data());
    return log;
}


void gl::Program::use() {
    glUseProgram(m_pointer);
}

gl::Attribute gl::Program::attribute(std::string name) {;
    return glGetAttribLocation(m_pointer, name.c_str());
}

gl::Uniform gl::Program::uniform(std::string name) {
    return glGetUniformLocation(m_pointer, name.c_str());
}

void gl::Program::uniform(Uniform uniform, int value) {
    glUniform1i(uniform, value);
}

void gl::Program::uniform(Uniform uniform, float value) {
    glUniform1f(uniform, value);
}

void gl::Program::uniform(Uniform uniform, const v2& value) {
    glUniform2f(uniform, value.x, value.y);
}

void gl::Program::uniform(Uniform uniform, const v3& value) {
    glUniform3f(uniform, value.x, value.y, value.z);
}

void gl::Program::uniform(Uniform uniform, const v4& value) {
    glUniform4f(uniform, value.x, value.y, value.z, value.w);
}

void gl::Program::uniform(Uniform uniform, const m4& value) {
    glUniformMatrix4fv(uniform, 1, GL_FALSE, value.data);
}

void gl::Program::uniform(Uniform uniform, const std::vector<int>& value) {
    glUniform1iv(uniform, value.size(), value.data());
}

void gl::Program::uniform(Uniform uniform, const std::vector<float>& value) {
    glUniform1fv(uniform, value.size(), value.data());
}

