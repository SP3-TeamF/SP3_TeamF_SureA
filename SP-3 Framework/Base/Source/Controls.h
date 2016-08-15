#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "KeyboardButton.h"
#include "ControllerInput.h"
#define controls Controls::GetInstance()

enum BUTTON_ID
{
    //Letters
    KEYBOARD_A,
    KEYBOARD_B,
    KEYBOARD_C,
    KEYBOARD_D,
    KEYBOARD_E,
    KEYBOARD_F,
    KEYBOARD_G,
    KEYBOARD_H,
    KEYBOARD_I,
    KEYBOARD_J,
    KEYBOARD_K,
    KEYBOARD_L,
    KEYBOARD_M,
    KEYBOARD_N,
    KEYBOARD_O,
    KEYBOARD_P,
    KEYBOARD_Q,
    KEYBOARD_R,
    KEYBOARD_S,
    KEYBOARD_T,
    KEYBOARD_U,
    KEYBOARD_V,
    KEYBOARD_W,
    KEYBOARD_X,
    KEYBOARD_Y,
    KEYBOARD_Z,

    //Numbers
    KEYBOARD_0,
    KEYBOARD_1,
    KEYBOARD_2,
    KEYBOARD_3,
    KEYBOARD_4,
    KEYBOARD_5,
    KEYBOARD_6,
    KEYBOARD_7,
    KEYBOARD_8,
    KEYBOARD_9,

    //Numpad
    NUMPAD_0,
    NUMPAD_1,
    NUMPAD_2,
    NUMPAD_3,
    NUMPAD_4,
    NUMPAD_5,
    NUMPAD_6,
    NUMPAD_7,
    NUMPAD_8,
    NUMPAD_9,

    //Function Keys
    KEYBOARD_F1,
    KEYBOARD_F2,
    KEYBOARD_F3,
    KEYBOARD_F4,
    KEYBOARD_F5,
    KEYBOARD_F6,
    KEYBOARD_F7,
    KEYBOARD_F8,
    KEYBOARD_F9,
    KEYBOARD_F10,
    KEYBOARD_F11,
    KEYBOARD_F12,

    //Mouse
    MOUSE_L_CLICK,
    MOUSE_R_CLICK,

    //Direction Pad
    KEYBOARD_UP,
    KEYBOARD_DOWN,
    KEYBOARD_LEFT,
    KEYBOARD_RIGHT,

    //Others
    KEYBOARD_TAB,
    KEYBOARD_ADD,
    KEYBOARD_BACK,
    KEYBOARD_ENTER,
    KEYBOARD_SPACE,
    KEYBOARD_ESCAPE,
    KEYBOARD_L_SHIFT,
    KEYBOARD_R_SHIFT,
    KEYBOARD_SUBTRACT,
    KEYBOARD_L_CONTROL,
    KEYBOARD_R_CONTROL,
    KEYBOARD_L_ALTERNATE,
    KEYBOARD_R_ALTERNATE,

    NUM_BUTTON_ID,
};

enum CONTROLLER_TYPE
{
    CONTROLLER_1,
    CONTROLLER_2,

    MAX_NUM_CONTROLLERS,
};

class Controls
{
public:
	static Controls& GetInstance()
	{
		static Controls globalV;
		return globalV;
	}

    Controls();
    virtual ~Controls();
	void Update();

    bool isKeyboardButtonHeld(BUTTON_ID Action);
    bool isKeyboardButtonPressed(BUTTON_ID Action);
    bool isKeyboardButtonReleased(BUTTON_ID Action);

    bool isControllerButtonHeld(CONTROLLER_TYPE controllerType, CONTROLLER_INPUT_BUTTONS Action);
    bool isControllerButtonPressed(CONTROLLER_TYPE controllerType, CONTROLLER_INPUT_BUTTONS Action);
    bool isControllerButtonReleased(CONTROLLER_TYPE controllerType, CONTROLLER_INPUT_BUTTONS Action);

	Vector3 GetControllerDirection(CONTROLLER_TYPE controllerType, CONTROLLER_JOYSTICK joystickType);

    void Controls_Init();
private:
    KeyboardButton keyboardArray[NUM_BUTTON_ID];
    ControllerInput controllerArray[MAX_NUM_CONTROLLERS];
};

#endif // !CONTROLS_H_
