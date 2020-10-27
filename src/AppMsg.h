#ifndef ZOMBIEGAME_APPMSG_H
#define ZOMBIEGAME_APPMSG_H

enum Type
{
    KEYUP, KEYDOWN, KEYREPEAT,
    MOUSEUP, MOUSEDOWN, MOUSESCROLL, MOUSEMOVE
};

struct AppMsg
{
    AppMsg()  = default;
    ~AppMsg() = default;

    // Keyboard
    int key{};
    int scancode{};
    int mods{};

    //Mouse
    double xPos{}, yPos{};
    int button{};

    Type getType() const { return m_Type; }
    void setType(Type type) { m_Type = type; }

private:
    Type m_Type;
};

#endif //ZOMBIEGAME_APPMSG_H
