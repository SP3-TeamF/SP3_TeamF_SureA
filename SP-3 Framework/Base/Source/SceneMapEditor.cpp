#include "SceneMapEditor.h"
#include "Application.h"
#include "GLFW\glfw3.h"

SceneMapEditor::SceneMapEditor()
{
}

SceneMapEditor::~SceneMapEditor()
{
}

void SceneMapEditor::Init()
{
    Scenebase::Init();

    EditorMap = nullptr;

    // Initialise and load the tile map
    EditorMap = nullptr;
    m_TileMap = nullptr;

    TilemapInit();
    MapEditorInit();

    CURR_EDITOR_STATE = MAP_EDITOR;
}

void SceneMapEditor::Update(double dt)
{
    switch (CURR_EDITOR_STATE)
    {
        case MAP_EDITOR:
        {
            UpdateMapEditor(dt);
            break;
        }
        case ITEM_SELECTOR:
        {
            UpdateSelectionScreen(dt);
            break;
        }
    }
}

void SceneMapEditor::Render()
{
    Scenebase::Render();

    Render2DMesh(meshList[GEO_BACKGROUND], false, 2.0f);

    switch (CURR_EDITOR_STATE)
    {
        case MAP_EDITOR:
        {
            RenderMapEditor();
            break;
        }
        case ITEM_SELECTOR:
        {
            RenderTileSelectionScreen();
            break;
        }
    }
}

void SceneMapEditor::Exit()
{

}

//Update functions
void SceneMapEditor::UpdateMapEditor(double dt)
{
    if (MapEditorName == "")
    {
        string mapName = "";

        cout << "Enter File Name: ";
        cin >> mapName;
        cout << endl;

        MapEditorName = "Image//CSV//" + mapName + ".csv";

        EditorMap = new TileMap();
        EditorMap->Init(1024, 800, 50, 64, 1600, 2048, 32);
        EditorMap->LoadMap(MapEditorName.c_str());
    }
    else
    {
        if (controls.isKeyboardButtonPressed(KEYBOARD_S))
        {
            EditorMap->SaveMap(MapEditorName);
        }

        if (controls.isKeyboardButtonPressed(KEYBOARD_F2))
        {
            MapEditorInit();
        }

		if (controls.isKeyboardButtonPressed(KEYBOARD_F11))
		{
			CURR_EDITOR_STATE = ITEM_SELECTOR;
		}
    }

    if (controls.isKeyboardButtonPressed(MOUSE_L_CLICK) || controls.isKeyboardButtonHeld(MOUSE_L_CLICK))
    {
        double x, y = 0;
        Application::GetCursorPos(&x, &y);
        y = Application::GetWindowHeight() - y;

        x = x / EditorMap->GetTileSize() + editor_X_Offet / EditorMap->GetTileSize();
		y = EditorMap->GetNumWorldTile_Height() - (y / EditorMap->GetTileSize() + editor_Y_Offet / EditorMap->GetTileSize());

        x = x < 0 ? 0 : x;
        x = x >= EditorMap->world_Tile_Map[0].size() ? EditorMap->world_Tile_Map[0].size() - 2 : x;

        y = y < 0 ? 0 : y;
        y = y >= EditorMap->world_Tile_Map.size() ? EditorMap->world_Tile_Map.size() - 1 : y;


        EditorMap->SetTile(currentTileType, x, y);
    }

    if (controls.isKeyboardButtonPressed(MOUSE_R_CLICK))
    {
        double x, y = 0;
        Application::GetCursorPos(&x, &y);
        y = Application::GetWindowHeight() - y;

        x = x / EditorMap->GetTileSize() + editor_X_Offet / EditorMap->GetTileSize();
		y = EditorMap->GetNumWorldTile_Height() - (y / EditorMap->GetTileSize() + editor_Y_Offet / EditorMap->GetTileSize());

        x = x < 0 ? 0 : x;
        x = x >= EditorMap->world_Tile_Map[0].size() ? EditorMap->world_Tile_Map[0].size() - 1 : x;

        y = y < 0 ? 0 : y;
        y = y >= EditorMap->world_Tile_Map.size() ? EditorMap->world_Tile_Map.size() - 1 : y;


        currentTileType = EditorMap->GetSpectificTileType(x, y);
    }

	if (controls.isKeyboardButtonPressed(KEYBOARD_LEFT) || controls.isKeyboardButtonHeld(KEYBOARD_LEFT))
    {
        editor_X_Offet -= EditorMap->GetTileSize();
        if (editor_X_Offet < 0)
        {
            editor_X_Offet = 0;
        }
        
    }

	if (controls.isKeyboardButtonPressed(KEYBOARD_RIGHT) || controls.isKeyboardButtonHeld(KEYBOARD_RIGHT))
    {
        editor_X_Offet += EditorMap->GetTileSize();
		if (editor_X_Offet > EditorMap->GetNumWorldTile_Width() * EditorMap->GetTileSize() * 0.5 - EditorMap->GetTileSize())
        {
			editor_X_Offet = EditorMap->GetNumWorldTile_Width() * EditorMap->GetTileSize() * 0.5 - EditorMap->GetTileSize();
        }
    }

	if (controls.isKeyboardButtonPressed(KEYBOARD_DOWN) || controls.isKeyboardButtonHeld(KEYBOARD_DOWN))
	{
		editor_Y_Offet -= EditorMap->GetTileSize();
		if (editor_Y_Offet < 0)
		{
			editor_Y_Offet = 0;
		}

	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_UP) || controls.isKeyboardButtonHeld(KEYBOARD_UP))
	{
		editor_Y_Offet += EditorMap->GetTileSize();
		if (editor_Y_Offet > EditorMap->GetNumWorldTile_Height() * EditorMap->GetTileSize() * 0.5 - EditorMap->GetTileSize())
		{
			editor_Y_Offet = EditorMap->GetNumWorldTile_Height() * EditorMap->GetTileSize() * 0.5 - EditorMap->GetTileSize();
		}
	}
}

