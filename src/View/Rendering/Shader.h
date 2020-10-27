#ifndef ZOMBIEGAME_SHADER_H
#define ZOMBIEGAME_SHADER_H

#include <glad.h>

#include <iostream>
#include <string>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
    Shader();
    ~Shader();

    unsigned int ID;

    Shader& Use();
    void Compile();

    void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);

    void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

private:

    static void checkCompileErrors(unsigned int object, const std::string& type);

    const char* m_vertexSource;
    const char* m_fragmentSource;
};

#endif //ZOMBIEGAME_SHADER_H
