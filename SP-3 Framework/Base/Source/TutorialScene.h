#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "SceneMapEditor.h"
#include "BasicEnemy.h"
#include "Pathfinding.h"
#include <vector>
using std::vector;

enum PLAYER_STATES{
	PS_INGAME,
	PS_INTUT,
	PS_INTUT2,
	PS_INTUT3
};
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

	//TextFile
	void readTextFile(string filename);
protected:
	vector<string>tutorialText;

private:
	float netScale;;
    TileMap tutorialMap;
	PLAYER_STATES playerState;
	string newLine;
	BasicEnemy tempEnemy;
	bool fireDone;
	bool waterDone;
	bool airDone;
};

#endif