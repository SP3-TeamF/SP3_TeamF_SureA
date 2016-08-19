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
	virtual void Render();
	virtual void Exit();

    //Update function
    void UpdateBullets(double dt);
    void UpdateSpriteAnimations(double dt);
    void UpdatePlayerInputUpdates(double dt);

    //Render
    void RenderBullets();
    void RenderMainCharacter();

private:
	float Test_X_OFFSET;
	float Test_Y_OFFSET;
	float netScale;
	bool netHit;
	bool stop;
	weapon* Weapon;
	Vector3 controllermovement;
    Pathfinding pathFinder;

    Vector3 nextPosition;
    Vector3 playerPosition;
};

#endif