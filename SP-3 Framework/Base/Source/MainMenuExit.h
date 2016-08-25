#ifndef MAINMENUEXIT_H
#define MAINMENUEXIT_H
#include "SceneBase.h"

enum YON
{
	YES = 1,
	NO
};

class MainMenuExit : public Scenebase
{
public:
	MainMenuExit();
	virtual ~MainMenuExit();
	virtual void Init();
	virtual void Exit();
	virtual void Render();
	virtual void Update(double dt);
	YON yesorno;

private:
	bool yesSelected;
	bool noSelected;
	double timeDelay;
	float arrow_posx;
};



#endif