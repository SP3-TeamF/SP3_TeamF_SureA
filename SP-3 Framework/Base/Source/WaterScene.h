#ifndef WATERSCENE_H
#define WATERSCENE_H

#include "SceneMapEditor.h"
#include "BasicEnemy.h"
#include "Pathfinding.h"
#include <vector>
using std::vector;



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

protected:


private:
	float netScale;;
	TileMap waterscene;
	
	string newLine;
	BasicEnemy tempEnemy;
	BasicEnemy tempEnemy2;
	BasicEnemy tempEnemy3;
	BasicEnemy tempEnemy4;
	BasicEnemy tempEnemy5;


};

#endif