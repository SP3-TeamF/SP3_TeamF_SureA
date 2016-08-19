#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "SceneMapEditor.h"
#include "weapon.h"

class TutorialScene : public Scenebase
{


public:
	TutorialScene();
	~TutorialScene();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	float Test_X_OFFSET;
	float Test_Y_OFFSET;
	float netScale;
	bool netHit;
	bool stop;
	weapon* Weapon;
	Vector3 controllermovement;
};

#endif