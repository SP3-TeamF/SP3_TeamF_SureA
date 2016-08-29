#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#define sceneManager SceneManager::GetInstance()

#include "test.h"
#include "Scene.h"
#include "ScenePathTest.h"
#include "TutorialScene.h"
#include "Collisiontest.h"
#include "SceneMapEditor.h"
#include "MainMenu.h"
#include "WaterScene.h"

enum SCENE_STATES
{
    SCENE_TUTORIAL,
    SCENE_MAPEDITOR,
    SCENE_COLLISIONTEST,
};

class SceneManager
{
public:

	static SceneManager& GetInstance()
	{
		static SceneManager scene_Manager;
		return scene_Manager;
	}

    SceneManager();
    virtual ~SceneManager();

    virtual void Init();
    virtual void Exit();
    virtual void Render();
    virtual void Update(double dt);


    Scene* currentScene;
    ScenePathTest* scenePathTest;
    TutorialScene* tutorialScene;
    Collisiontest* collisionTest;
    SceneMapEditor* sceneMapEditor;
	MainMenu* mainMenu;
	WaterScene*waterscene;

};

#endif SCENEMANAGER_H_