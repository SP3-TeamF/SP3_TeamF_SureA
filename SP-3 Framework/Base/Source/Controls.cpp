#include "Controls.h"
#include "Win32Input.h"
#include <GLFW/glfw3.h>

Controls::Controls()
{
    Controls_Init();
}

Controls::~Controls()
{
}

void Controls::Update()
{
    for (int i = 0; i < NUM_BUTTON_ID; ++i)
	{
		keyboardArray[i].Update();
	}

    for (int i = 0; i < MAX_NUM_CONTROLLERS; ++i)
    {
        controllerArray[i].ControllerInput_Update();
    }
}

bool Controls::isKeyboardButtonHeld(BUTTON_ID Action)
{
	if (keyboardArray[Action].GetButtonState() == HELD)
	{
		return true;
	}
	return false;
}

bool Controls::isKeyboardButtonPressed(BUTTON_ID Action)
{
	if (keyboardArray[Action].GetButtonState() == PRESSED)
	{
		return true;
	}
	return false;
}

bool Controls::isKeyboardButtonReleased(BUTTON_ID Action)
{
	if (keyboardArray[Action].GetButtonState() == RELEASED)
	{
		return true;
	}
    return false;
}

bool Controls::isControllerButtonHeld(CONTROLLER_TYPE controllerType, CONTROLLER_INPUT_BUTTONS Action)
{
    return controllerArray[controllerType].GetIsKeyHeld(Action);
}
             
bool Controls::isControllerButtonPressed(CONTROLLER_TYPE controllerType, CONTROLLER_INPUT_BUTTONS Action)
{
    return controllerArray[controllerType].GetIsKeyPressed(Action);
}

bool Controls::isControllerButtonReleased(CONTROLLER_TYPE controllerType, CONTROLLER_INPUT_BUTTONS Action)
{
    return controllerArray[controllerType].GetIsKeyReleased(Action);
}

Vector3 Controls::GetControllerDirection(CONTROLLER_TYPE controllerType, CONTROLLER_JOYSTICK joystickType)
{
	return controllerArray[controllerType].GetDirection(joystickType);
}

