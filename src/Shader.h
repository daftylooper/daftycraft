#pragma once
#include <string>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Macros.h"

struct ShaderSource{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader{
    private:
        const std::string m_FilePath;
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        int GetUniformLocation(const std::string& name);
        ShaderSource ParseShader();
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetUniform1i(const std::string& name, int value);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};