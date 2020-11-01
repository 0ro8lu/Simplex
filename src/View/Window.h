#ifndef ZOMBIEGAME_WINDOW_H
#define ZOMBIEGAME_WINDOW_H

#include <iostream>

#include "glad.h"
#include "glfw3.h"

#include "AppCloseEvent.h"
#include "EventManager.h"
#include "AppMsg.h"
#include "SceneNodes/SpriteNode.h"

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void processInput();

    static int getWidth()  { return m_Width; }
    static int getHeight() { return m_Height; }

private:

    static int m_Width, m_Height;
    const char* m_Title;

    GLFWwindow* m_pWindow;
};

#endif //ZOMBIEGAME_WINDOW_H