void Controls::Controls_Init()
{
    //Letters 
    keyboardArray[KEYBOARD_A].AssignKey('A');
    keyboardArray[KEYBOARD_B].AssignKey('B');
    keyboardArray[KEYBOARD_C].AssignKey('C');
    keyboardArray[KEYBOARD_D].AssignKey('D');
    keyboardArray[KEYBOARD_E].AssignKey('E');
    keyboardArray[KEYBOARD_F].AssignKey('F');
    keyboardArray[KEYBOARD_G].AssignKey('G');
    keyboardArray[KEYBOARD_H].AssignKey('H');
    keyboardArray[KEYBOARD_I].AssignKey('I');
    keyboardArray[KEYBOARD_J].AssignKey('J');
    keyboardArray[KEYBOARD_K].AssignKey('K');
    keyboardArray[KEYBOARD_L].AssignKey('L');
    keyboardArray[KEYBOARD_M].AssignKey('M');
    keyboardArray[KEYBOARD_N].AssignKey('N');
    keyboardArray[KEYBOARD_O].AssignKey('O');
    keyboardArray[KEYBOARD_P].AssignKey('P');
    keyboardArray[KEYBOARD_Q].AssignKey('Q');
    keyboardArray[KEYBOARD_R].AssignKey('R');
    keyboardArray[KEYBOARD_S].AssignKey('S');
    keyboardArray[KEYBOARD_T].AssignKey('T');
    keyboardArray[KEYBOARD_U].AssignKey('U');
    keyboardArray[KEYBOARD_V].AssignKey('V');
    keyboardArray[KEYBOARD_W].AssignKey('W');
    keyboardArray[KEYBOARD_X].AssignKey('X');
    keyboardArray[KEYBOARD_Y].AssignKey('Y');
    keyboardArray[KEYBOARD_Z].AssignKey('Z');
    
    //Numbers
    keyboardArray[KEYBOARD_0].AssignKey('0');
    keyboardArray[KEYBOARD_1].AssignKey('1');
    keyboardArray[KEYBOARD_2].AssignKey('2');
    keyboardArray[KEYBOARD_3].AssignKey('3');
    keyboardArray[KEYBOARD_4].AssignKey('4');
    keyboardArray[KEYBOARD_5].AssignKey('5');
    keyboardArray[KEYBOARD_6].AssignKey('6');
    keyboardArray[KEYBOARD_7].AssignKey('7');
    keyboardArray[KEYBOARD_8].AssignKey('8');
    keyboardArray[KEYBOARD_9].AssignKey('9');

    //Numpad
    keyboardArray[NUMPAD_0].AssignKey(VK_NUMPAD0);
    keyboardArray[NUMPAD_1].AssignKey(VK_NUMPAD1);
    keyboardArray[NUMPAD_2].AssignKey(VK_NUMPAD2);
    keyboardArray[NUMPAD_3].AssignKey(VK_NUMPAD3);
    keyboardArray[NUMPAD_4].AssignKey(VK_NUMPAD4);
    keyboardArray[NUMPAD_5].AssignKey(VK_NUMPAD5);
    keyboardArray[NUMPAD_6].AssignKey(VK_NUMPAD6);
    keyboardArray[NUMPAD_7].AssignKey(VK_NUMPAD7);
    keyboardArray[NUMPAD_8].AssignKey(VK_NUMPAD8);
    keyboardArray[NUMPAD_9].AssignKey(VK_NUMPAD9);

    //Function Keys
    keyboardArray[KEYBOARD_F1].AssignKey(VK_F1);
    keyboardArray[KEYBOARD_F2].AssignKey(VK_F2);
    keyboardArray[KEYBOARD_F3].AssignKey(VK_F3);
    keyboardArray[KEYBOARD_F4].AssignKey(VK_F4);
    keyboardArray[KEYBOARD_F5].AssignKey(VK_F5);
    keyboardArray[KEYBOARD_F6].AssignKey(VK_F6);
    keyboardArray[KEYBOARD_F7].AssignKey(VK_F7);
    keyboardArray[KEYBOARD_F8].AssignKey(VK_F8);
    keyboardArray[KEYBOARD_F9].AssignKey(VK_F9);
    keyboardArray[KEYBOARD_F10].AssignKey(VK_F10);
    keyboardArray[KEYBOARD_F11].AssignKey(VK_F11);
    keyboardArray[KEYBOARD_F12].AssignKey(VK_F12);

    //Mouse
    keyboardArray[MOUSE_L_CLICK].AssignKey(VK_LBUTTON);
    keyboardArray[MOUSE_R_CLICK].AssignKey(VK_RBUTTON);

    //Direction Pad
    keyboardArray[KEYBOARD_UP].AssignKey(VK_UP);
    keyboardArray[KEYBOARD_DOWN].AssignKey(VK_DOWN);
    keyboardArray[KEYBOARD_LEFT].AssignKey(VK_LEFT);
    keyboardArray[KEYBOARD_RIGHT].AssignKey(VK_RIGHT);

    //Others
    keyboardArray[KEYBOARD_TAB].AssignKey(VK_TAB);
    keyboardArray[KEYBOARD_ADD].AssignKey(VK_ADD);
    keyboardArray[KEYBOARD_BACK].AssignKey(VK_BACK);
    keyboardArray[KEYBOARD_SPACE].AssignKey(VK_SPACE);
    keyboardArray[KEYBOARD_ENTER].AssignKey(VK_RETURN);
    keyboardArray[KEYBOARD_ESCAPE].AssignKey(VK_ESCAPE);
    keyboardArray[KEYBOARD_L_SHIFT].AssignKey(VK_LSHIFT);
    keyboardArray[KEYBOARD_R_SHIFT].AssignKey(VK_RSHIFT);
    keyboardArray[KEYBOARD_L_ALTERNATE].AssignKey(VK_LMENU);
    keyboardArray[KEYBOARD_R_ALTERNATE].AssignKey(VK_RMENU);
    keyboardArray[KEYBOARD_SUBTRACT].AssignKey(VK_SUBTRACT);
    keyboardArray[KEYBOARD_L_CONTROL].AssignKey(VK_LCONTROL);
    keyboardArray[KEYBOARD_R_CONTROL].AssignKey(VK_RCONTROL);

    controllerArray[CONTROLLER_1].ControllerInput_Init(CONTROLLER_ID_1);
    controllerArray[CONTROLLER_2].ControllerInput_Init(CONTROLLER_ID_2);
}