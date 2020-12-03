#ifndef ZOMBIEGAME_PRINTUTILS_H
#define ZOMBIEGAME_PRINTUTILS_H

#include "glm.hpp"
#include <iostream>

class PrintUtils
{
public:

    static void printVec2(const glm::vec2 vec)
    {
        std::cout << "X: " << vec.x << " Y: " << vec.y << "\n\n";
    }

    static void printVec3(const glm::vec3 vec)
    {
        std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << "\n\n";
    }

    static void printMat(const glm::mat4& mat)
    {
        for(int i = 0; i <= 3; i++)
        {
            std::cout << "X: " << mat[i][0] << " Y: " << mat[i][1] << " Z: " << mat[i][2] << "\n";
        }

        std::cout << "\n\n";
    }
};



#endif //ZOMBIEGAME_PRINTUTILS_H
