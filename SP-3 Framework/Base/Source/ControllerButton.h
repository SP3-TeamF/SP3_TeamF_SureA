#ifndef CONTROLLER_BUTTON_H_
#define CONTROLLER_BUTTON_H_

#include "Button.h"

class ControllerButton : public Button
{
public:
    ControllerButton();
    virtual ~ControllerButton();

    void StatusUpdate(bool status);
    virtual void Update();
private:
    bool status;
};

#endif CONTROLLER_BUTTON_H_