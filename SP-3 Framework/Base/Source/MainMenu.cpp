#include "MainMenu.h"
#include "SceneManager.h"
#include "GL\glew.h"

MainMenu::MainMenu()
{
	arrow_posx = 0.07;
	timeDelay = 0;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	Scenebase::Init();
	currently_selected = Play;
}

void MainMenu::Render()
{
	//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	Scenebase::Render();
	Scenebase::RenderMainMenu();

	Render2DMesh(meshList[GEO_ARROW], false, 1.0f, m_TileMap->GetScreenWidth() * arrow_posx, m_TileMap->GetScreenHeight() * 0.55625);
}

void MainMenu::Update(double dt)
{
	timeDelay -= dt;

	if (controls.isKeyboardButtonPressed(KEYBOARD_D) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_RIGHT))
	{
		if (timeDelay < 0)
		{
			if (currently_selected < 5)
			{
				currently_selected = static_cast<CURRENTLY_SELECTED>(((int)currently_selected) + 1);
			}
			if (currently_selected >= 5)
			{
				currently_selected = static_cast<CURRENTLY_SELECTED>(1);
			}
			timeDelay = 0.3;
		}
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_A) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_LEFT))
	{
		if (timeDelay < 0)
		{
			if (currently_selected < 5)
			{
				currently_selected = static_cast<CURRENTLY_SELECTED>(((int)currently_selected) - 1);
			}
			if (currently_selected <= 0)
			{
				currently_selected = static_cast<CURRENTLY_SELECTED>(4);
			}
			timeDelay = 0.3;
		}
	}

	if (currently_selected == Play && (controls.isKeyboardButtonPressed(KEYBOARD_ENTER) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_A)))
	{
		sceneManager.currentScene = sceneManager.tutorialScene;
		//sceneManager.currentScene->Reset();
	}
	if (currently_selected == Load && (controls.isKeyboardButtonPressed(KEYBOARD_ENTER) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_A)))
	{

	}
	if (currently_selected == Exit_game && (controls.isKeyboardButtonPressed(KEYBOARD_ENTER) || controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_A)))
	{
		sceneManager.currentScene = sceneManager.mainMenuExit;
	}

	switch (currently_selected)
	{
	case Play:
		arrow_posx = 0.07f;
		break;

	case Load:
		arrow_posx = 0.26f;
		break;

	case Credit:
		arrow_posx = 0.455f;
		break;

	case Exit_game:
		arrow_posx = 0.71f;
		break;

	default:
		break;
	}
}

void MainMenu::Exit()
{

}