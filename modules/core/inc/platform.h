#pragma once
#include <glad/glad.h>



/* -------------------------------------------------------------------------- */
/*                            GL and Platform Types                           */
/* -------------------------------------------------------------------------- */
namespace gl {
using Attribute = GLint;
using Uniform = GLint;
using GlPointer = GLuint;
} // namespace gl

/* -------------------------------------------------------------------------- */
/*                                 Enum Types                                 */
/* -------------------------------------------------------------------------- */
namespace gl {
enum class ShaderType {
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    TessellationControl = GL_TESS_CONTROL_SHADER,
    TessellationEvaluation = GL_TESS_EVALUATION_SHADER,
    Compute = GL_COMPUTE_SHADER
};
} // namespace gl

/* -------------------------------------------------------------------------- */
/*                                 Error Types                                */
/* -------------------------------------------------------------------------- */
#include <exception>
#include <string>
#define DEFINE_ERROR(name)                                                                         \
    namespace gl::error {                                                                          \
    class name : public std::exception {                                                           \
      private:                                                                                     \
        std::string m_message;                                                                     \
                                                                                                   \
      public:                                                                                      \
        name(const std::string& message) throw() : m_message(message) {}                           \
        ~name() throw() {}                                                                         \
        virtual const char* what() const throw() { return m_message.c_str(); }                     \
    };                                                                                             \
    }
DEFINE_ERROR(CompileError)
DEFINE_ERROR(LinkError)
DEFINE_ERROR(ValidateError)