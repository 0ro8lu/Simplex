#include "Shader.h"

unsigned int Shader::ID = 0;

Shader::Shader()
{
    m_vertexSource = "#version 330 core\n"
                     "layout (location = 0) in vec2 aPos;\n"
                     "layout (location = 1) in vec2 aTexCoord;\n"
                     "out vec2 TexCoords;\n"
                     "uniform mat4 projection;\n"
                     "uniform mat4 view;\n"
                     "uniform mat4 model;\n"
                     "void main()\n"
                     "{\n"
                     "   TexCoords = vec2(aTexCoord.x, aTexCoord.y);\n"
                     "   gl_Position = projection * view * model * vec4(aPos, 1.0, 1.0);\n"
                     "}\0";

    /*m_vertexSource = "#version 330 core\n"
                     "layout (location = 0) in vec4 vertex;\n"
                     "out vec2 TexCoords;\n"
                     "uniform mat4 projection;\n"
                     "uniform mat4 view;\n"
                     "uniform mat4 model;\n"
                     "void main()\n"
                     "{\n"
                     "   TexCoords = vertex.zw;\n"
                     "   gl_Position = projection * view * model * vec4(vertex.xyz, 1.0);\n"
                     "}\0";*/

    m_fragmentSource = "#version 330 core\n"
                       "out vec4 FragColor;\n"
                       "in vec2 TexCoords;\n"
                       "uniform sampler2D ourTexture;\n"
                       "void main()\n"
                       "{\n"
                       "//FragColor = vec4(0, 0, 0, 255);\n"
                       "FragColor = texture(ourTexture, TexCoords);\n"
                       "}\0";
}

Shader::~Shader() = default;

Shader &Shader::Use()
{
    glUseProgram(Shader::ID);
    return *this;
}

void Shader::Compile()
{
    unsigned int sVertex, sFragment;

    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &m_vertexSource, nullptr);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &m_fragmentSource, nullptr);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    Shader::ID = glCreateProgram();
    glAttachShader(Shader::ID, sVertex);
    glAttachShader(Shader::ID, sFragment);

    glLinkProgram(Shader::ID);
    checkCompileErrors(Shader::ID, "PROGRAM");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

void Shader::checkCompileErrors(unsigned int object, const std::string& type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}

void Shader::SetVector3f(const std::string &name, float x, float y, float z, bool useShader)
{
    if(useShader)
        glUseProgram(Shader::ID);
    glUniform3f(glad_glGetUniformLocation(Shader::ID, name.c_str()), x, y, z);
}

void Shader::SetVector3f(const std::string &name, const glm::vec3 &value, bool useShader)
{
    if(useShader)
        glUseProgram(Shader::ID);
    glUniform3f(glad_glGetUniformLocation(Shader::ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetMatrix4(const std::string &name, const glm::mat4 &matrix, bool useShader)
{
    if(useShader)
        glUseProgram(Shader::ID);
    glUniformMatrix4fv(glad_glGetUniformLocation(Shader::ID, name.c_str()), 1, false, glm::value_ptr(matrix));
}

void Shader::SetInt(const std::string &name, int value, bool useShader)
{
    if(useShader)
        glUseProgram(Shader::ID);
    glUniform1i(glGetUniformLocation(Shader::ID, name.c_str()), value);
}
