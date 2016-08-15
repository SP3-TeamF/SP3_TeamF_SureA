#include "KeyboardButton.h"
#include "Win32Input.h"

bool IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

KeyboardButton::KeyboardButton()
{
    isButtonState = false;
    currentButtonState = IDLE;
    keyAssigned = 'A';
}

KeyboardButton::~KeyboardButton()
{
}

void KeyboardButton::AssignKey(unsigned char key)
{
    isButtonState = false;
    currentButtonState = IDLE;
    keyAssigned = key;
}

void KeyboardButton::Update()
{
    if (!isButtonState && IsKeyPressed(keyAssigned))
    {
        isButtonState = true;
        currentButtonState = PRESSED;
    }
    else if (isButtonState && IsKeyPressed(keyAssigned))
    {
        currentButtonState = HELD;
    }
    else if (isButtonState && !IsKeyPressed(keyAssigned))
    {
        isButtonState = false;
        currentButtonState = RELEASED;
    }
    else
    {
        currentButtonState = IDLE;
    }
}