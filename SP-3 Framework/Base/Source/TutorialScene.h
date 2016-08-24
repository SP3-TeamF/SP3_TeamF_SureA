#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "SceneMapEditor.h"
#include "Pathfinding.h"

class TutorialScene : public Scenebase
{


public:
	TutorialScene();
	~TutorialScene();
	virtual void Init();
	virtual void Update(double dt);
    virtual void Reset();
	virtual void Render();
	virtual void Exit();

    //Update function
    void UpdatePlayerInputUpdates(double dt);

    //Render
    void RenderMainCharacter();
	Scenebase *renderthesprite;

private:
	float Test_X_OFFSET;
	float Test_Y_OFFSET;
	float netScale;
	bool netHit;
	bool stop;
	Vector3 controllermovement;

    TileMap tutorialMap;
};

#endif