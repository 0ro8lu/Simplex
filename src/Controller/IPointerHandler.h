#ifndef ZOMBIEGAME_IPOINTERHANDLER_H
#define ZOMBIEGAME_IPOINTERHANDLER_H

class IPointerHandler
{
public:
    virtual bool VOnPointerMove(int x, int y) = 0;
    virtual bool VOnPointerButtonDown(int x, int y, int key) = 0;
    virtual bool VOnPointerButtonUp(int x, int y, int key) = 0;
};

#endif //ZOMBIEGAME_IPOINTERHANDLER_H
