#ifndef KEYBOARD_BUTTON_H_
#define KEYBOARD_BUTTON_H_

#include "Button.h"

class KeyboardButton : public Button
{
public:
    KeyboardButton();
    virtual ~KeyboardButton();

    virtual void Update();
    void AssignKey(unsigned char Key);

private:
    short keyAssigned;
};

#endif KEYBOARD_BUTTON_H_