void SceneMapEditor::UpdateSelectionScreen(double dt)
{
    if (controls.isKeyboardButtonPressed(MOUSE_L_CLICK))
    {
        double x, y = 0;
        Application::GetCursorPos(&x, &y);
        y = Application::GetWindowHeight() - y;

        x = x / TileSelectionScreen->GetTileSize();
        y = TileSelectionScreen->GetNumWorldTile_Height() - y / TileSelectionScreen->GetTileSize();

        x = x < 0 ? 0 : x;
        x = x >= TileSelectionScreen->world_Tile_Map[0].size() ? TileSelectionScreen->world_Tile_Map[0].size() - 1 : x;

        y = y < 0 ? 0 : y;
        y = y >= TileSelectionScreen->world_Tile_Map.size() ? TileSelectionScreen->world_Tile_Map.size() - 1 : y;

        currentTileType = TileSelectionScreen->GetSpectificTileType(x, y);
    }

    if (controls.isKeyboardButtonPressed(KEYBOARD_F11))
    {
        CURR_EDITOR_STATE = MAP_EDITOR;
    }
}

//Render functions
void SceneMapEditor::RenderMapEditor()
{
    if (EditorMap != nullptr)
    {
		RenderTileMap(EditorMap, editor_X_Offet, editor_Y_Offet);
    }
}

void SceneMapEditor::RenderTileSelectionScreen()
{
    if (TileSelectionScreen != nullptr)
    {
        RenderTileMap(TileSelectionScreen, 1);
    }
}

//Init Functions
void SceneMapEditor::TilemapInit()
{
    //Tile Map Init 
    TileSelectionScreen = new TileMap();
    TileSelectionScreen->Init(1024, 800, 25, 32, 800, 1024, 32);
    TileSelectionScreen->LoadMap("Image//CSV//TileMap.csv");
}

void SceneMapEditor::MapEditorInit()
{
    MapEditorName = "";
    editor_X_Offet = 0;
	editor_Y_Offet = 0;
    currentTileType = 0;

	controls.isControllerButtonHeld(CONTROLLER_1, CONTROLLER_RSTICKER);
}