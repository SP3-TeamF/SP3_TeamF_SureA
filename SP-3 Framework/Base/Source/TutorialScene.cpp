#include "TutorialScene.h"
#include "Application.h"
#include "SceneManager.h"


TutorialScene::TutorialScene()
{
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Init()
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

}

//Update functions
void TutorialScene::Update(double dt)
{
	tempEnemy.Update(dt);
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

	//Fire
	if (c_tile == 107){
		sceneManager.currentScene = sceneManager.scenePathTest;
		sceneManager.currentScene->Reset();
		fireDone = true;
	}
	//Water
	if (c_tile == 180){
		sceneManager.currentScene = sceneManager.scenePathTest;
		sceneManager.currentScene->Reset();
		waterDone = true;
	}
	//Air
	if (c_tile == 436){
		sceneManager.currentScene = sceneManager.scenePathTest;
		sceneManager.currentScene->Reset();
		airDone = true;
	}
	//Tutorial Tile
	if (c_tile == 282){
		if (playerState == PS_INGAME)
			playerState = PS_INTUT;
	}
	else{
		playerState = PS_INGAME;
	}

	if (controls.isKeyboardButtonPressed(KEYBOARD_G) && playerState == PS_INTUT){
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

void TutorialScene::UpdatePlayerInputUpdates(double dt)
{
    player->Update(dt);
}

//Render functions
void TutorialScene::Render()
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
			RenderTextOnScreen(meshList[GEO_TEXT], tutorialText[i], Color(0,0, 0), 20, Application::GetInstance().GetWindowWidth() * 0.23f, Application::GetInstance().GetWindowHeight() * 0.5f + i * -25);
		}
		tutorialText.clear();

	}
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_DOT], false, 10, ((player->Get_cPosition().x + GlobalData.world_X_offset) /13+60 ), 
		((player->Get_cPosition().y + GlobalData.world_Y_offset) / 7.2 + 625));

	//Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy.Get_cPosition().x + GlobalData.world_X_offset) / 14.5 + 60), 
		//((tempEnemy.Get_cPosition().y + GlobalData.world_Y_offset) / 10.1 + 635));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy.Get_cPosition().x) / 12.6 + 60),
		((tempEnemy.Get_cPosition().y ) / 8 + 635));
	
	//for (auto enemyIt : Enemy_list)
	//{
	//	if (enemyIt.Get_cActive() == true)
	//	{
	//		Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((enemyIt.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((enemyIt.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	//	}
	//}
}

void TutorialScene::readTextFile(string filename){
	ifstream file(filename.c_str());
	string line;
	while (std::getline(file, line)){
		newLine = line + '\n';
		tutorialText.push_back(newLine);
	}
}


void TutorialScene::Exit()
{
}

//Other Functions
void TutorialScene::Reset()
{
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

	tempEnemy.SetAttackRadius(10);
	tempEnemy.SetScanRadius(100);
	tempEnemy.Set_cMoveSpeed(100);
	tempEnemy.Set_cPosition(Vector3(800, 490));
}