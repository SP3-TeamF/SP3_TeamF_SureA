#include "Collisiontest.h"
#include "Application.h"
#include "GLFW\glfw3.h"

Collisiontest::Collisiontest()
{}

Collisiontest::~Collisiontest()
{}

void Collisiontest::Init()
{
	Scenebase::Init();
	player->SetPlayerBorder(64, 1024, 64, 736);
	player->Set_cMoveSpeed(100);

	EditorMap = nullptr;

    // Initialise and load the tile map

    TilemapInit();
    MapEditorInit();

	plswork = haha;
	m_TileMap->Init(800, 1024, 1600, 2048, 32);
	m_TileMap->LoadMap(MapEditorName.c_str());
	
}

void Collisiontest::Update(double dt)
{
	switch (plswork)
	{
	case haha:
	{
		UpdateMapEditor(dt);
		break;
	}
	case heheXD:
	{
		UpdateSelectionScreen(dt);
		break;
	}

	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_W))
	{
		player->Add_cMovement(Vector3(0, 1, 0));
	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_S))
	{
		player->Add_cMovement(Vector3(0, -1, 0));
	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_D))
	{
		player->Add_cMovement(Vector3(1, 0, 0));
	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_A))
	{
		player->Add_cMovement(Vector3(-1, 0, 0));
	}

	player->Add_cMovement(controls.GetControllerDirection(CONTROLLER_1, L_JOYSTICK));

	//cout << player->Get_cPosition() << endl;
	player->Update(dt);

	cout << m_TileMap->GetTileType(0, 0) << endl;

}


void Collisiontest::Render()
{

	Scenebase::Render();

	Render2DMesh(meshList[GEO_BACKGROUND], false, 2.0f);

	switch (plswork)
	{
	case haha:
		{
			RenderMapEditor();
			break;
		}
	case heheXD:
		{
			RenderTileSelectionScreen();
			break;
		}
	}

	Render2DMesh(meshList[GEO_TEST], false, 3.0f, player->Get_cPosition().x, player->Get_cPosition().y, 0);
}

void Collisiontest::Exit()
{}

