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
	player->Set_cPosition(Vector3(500, 400, 0));

	waterscene.Init(1024, 800, 2048, 1600, 32);
	waterscene.LoadMap("Image//CSV//watermap.csv");

	m_TileMap = &waterscene;

	
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



}

void WaterScene::UpdatePlayerInputUpdates(double dt)
{
	player->Update(dt);
}

//Render functions
void WaterScene::Render()
{

	/*if (backspeed <-1600 - 1600 * multi)
		multi++;
	if (backspeed < -1600 - 1600 * multi2)
		multi2++;*/

	//Render2DMesh(meshList[GEO_SKYBACK], false, 2, backspeed, 0);
	////end at 1600
	//Render2DMesh(meshList[GEO_SKYBACK], false, 2, 1600 * multi + backspeed, 0);

	//Render2DMesh(meshList[GEO_SKYBACK], false, 2, 1600 + 1600 * multi2 + backspeed, 0);



	//Render2DMesh(meshList[GEO_LAVABACK], false, 2000, 500, 0, 0);

	
	Scenebase::Render();
	Render2DMesh(meshList[GEO_WATERBACK], false, 2000, 500, 0, 0);
	if (m_TileMap != nullptr)
	{
		RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
	}
	

/*	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy2.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy2.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy3.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy3.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);

	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy4.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy4.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);
	Render2DMesh(meshList[GEO_FIRE], false, 32, tempEnemy5.Get_cPosition().x + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_X_offset, tempEnemy5.Get_cPosition().y + m_TileMap->GetTileSize() * 0.5 - GlobalData.world_Y_offset, 0);

	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy2.Get_cPosition().x + GlobalData.world_X_offset) / 10 +60), ((tempEnemy2.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy3.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy3.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy4.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy4.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	Render2DMesh(meshList[GEO_ENEMYDOT], false, 10, ((tempEnemy5.Get_cPosition().x + GlobalData.world_X_offset) / 10 + 60), ((tempEnemy5.Get_cPosition().y + GlobalData.world_Y_offset) / 5.5 + 625));
	*/Scenebase::RenderHUD();
	Scenebase::RenderBullet();
	Scenebase::RenderSprites();
	cout << player->Get_cPosition().x << player->Get_cPosition().y << endl;


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
	player->Set_cPosition(Vector3(300, 200, 0));

	waterscene.Init(1024, 800, 2048, 1600, 32);
	waterscene.LoadMap("Image//CSV//watermap.csv");

	m_TileMap = &waterscene;


	tempEnemy.SetAttackRadius(10);
	tempEnemy.SetScanRadius(164);
	tempEnemy.Set_cMoveSpeed(100);
	tempEnemy.Set_cPosition(Vector3(500, 400));

	tempEnemy2.SetAttackRadius(10);
	tempEnemy2.SetScanRadius(164);
	tempEnemy2.Set_cMoveSpeed(100);
	tempEnemy2.Set_cPosition(Vector3(500, 1200));

	tempEnemy3.SetAttackRadius(10);
	tempEnemy3.SetScanRadius(164);
	tempEnemy3.Set_cMoveSpeed(100);
	tempEnemy3.Set_cPosition(Vector3(1500, 250));

	tempEnemy4.SetAttackRadius(10);
	tempEnemy4.SetScanRadius(164);
	tempEnemy4.Set_cMoveSpeed(100);
	tempEnemy4.Set_cPosition(Vector3(1600, 1100));
	
	tempEnemy5.SetAttackRadius(10);
	tempEnemy5.SetScanRadius(164);
	tempEnemy5.Set_cMoveSpeed(100);
	tempEnemy5.Set_cPosition(Vector3(1500, 400));



}