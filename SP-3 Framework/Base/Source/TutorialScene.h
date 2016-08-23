#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "SceneMapEditor.h"
#include "weapon.h"
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
    void UpdateBullets(double dt);
   
    void UpdatePlayerInputUpdates(double dt);

    //Render
    void RenderBullets();
    void RenderMainCharacter();
	Scenebase *renderthesprite;

private:
	float Test_X_OFFSET;
	float Test_Y_OFFSET;
	float netScale;
	bool netHit;
	bool stop;
	weapon* Weapon;
	Vector3 controllermovement;

    TileMap tutorialMap;
};

#endif