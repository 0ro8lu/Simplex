#include "Window.h"
#include "Model/IApplication.h"

Window::Window(int width, int height, const char *title)
        : m_Width(width), m_Height(height), m_Title(title)
{

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!\n";
        exit(2);
    }

    glfwSetErrorCallback([](int error, const char *description)
                         {
                             std::cout << "Error: " << description << "\n";
                         });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, false);

    m_pWindow = glfwCreateWindow(m_Width, m_Height, "ZombieGame", nullptr, nullptr);

    if (!m_pWindow)
    {
        std::cout << "Failed to create GLFWwindow\n";
        glfwTerminate();
        exit(2);
    }

    glfwMakeContextCurrent(m_pWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        exit(2);
    }

    glViewport(0, 0, m_Width, m_Height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ------------------------------ GLFW Callbacks ------------------------------------

    glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow *window)
    {
        std::unique_ptr<AppCloseEvent> pAppCloseEvent = std::make_unique<AppCloseEvent>();
        EventManager::Get()->triggerEvent((EventPointer const &) pAppCloseEvent);
    });

    glfwSetKeyCallback(m_pWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        AppMsg msg;

        msg.key = key;
        msg.scancode = scancode;
        msg.mods = mods;

        switch (action)
        {
            case GLFW_REPEAT:
                msg.setType(KEYREPEAT);
                break;
            case GLFW_PRESS:
                msg.setType(KEYDOWN);
                break;
            case GLFW_RELEASE:
                msg.setType(KEYUP);
            default:
                break;
        }

        IApplication::messageProcess(msg);
    });

    glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow *window, int button, int action, int mods)
    {
        AppMsg msg;

        msg.button = button;
        msg.mods = mods;

        switch (action)
        {
            case GLFW_PRESS:
                msg.setType(MOUSEDOWN);
                break;
            case GLFW_RELEASE:
                msg.setType(MOUSEUP);
                break;
            default:
                break;
        }

        IApplication::messageProcess(msg);
    });

    glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow *window, double xPos, double yPos)
    {
        AppMsg msg;

        msg.xPos = xPos;
        msg.yPos = yPos;
        msg.setType(MOUSEMOVE);

        IApplication::messageProcess(msg);
    });

    ///TODO: Add MouseScerollCallback.
}

Window::~Window()
{
    glfwDestroyWindow(m_pWindow);
    m_pWindow = nullptr;
    glfwTerminate();
}

void Window::processInput()
{
    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}
