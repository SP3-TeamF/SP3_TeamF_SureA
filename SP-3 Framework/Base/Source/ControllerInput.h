#ifndef CONTROLLER_INPUTS_H_
#define CONTROLLER_INPUTS_H_
#include "Vector3.h"

enum CONTROLLER_INPUT_BUTTONS
{
    CONTROLLER_A = 0,
    CONTROLLER_B,
    CONTROLLER_X,
    CONTROLLER_Y,

    CONTROLLER_LBUMPER,
	CONTROLLER_RBUMPER,

    CONTROLLER_BACK,
    CONTROLLER_START,

    CONTROLLER_LSTICKER,
    CONTROLLER_RSTICKER,

    CONTROLLER_DPAD_UP,
	CONTROLLER_DPAD_RIGHT,
    CONTROLLER_DPAD_DOWN,
    CONTROLLER_DPAD_LEFT,

    NUM_CONTROLLER_INPUT,
};

enum CONTROLLER_JOYSTICK
{
    L_JOYSTICK = 8,
    R_JOYSTICK,
};

enum CONTROLLER_TRIGGER
{
	L_TRIGGER,
	R_TRIGGER,
};

enum CONTROLLER_ID
{
    CONTROLLER_ID_1 = 0,
    CONTROLLER_ID_2,
    CONTROLLER_ID_3,
    CONTROLLER_ID_4,
    CONTROLLER_ID_5,
    CONTROLLER_ID_6,
    CONTROLLER_ID_7,
    CONTROLLER_ID_8,
    CONTROLLER_ID_9,
    CONTROLLER_ID_10,
    CONTROLLER_ID_11,
    CONTROLLER_ID_12,
    CONTROLLER_ID_13,
    CONTROLLER_ID_14,
    CONTROLLER_ID_15,
    CONTROLLER_ID_16,
};

class ControllerInput
{
public:
    ControllerInput();
    virtual ~ControllerInput();

    void ControllerInput_Init(CONTROLLER_ID controllerID);

    //Getters
    bool GetIsKeyPressed(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON);
    bool GetIsKeyHeld(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON);
    bool GetIsKeyReleased(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON);

	bool GetIsTriggerPressed(CONTROLLER_TRIGGER TRIGGER_TYPE);

	Vector3 GetDirection(CONTROLLER_JOYSTICK JOYSTICK_TYPE);

private:
    CONTROLLER_ID controllerID;
    int GetInputs[NUM_CONTROLLER_INPUT];
	
};

#endif CONTROLLER_INPUTS_H_
