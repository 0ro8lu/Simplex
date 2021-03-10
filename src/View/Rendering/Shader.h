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

    Shader& Use();
    void Compile();

    static unsigned int GetID() { return ID; }

    static void SetInt(const std::string &name, int value, bool useShader);

    static void SetVector3f(const std::string &name, const glm::vec3& value, bool useShader = false);
    static void SetVector3f(const std::string &name, float x, float y, float z, bool useShader = false);

    static void SetMatrix4(const std::string &name, const glm::mat4& matrix, bool useShader = false);

private:

    static void checkCompileErrors(unsigned int object, const std::string& type);

    static unsigned int ID;

    const char* m_vertexSource;
    const char* m_fragmentSource;
};

#endif //ZOMBIEGAME_SHADER_H
