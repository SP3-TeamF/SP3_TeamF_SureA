#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "SceneMapEditor.h"
#include "weapon.h"

class TutorialScene : public Scenebase
{
	enum WEAPON_TYPE{
		WT_NET,
		WT_FIRE
	};
public:
	TutorialScene();
	~TutorialScene();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	weapon* Weapon;
	WEAPON_TYPE WeaponType;
};

#endif