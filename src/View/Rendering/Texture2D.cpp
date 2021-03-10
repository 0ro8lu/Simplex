#include "Texture2D.h"

Texture2D::Texture2D()
        : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
          Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &this->ID);
}

Texture2D::~Texture2D()
{

}

void Texture2D::Generate(int width, int height, unsigned char *data)
{
    this->Width  = width;
    this->Height = height;

    glBindTexture(GL_TEXTURE_2D, this->ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, Width, Height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture2D::LoadFromFile(const char *file, bool alpha)
{
    if(alpha)
    {
        Internal_Format = GL_RGBA;
        Image_Format    = GL_RGBA;
    }

    unsigned char* data = stbi_load(file, &Width, &Height, &nrChannels, 0);

    if(!data)
    {
        std::cout << "Unable to load texture file " << file << "\n";
        return;
    }

    Generate(Width, Height, data);

    stbi_image_free(data);

    //Shader::SetInt("ourTexture", 0, true);

    //glBindTexture(GL_TEXTURE_2D, 0);
}
