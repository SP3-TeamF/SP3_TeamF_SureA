#include "ControllerButton.h"

ControllerButton::ControllerButton()
{
    bool status = false;
}

ControllerButton::~ControllerButton()
{
}

void ControllerButton::Update()
{
    if (!isButtonState && status)
    {
        isButtonState = true;
        currentButtonState = PRESSED;
    }
    else if (isButtonState && status)
    {
        currentButtonState = HELD;
    }
    else if (isButtonState && !status)
    {
        isButtonState = false;
        currentButtonState = RELEASED;
    }
    else
    {
        currentButtonState = IDLE;
    }
}

void ControllerButton::StatusUpdate(bool status)
{
    this->status = status;
}
