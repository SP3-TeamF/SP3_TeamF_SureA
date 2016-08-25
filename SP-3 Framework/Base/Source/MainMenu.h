#ifndef MAINMENU_H
#define MAINMENU_H
#include "SceneMapEditor.h"

enum CURRENTLY_SELECTED
{
	Play = 1,
	Load,
	Credit,
	Exit_game

};


class MainMenu : public Scenebase
{
public:
	MainMenu();
	virtual ~MainMenu();

	virtual void Init();
	virtual void Exit();
	virtual void Render();
	virtual void Update(double dt);
	CURRENTLY_SELECTED currently_selected;

private:
	bool playSelect;
	bool TestLevelSelect;
	bool exitSelect;
	double timeDelay;
	float arrow_posx;
};


#endif