//Update functions
void Collisiontest::UpdateMapEditor(double dt)
{
	if (MapEditorName == "")
	{
		string mapName = "";

		cout << "Enter File Name: ";
		cin >> mapName;
		cout << endl;

		MapEditorName = "Image//CSV//" + mapName + ".csv";

		m_TileMap = new TileMap();
		m_TileMap->Init(1024, 800, 2048, 1600, 32);
		m_TileMap->LoadMap(MapEditorName.c_str());
	}
	else
	{
		if (controls.isKeyboardButtonPressed(KEYBOARD_X))
		{
			m_TileMap->SaveMap(MapEditorName);
		}

		if (controls.isKeyboardButtonPressed(KEYBOARD_F2))
		{
			MapEditorInit();
		}

		if (controls.isKeyboardButtonPressed(KEYBOARD_F11))
		{
			plswork = heheXD;
		}
	}

	if (controls.isKeyboardButtonPressed(MOUSE_L_CLICK) || controls.isKeyboardButtonHeld(MOUSE_L_CLICK))
	{
		double x, y = 0;
		Application::GetCursorPos(&x, &y);
		y = Application::GetWindowHeight() - y;

		x = x / m_TileMap->GetTileSize() + editor_X_Offet / m_TileMap->GetTileSize();
		y = y / m_TileMap->GetTileSize() + editor_Y_Offet / m_TileMap->GetTileSize();

		x = x < 0 ? 0 : x;
		x = x >= m_TileMap->world_Tile_Map[0].size() ? m_TileMap->world_Tile_Map[0].size() - 1 : x;

		y = y < 0 ? 0 : y;
		y = y >= m_TileMap->world_Tile_Map.size() ? m_TileMap->world_Tile_Map.size() - 1 : y;


		m_TileMap->SetTile(currentTileType, x, y);

	}

	if (controls.isKeyboardButtonPressed(MOUSE_R_CLICK))
	{
		double x, y = 0;
		Application::GetCursorPos(&x, &y);
		y = Application::GetWindowHeight() - y;

		x = x / m_TileMap->GetTileSize() + editor_X_Offet / m_TileMap->GetTileSize();
		y = y / m_TileMap->GetTileSize() + editor_Y_Offet / m_TileMap->GetTileSize();

		x = x < 0 ? 0 : x;
		x = x >= m_TileMap->world_Tile_Map[0].size() ? m_TileMap->world_Tile_Map[0].size() - 1 : x;

		y = y < 0 ? 0 : y;
		y = y >= m_TileMap->world_Tile_Map.size() ? m_TileMap->world_Tile_Map.size() - 1 : y;


		currentTileType = m_TileMap->GetTileType(x, y);
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_LEFT) || controls.isKeyboardButtonHeld(KEYBOARD_LEFT))
	{
		editor_X_Offet -= m_TileMap->GetTileSize();
		if (editor_X_Offet < 0)
		{
			editor_X_Offet = 0;
		}
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_RIGHT) || controls.isKeyboardButtonHeld(KEYBOARD_RIGHT))
	{
		editor_X_Offet += m_TileMap->GetTileSize();
		if (editor_X_Offet > m_TileMap->GetWorldWidth() - m_TileMap->GetScreenWidth())
		{
			editor_X_Offet = m_TileMap->GetWorldWidth() - m_TileMap->GetScreenWidth();
		}
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_DOWN) || controls.isKeyboardButtonHeld(KEYBOARD_DOWN))
	{
		editor_Y_Offet -= m_TileMap->GetTileSize();
		if (editor_Y_Offet < 0)
		{
			editor_Y_Offet = 0;
		}
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_UP) || controls.isKeyboardButtonHeld(KEYBOARD_UP))
	{
		editor_Y_Offet += m_TileMap->GetTileSize();
		if (editor_Y_Offet > m_TileMap->GetWorldHeight() - m_TileMap->GetScreenHeight())
		{
			editor_Y_Offet = m_TileMap->GetWorldHeight() - m_TileMap->GetScreenHeight();
		}
	}
}

void Collisiontest::UpdateSelectionScreen(double dt)
{
	if (controls.isKeyboardButtonPressed(MOUSE_L_CLICK))
	{
		double x, y = 0;
		Application::GetCursorPos(&x, &y);
		y = Application::GetWindowHeight() - y;

		x = x / TileSelectionScreen->GetTileSize();
		y = y / TileSelectionScreen->GetTileSize();

		x = x < 0 ? 0 : x;
		x = x >= TileSelectionScreen->world_Tile_Map[0].size() ? TileSelectionScreen->world_Tile_Map[0].size() - 1 : x;

		y = y < 0 ? 0 : y;
		y = y >= TileSelectionScreen->world_Tile_Map.size() ? TileSelectionScreen->world_Tile_Map.size() - 1 : y;

		currentTileType = TileSelectionScreen->GetTileType(x, y);
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_F11))
	{
		plswork = haha;
	}
}

//Render functions
void Collisiontest::RenderMapEditor()
{
	if (m_TileMap != nullptr)
	{
		RenderTileMap(m_TileMap, editor_X_Offet, editor_Y_Offet);
	}
}

void Collisiontest::RenderTileSelectionScreen()
{
	if (TileSelectionScreen != nullptr)
	{
		RenderTileMap(TileSelectionScreen, 1);
	}
}

//Init Functions
void Collisiontest::TilemapInit()
{
	//Tile Map Init 
	TileSelectionScreen = new TileMap();
	TileSelectionScreen->Init(1024, 800, 1024, 800, 32);
	TileSelectionScreen->LoadMap("Image//CSV//TileMap.csv");
}

void Collisiontest::MapEditorInit()
{
	MapEditorName = "";
	editor_X_Offet = 0;
	editor_Y_Offet = 0;
	currentTileType = 0;

	controls.isControllerButtonHeld(CONTROLLER_1, CONTROLLER_RSTICKER);
}