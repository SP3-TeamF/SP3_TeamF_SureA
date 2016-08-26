#include "WaterScene.h"
#include "Application.h"


WaterScene::WaterScene()
{
}

WaterScene::~WaterScene()
{
}

void WaterScene::Init()
{
	Scenebase::Init();
	GlobalData.world_X_offset = 0;
	GlobalData.world_Y_offset = 0;

	player->SetPlayerBorder(128, 864, 128, 480);
	player->Set_cMoveSpeed(100);
	player->Set_cPosition(Vector3(800, 400, 0));

	tutorialMap.Init(1024, 800, 2048, 1600, 32);
	tutorialMap.LoadMap("Image//CSV//ZenTut.csv");

	m_TileMap = &tutorialMap;

	heartScale = 5.f;
	heartMove = 0.f;
	playerState = PS_INGAME;
	watermapclear = false;

}

//Update functions
void WaterScene::Update(double dt)
{
	tempEnemy.Update(dt);
	tempEnemy2.Update(dt);
	tempEnemy3.Update(dt);

	tempEnemy4.Update(dt);
	tempEnemy5.Update(dt);
	tempEnemy6.Update(dt);

	tempEnemy7.Update(dt);
	tempEnemy8.Update(dt);


	//fps = 1 / dt;
	//cout << fps << endl;
	Scenebase::UpdateSpritesAnimation(dt);
	UpdatePlayerInputUpdates(dt);


	Vector3 updatedPos = player->Get_cPosition() + (player->Get_cMovement() * player->Get_cMoveSpeed()) * dt;
	updatedPos.x += GlobalData.world_X_offset;
	updatedPos.y += GlobalData.world_Y_offset;

	int tilePosX = updatedPos.x / m_TileMap->GetTileSize();
	int tilePosY = updatedPos.y / m_TileMap->GetTileSize();

	int c_tile = m_TileMap->GetTileType(tilePosX, tilePosY);
	if (c_tile == 282){
		if (playerState == PS_INGAME)
			playerState = PS_INTUT;
	}
	else{
		playerState = PS_INGAME;
	}
	if (controls.isKeyboardButtonPressed(KEYBOARD_G)){
		playerState = PS_INTUT2;
	}

	if (controls.isKeyboardButtonHeld(KEYBOARD_ADD))
	{
		heartScale -= 0.1f;
		heartMove += 1.5f;
	}

	if (controls.isKeyboardButtonHeld(KEYBOARD_SUBTRACT))
	{
		heartScale += 0.1f;
		heartMove -= 1.5f;
		cout << heartScale << "      " << heartMove << endl;
	}

	if (playerState == PS_INTUT)
		readTextFile("Text//test.txt");
	if (playerState == PS_INGAME)
		readTextFile("Text//tutorial2.txt");
	if (playerState == PS_INTUT2)
		readTextFile("Text//tutorial3.txt");
}

void WaterScene::UpdatePlayerInputUpdates(double dt)
{
	player->Update(dt);
}

//Render functions
void WaterScene::Render()
{

	Scenebase::Render();
	if (m_TileMap != nullptr)
	{
		RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
	}
	Scenebase::RenderHUD();
	Scenebase::RenderBullet();
	Scenebase::RenderSprites();
	if (playerState != PS_INGAME){
		Render2DMesh(meshList[GEO_SCROLL], false, 1, Application::GetInstance().GetWindowWidth() * 0.1f, Application::GetInstance().GetWindowHeight()* 0.1f);
		for (int i = 0; i < tutorialText.size(); i++){
			RenderTextOnScreen(meshList[GEO_TEXT], tutorialText[i], Color(0, 0, 0), 20, Application::GetInstance().GetWindowWidth() * 0.3f, Application::GetInstance().GetWindowHeight() * 0.5f + i * -25);
		}
		tutorialText.clear();

	}
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy2.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy2.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy3.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy3.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);

	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy4.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy4.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy5.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy5.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy6.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy6.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);

	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy7.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy7.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy8.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy8.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);

	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy2.Get_cPosition().x + GlobalData.world_X_offset) / 10 +60), ((tempEnemy2.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy3.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy3.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy4.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy4.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy5.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy5.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy6.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy6.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy7.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy7.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy8.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy8.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));



}

void WaterScene::readTextFile(string filename){
	ifstream file(filename.c_str());
	string line;
	while (std::getline(file, line)){
		newLine = line + '\n';
		tutorialText.push_back(newLine);
	}

}


void WaterScene::Exit()
{
}

//Other Functions
void WaterScene::Reset()
{
	GlobalData.world_X_offset = 0;
	GlobalData.world_Y_offset = 0;

	player->SetPlayerBorder(128, 864, 128, 480);
	player->Set_cMoveSpeed(100);
	player->Set_cPosition(Vector3(800, 400, 0));

	tutorialMap.Init(1024, 800, 2048, 1600, 32);
	tutorialMap.LoadMap("Image//CSV//watermap.csv");

	m_TileMap = &tutorialMap;

	heartScale = 5.f;
	heartMove = 0.f;
	playerState = PS_INGAME;

	tempEnemy.SetAttackRadius(10);
	tempEnemy.SetScanRadius(164);
	tempEnemy.Set_cMoveSpeed(100);
	tempEnemy.Set_cPosition(Vector3(800, 490));

	tempEnemy2.SetAttackRadius(10);
	tempEnemy2.SetScanRadius(164);
	tempEnemy2.Set_cMoveSpeed(100);
	tempEnemy2.Set_cPosition(Vector3(850, 290));

	tempEnemy3.SetAttackRadius(10);
	tempEnemy3.SetScanRadius(164);
	tempEnemy3.Set_cMoveSpeed(100);
	tempEnemy3.Set_cPosition(Vector3(900, 450));

	tempEnemy4.SetAttackRadius(10);
	tempEnemy4.SetScanRadius(164);
	tempEnemy4.Set_cMoveSpeed(100);
	tempEnemy4.Set_cPosition(Vector3(800, 490));

	tempEnemy5.SetAttackRadius(10);
	tempEnemy5.SetScanRadius(164);
	tempEnemy5.Set_cMoveSpeed(100);
	tempEnemy5.Set_cPosition(Vector3(850, 290));

	tempEnemy6.SetAttackRadius(10);
	tempEnemy6.SetScanRadius(164);
	tempEnemy6.Set_cMoveSpeed(100);
	tempEnemy6.Set_cPosition(Vector3(900, 450));

	tempEnemy7.SetAttackRadius(10);
	tempEnemy7.SetScanRadius(164);
	tempEnemy7.Set_cMoveSpeed(100);
	tempEnemy7.Set_cPosition(Vector3(800, 490));

	tempEnemy8.SetAttackRadius(10);
	tempEnemy8.SetScanRadius(164);
	tempEnemy8.Set_cMoveSpeed(100);
	tempEnemy8.Set_cPosition(Vector3(850, 290));



}