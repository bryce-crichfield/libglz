#pragma once
#include <string>
#include <vector>
#include "shader.h"

#include "platform.h"
#include "math/m4.h"
#include "math/v4.h"
#include "math/v3.h"
#include "math/v2.h"


namespace gl {
    class Program {
    private:
        GlPointer m_pointer;
        Program(const Program& other) = delete;
        Program& operator=(const Program& other) = delete;
        
    public:
        Program();
        ~Program();
        // void attach(const Shader& shader);
        void link();
        std::string infoLog();

        void use();

        Attribute attribute(std::string name);

        Uniform uniform(std::string name);
        void uniform(Uniform uniform, int value);
        void uniform(Uniform uniform, float value);
        void uniform(Uniform uniform, const v2& value);
        void uniform(Uniform uniform, const v3& value);
        void uniform(Uniform uniform, const v4& value);
        void uniform(Uniform uniform, const m4& value);
        void uniform(Uniform uniform, const std::vector<int>& value);
        void uniform(Uniform uniform, const std::vector<float>& value);
    };
}