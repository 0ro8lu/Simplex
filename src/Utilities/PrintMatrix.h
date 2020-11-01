#ifndef ZOMBIEGAME_PRINTMATRIX_H
#define ZOMBIEGAME_PRINTMATRIX_H

#include "glm.hpp"
#include <iostream>

void printMat(glm::mat4& model)
{
    for(int i = 0; i <= 3; i++)
    {
        std::cout << "X: " << model[i][0] << " Y: " << model[i][1] << " Z: " << model[i][2] << "\n";
    }

    std::cout << "\n\n\n\n\n\n";
}

#endif //ZOMBIEGAME_PRINTMATRIX_H
