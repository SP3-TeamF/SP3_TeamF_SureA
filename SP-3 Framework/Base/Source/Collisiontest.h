#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include "Scenebase.h"


enum NOTATEST
{
	haha,
	heheXD,
};

class Collisiontest : public Scenebase
{

public:

	virtual void Init();
	virtual void Update(double dt);
    virtual void Reset();
	virtual void Render();
	virtual void Exit();

	Collisiontest();
	virtual ~Collisiontest();

	void TilemapInit();
	void MapEditorInit();

	//Render functions
	void RenderMapEditor();
	void RenderTileSelectionScreen();

	//Update functions
	void UpdateMapEditor(double dt);
	void UpdateSelectionScreen(double dt);

	void updateCollision(double dt);

private:
	int currentTileType;
	float editor_X_Offet;
	float editor_Y_Offet;
	string MapEditorName;

	//Map Editor stuff
	TileMap* EditorMap;
	TileMap* TileSelectionScreen;

	NOTATEST plswork;
};

#endif