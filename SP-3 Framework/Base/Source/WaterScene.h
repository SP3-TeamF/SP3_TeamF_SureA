#ifndef WATERSCENE_H
#define WATERSCENE_H

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
class WaterScene : public Scenebase
{


public:
	WaterScene();
	~WaterScene();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Reset();
	virtual void Render();
	virtual void Exit();

	//Update function
	void UpdatePlayerInputUpdates(double dt);

	//TextFile
	bool watermapclear;
	void readTextFile(string filename);
protected:
	vector<string>tutorialText;

private:
	float netScale;;
	TileMap tutorialMap;
	PLAYER_STATES playerState;
	string newLine;
	BasicEnemy tempEnemy;
	BasicEnemy tempEnemy2;
	BasicEnemy tempEnemy3;
	BasicEnemy tempEnemy4;
	BasicEnemy tempEnemy5;
	BasicEnemy tempEnemy6;
	BasicEnemy tempEnemy7;
	BasicEnemy tempEnemy8;


};

#endif