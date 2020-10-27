#ifndef ZOMBIEGAME_SPRITERENDERER_H
#define ZOMBIEGAME_SPRITERENDERER_H

#include <gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"

class SpriteRenderer
{
public:
    SpriteRenderer();
    ~SpriteRenderer();

    //void DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size, float rotate = 0.0f);
    void DrawSprite(const Texture2D& texture, const glm::mat4 &model);
    void DrawBackGround();

private:

    void initRenderData();

    unsigned int m_VAO;

    Shader* m_pShader;
};

#endif //ZOMBIEGAME_SPRITERENDERER_H
