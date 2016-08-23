#include "ControllerInput.h"
#include <GLFW/glfw3.h>
#include <iostream>
using std::cout;
using std::endl;
#include "GlobalDatas.h"

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
	if (GlobalData.isControllerConnected)
	{
		int controllerInput;
		const unsigned char * arrayButtonStatus = glfwGetJoystickButtons(0, &controllerInput);

		return (arrayButtonStatus[CONTROLLER_BUTTON] == GLFW_PRESS);
	}

	return false;
}

bool ControllerInput::GetIsKeyHeld(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
	if (GlobalData.isControllerConnected)
	{
		int controllerInput;
		const unsigned char * arrayButtonStatus = glfwGetJoystickButtons(0, &controllerInput);

		return (arrayButtonStatus[CONTROLLER_BUTTON] == GLFW_REPEAT);
	}

	return false;
}

bool ControllerInput::GetIsKeyReleased(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
	if (GlobalData.isControllerConnected)
	{
		int controllerInput;
		const unsigned char * arrayButtonStatus = glfwGetJoystickButtons(0, &controllerInput);

		return (arrayButtonStatus[CONTROLLER_BUTTON] == GLFW_RELEASE);
	}
	return false;
}

bool ControllerInput::GetIsTriggerPressed(CONTROLLER_TRIGGER TRIGGER_TYPE)
{
	if (GlobalData.isControllerConnected)
	{
		int JoystickData;
		const float* storedTrigger = glfwGetJoystickAxes(controllerID, &JoystickData);

		switch (TRIGGER_TYPE)
		{
			case L_TRIGGER:
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
	}
	return false;
}

Vector3 ControllerInput::GetDirection(CONTROLLER_JOYSTICK JOYSTICK_TYPE)
{
	float dirX = 0;
	float dirY = 0;

	if (GlobalData.isControllerConnected)
	{
		int JoystickData;
		const float* storedAxes = glfwGetJoystickAxes(controllerID, &JoystickData);

		switch (JOYSTICK_TYPE)
		{
			case L_JOYSTICK:
			{
				dirX = storedAxes[0];
				dirY = storedAxes[1];
				if (dirX > -0.2 && dirX < 0.2)
				{
					dirX = 0;
				}
				if (dirY > -0.2 && dirY < 0.2)
				{
					dirY = 0;
				}
				break;
			}
			case R_JOYSTICK:
			{
				dirX = storedAxes[4];
				dirY = -storedAxes[3];
				if (dirX > -0.2 && dirX < 0.2)
				{
					dirX = 0;
				}
				if (dirY > -0.2 && dirY < 0.2)
				{
					dirY = 0;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}

	if (dirX != 0 || dirY != 0)
	{
		return Vector3(dirX, dirY, 0).Normalized();
	}
	return Vector3(dirX, dirY, 0);
}
