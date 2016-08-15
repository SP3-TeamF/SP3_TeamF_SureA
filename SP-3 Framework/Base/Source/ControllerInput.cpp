#include "ControllerInput.h"
#include <GLFW/glfw3.h>
#include <iostream>
using std::cout;
using std::endl;

ControllerInput::ControllerInput()
{
}

ControllerInput::~ControllerInput()
{
}

void ControllerInput::ControllerInput_Init(CONTROLLER_ID controllerID)
{
    for (int i = 0; i < NUM_CONTROLLER_INPUT; ++i)
    {
        GetInputs[i] = 0;
    }

    this->controllerID = controllerID;
}

bool ControllerInput::GetIsKeyPressed(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
	int controllerInput;
	const unsigned char * arrayButtonStatus = glfwGetJoystickButtons(0, &controllerInput);

	return (arrayButtonStatus[CONTROLLER_BUTTON] == GLFW_PRESS);
}

bool ControllerInput::GetIsKeyHeld(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
	int controllerInput;
	const unsigned char * arrayButtonStatus = glfwGetJoystickButtons(0, &controllerInput);

	return (arrayButtonStatus[CONTROLLER_BUTTON] == GLFW_REPEAT);
}

bool ControllerInput::GetIsKeyReleased(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
	int controllerInput;
	const unsigned char * arrayButtonStatus = glfwGetJoystickButtons(0, &controllerInput);

	return (arrayButtonStatus[CONTROLLER_BUTTON] == GLFW_RELEASE);
}

bool ControllerInput::GetIsTriggerPressed(CONTROLLER_TRIGGER TRIGGER_TYPE)
{
	int JoystickData;
	const float* storedTrigger = glfwGetJoystickAxes(controllerID, &JoystickData);

	switch (TRIGGER_TYPE)
	{
		case L_TRIGGER :
		{
			if (storedTrigger[2] > 0.5)
			{
				return true;
			}
			break;
		}
		case R_TRIGGER:
		{
			if (storedTrigger[2] < -0.5)
			{
				return true;
			}
			break; 
		}	
		default:
			break;
	}
	return false;
}

Vector3 ControllerInput::GetDirection(CONTROLLER_JOYSTICK JOYSTICK_TYPE)
{
    int JoystickData;
	const float* storedAxes = glfwGetJoystickAxes(controllerID, &JoystickData);

    switch (JOYSTICK_TYPE)
        {
        case L_JOYSTICK:
        {
			return Vector3(storedAxes[0], storedAxes[1]);
            break;
        }
        case R_JOYSTICK:
        {
			return Vector3(storedAxes[3], storedAxes[4]);
            break;
        }
        default:
        {
            break;
        }
    }
}
