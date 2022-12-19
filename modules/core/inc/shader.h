#pragma once
#include "platform.h"
#include "error.h"
#include <exception>
#include <string>
#include "program.h"


namespace gl {

class Shader {
  protected:
    friend class Program;
    GlPointer m_pointer;
    Shader() = default;
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;
    
  public:
    Shader(ShaderType type);
    ~Shader();
    void source(std::string& code);
    void compile();
    std::string infoLog();
};

} // namespace gl

