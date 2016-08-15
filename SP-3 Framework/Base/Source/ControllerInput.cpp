#include "ControllerInput.h"
#include <GLFW/glfw3.h>

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

void ControllerInput::ControllerInput_Update()
{
    glfwGetJoystickButtons(controllerID, GetInputs);
    for (int i = 0; i < NUM_CONTROLLER_INPUT; ++i)
    {
        ControllerButtons[i].StatusUpdate(GetInputs[i]);
        ControllerButtons[i].Update();
    }
}

bool ControllerInput::GetIsKeyPressed(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
    return ControllerButtons[CONTROLLER_BUTTON].GetButtonState();
}

bool ControllerInput::GetIsKeyHeld(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
    return ControllerButtons[CONTROLLER_BUTTON].GetButtonState();
}

bool ControllerInput::GetIsKeyReleased(CONTROLLER_INPUT_BUTTONS CONTROLLER_BUTTON)
{
    return ControllerButtons[CONTROLLER_BUTTON].GetButtonState();
}

Vector3 ControllerInput::GetDirection(CONTROLLER_JOYSTICK JOYSTICK_TYPE)
{
    int JoystickData[5];
    glfwGetJoystickAxes(GLFW_JOYSTICK_1, JoystickData);

    switch (JOYSTICK_TYPE)
        {
        case L_JOYSTICK:
        {
            return Vector3(JoystickData[0], JoystickData[1]);
            break;
        }
        case R_JOYSTICK:
        {
            return Vector3(JoystickData[3], JoystickData[4]);
            break;
        }
        default:
        {
            break;
        }
    }
}
