#ifndef ZOMBIEGAME_IKEYBOARDHANDLER_H
#define ZOMBIEGAME_IKEYBOARDHANDLER_H

class IKeyboardHandler
{
public:
    virtual bool VOnKeyDown(short key) = 0;
    virtual bool VOnKeyUp(short key) = 0;
};

#endif //ZOMBIEGAME_IKEYBOARDHANDLER_H
