#include "SceneManager.h"
#include "Controls.h"

SceneManager::SceneManager()
{
    this->currentScene = nullptr;
    this->scenePathTest = new ScenePathTest();
    this->tutorialScene = new TutorialScene();
    this->collisionTest = new Collisiontest();
    this->sceneMapEditor = new SceneMapEditor();
	this->mainMenu = new MainMenu();
	this->mainMenuExit = new MainMenuExit();
	Init();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
    this->scenePathTest->Init();
    this->collisionTest->Init();
    this->sceneMapEditor->Init();
	this->tutorialScene->Init();
	this->mainMenu->Init();
	this->mainMenuExit->Init();

	this->currentScene = mainMenu;
    this->currentScene->Reset();
}

void SceneManager::Render()
{
    currentScene->Render();
}

void SceneManager::Update(double dt)
{
    if (controls.isKeyboardButtonPressed(KEYBOARD_1))
    {
        currentScene = sceneMapEditor;
        currentScene->Reset();
    }
    else if (controls.isKeyboardButtonPressed(KEYBOARD_2))
    {
        currentScene = tutorialScene;
        currentScene->Reset();
    }
    else if (controls.isKeyboardButtonPressed(KEYBOARD_3))
    {
        currentScene = collisionTest;
        currentScene->Reset();
    }
    else if (controls.isKeyboardButtonPressed(KEYBOARD_4))
    {
        currentScene = scenePathTest;
        currentScene->Reset();
    }
	else if (controls.isKeyboardButtonPressed(KEYBOARD_5))
	{
		currentScene = mainMenu;
		mainMenu->Reset();
	}

    currentScene->Update(dt);
}

void SceneManager::Exit()
{
   this->tutorialScene->Exit();
   this->collisionTest->Exit();
   this->sceneMapEditor->Exit();

   delete this->scenePathTest;
   delete this->tutorialScene;
   delete this->collisionTest;
   delete this->sceneMapEditor;
   delete this->mainMenu;
   delete this->mainMenuExit;
}