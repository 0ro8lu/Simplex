#ifndef ZOMBIEGAME_ISCREENELEMENT_H
#define ZOMBIEGAME_ISCREENELEMENT_H

#include "AppMsg.h"

class IScreenElement
{
public:

    virtual ~IScreenElement() = default;
    virtual void VOnUpdate() = 0;
    virtual bool VIsVisible() const = 0;
    virtual void VOnRender() = 0;
    virtual bool VOnMsgProc(const AppMsg& msg) = 0;

    /*
     * virtual HRESULT(?) VOnRestore() = 0;
     * virtual HRESULT(?) VOnLostDevice = 0;
     * virtual int VGetZOrder() const = 0;
     * virtual void VSetZOrdr(int const zOrder) = 0;
     * virtual void VSetVisible(bool visible) = 0;
     * virtual bool const operator < ();
     */
};

#endif //ZOMBIEGAME_ISCREENELEMENT_H
