#ifndef ZOMBIEGAME_TEXTURE2D_H
#define ZOMBIEGAME_TEXTURE2D_H

#include <glad.h>

#include <iostream>

#include "stb_image.h"

class Texture2D
{
public:

    Texture2D();
    ~Texture2D();

    void LoadFromFile(const char* file, bool alpha);
    void Bind() const;

    unsigned int ID;

    int Width, Height;
    int nrChannels;

    unsigned int Internal_Format;
    unsigned int Image_Format;

    unsigned int Wrap_S;
    unsigned int Wrap_T;
    unsigned int Filter_Min;
    unsigned int Filter_Max;

private:
    void Generate(int width, int height, unsigned char* data);
};

#endif //ZOMBIEGAME_TEXTURE2D_H
