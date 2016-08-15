#ifndef SCENE_MAPEDITOR_H
#define SCENE_MAPEDITOR_H

#include "Scenebase.h"

enum EDITOR_STATE
{
    MAP_EDITOR,
    ITEM_SELECTOR,
};

class SceneMapEditor : public Scenebase
{
public:

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

    //Constructor / Destructor
    SceneMapEditor();
    virtual ~SceneMapEditor();

    //Init functions
    void TilemapInit();
    void MapEditorInit();

    //Render functions
    void RenderMapEditor();
    void RenderTileSelectionScreen();

    //Update functions
    void UpdateMapEditor(double dt);
    void UpdateSelectionScreen(double dt);


private:
    int currentTileType;
    float editor_X_Offet;
    string MapEditorName;

    //Map Editor stuff
    TileMap* EditorMap;
    TileMap* TileSelectionScreen;

    EDITOR_STATE CURR_EDITOR_STATE;
};

#endif 
