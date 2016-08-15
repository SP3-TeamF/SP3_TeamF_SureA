#include "Button.h"

Button::Button()
{
	isButtonState = false;
	currentButtonState = IDLE;
}

Button::~Button()
{
}

BUTTON_STATE Button::GetButtonState()
{
	return currentButtonState;
}