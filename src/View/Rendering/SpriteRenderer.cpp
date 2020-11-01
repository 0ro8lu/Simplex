#include "SpriteRenderer.h"

#include "Utilities/PrintMatrix.h"

SpriteRenderer::SpriteRenderer()
{
    m_VAO = 0;

    m_pShader = new Shader;
    m_pShader->Compile();

    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    delete m_pShader;
    m_pShader = nullptr;
}

void SpriteRenderer::initRenderData()
{
    unsigned int VBO;

    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    /*float vertices[] = {
            // pos      // tex
            0.0f, 0.5f, 0.0f, 1.0f,
            0.5f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.0f, 1.0f, 0.0f
    };*/

    glGenVertexArrays(1, &this->m_VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->m_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::SetProjectionMatrix(const glm::mat4& projectionMatrix)
{
    m_pShader->Use();
    m_pShader->SetMatrix4("projection", projectionMatrix);
}

void SpriteRenderer::SetViewMatrix(glm::mat4& viewMatrix)
{
    ///TODO: Do it the correct way: don't use a secondary m_View matrix, just pass it to the shaders.
    m_View = viewMatrix;
    //m_pShader->Use();
    //m_pShader->SetMatrix4("view ", viewMatrix, true);
}

/*
void SpriteRenderer::DrawSprite(const Texture2D &texture, const glm::vec2 &position, const glm::vec2 &size, float rotate)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    //model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_pShader->SetMatrix4("model", model);

    glm::mat4 view = glm::mat4(1);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    m_pShader->SetMatrix4("view", view);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    printMat(model);

    m_pShader->Use();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
*/

void SpriteRenderer::DrawSprite(const Texture2D& texture, const glm::mat4& model)
{
    m_pShader->SetMatrix4("model", model);

    m_pShader->SetMatrix4("view", m_View);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    m_pShader->Use();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawBackGround()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
