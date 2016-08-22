#include "SceneManager.h"
#include "Controls.h"

SceneManager::SceneManager()
{
    this->currentScene = nullptr;
    this->tutorialScene = new TutorialScene();
    this->collisionTest = new Collisiontest();
    this->sceneMapEditor = new SceneMapEditor();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
    this->collisionTest->Init();
    this->sceneMapEditor->Init();
    this->tutorialScene->Init();
    this->currentScene = tutorialScene;
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

    currentScene->Update(dt);
}

void SceneManager::Exit()
{
   this->tutorialScene->Exit();
   this->collisionTest->Exit();
   this->sceneMapEditor->Exit();
}