#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "test.h"
#include "Scene.h"
#include "TutorialScene.h"
#include "Collisiontest.h"
#include "SceneMapEditor.h"

enum SCENE_STATES
{
    SCENE_TUTORIAL,
    SCENE_MAPEDITOR,
    SCENE_COLLISIONTEST,
};

class SceneManager
{
public:
    SceneManager();
    virtual ~SceneManager();

    virtual void Init();
    virtual void Exit();
    virtual void Render();
    virtual void Update(double dt);

private:
    Scene* currentScene;
    TutorialScene* tutorialScene;
    Collisiontest* collisionTest;
    SceneMapEditor* sceneMapEditor;

};

#endif SCENEMANAGER_H_