#include "MainMenuExit.h"
#include "SceneManager.h"
#include "GL\glew.h"

MainMenuExit::MainMenuExit()
{
	arrow_posx = 0.2;
	timeDelay = 0;
}

MainMenuExit::~MainMenuExit()
{
}

void MainMenuExit::Init()
{
	Scenebase::Init();
	yesorno = YES;
}

void MainMenuExit::Render()
{
	Scenebase::Render();
	//Scenebase::RenderMainMenuExit();

	Render2DMesh(meshList[GEO_ARROW], false, 1.0f, m_TileMap->GetScreenWidth() * arrow_posx, m_TileMap->GetScreenHeight() * 0.55625);
}

void MainMenuExit::Update(double dt)
{
	timeDelay -= dt;
	if (controls.isKeyboardButtonPressed(KEYBOARD_D) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_RIGHT))
	{
		if (timeDelay < 0)
		{
			if (yesorno <= 2)
			{
				yesorno = static_cast<YON>(((int)yesorno) + 1);
			}
			if (yesorno >= 3)
			{
				yesorno = static_cast<YON>(1);
			}
			timeDelay = 0.3;
		}
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_A) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_LEFT))
	{
		if (timeDelay < 0)
		{
			if (yesorno < 3)
			{
				yesorno = static_cast<YON>(((int)yesorno) - 1);
			}
			if (yesorno <= 0)
			{
				yesorno = static_cast<YON>(2);
			}
			timeDelay = 0.3;
		}
	}

	if (yesorno == YES && (controls.isKeyboardButtonPressed(KEYBOARD_ENTER) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_A)))
	{
		GlobalData.quitGame = true;
	}
	if (yesorno == NO && (controls.isKeyboardButtonPressed(KEYBOARD_ENTER) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_A)))
	{
		sceneManager.currentScene = sceneManager.mainMenu;
	}

	switch (yesorno)
	{
	case YES:
		arrow_posx = 0.2f;
		break;

	case NO:
		arrow_posx = 0.7f;
		break;

	default:
		break;
	}
}

void MainMenuExit::Exit()
{

}