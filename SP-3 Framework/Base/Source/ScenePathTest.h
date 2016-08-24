#ifndef SCENE_PATHTEST_H_
#define SCENE_PATHTEST_H_

#include "Scenebase.h"
#include "Pathfinding.h"
#include "BasicEnemy.h"
#include "TutorialScene.h"

class ScenePathTest :public Scenebase
{
public:
    ScenePathTest();
    virtual ~ScenePathTest();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Reset();
    virtual void Render();
    virtual void Exit();
	void UpdateBullets(double dt);
private:
    TileMap pathTestMap;
    Pathfinding pathFinder;

    Vector3 endPosition;
    Vector3 startPosition;
    Vector3 currentPosition;

    BasicEnemy testEnemy;
};

#endif SCENE_PATHTEST_H_