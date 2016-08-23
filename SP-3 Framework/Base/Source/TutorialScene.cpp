#include "TutorialScene.h"
#include "weapon.h"
#include "Application.h"

TutorialScene::TutorialScene()
{
	Weapon = new weapon();
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
	
    Weapon = new weapon();

    tutorialMap.Init(1024, 800, 2048, 1600, 32);
    tutorialMap.LoadMap("Image//CSV//Zentut.csv");

    m_TileMap = &tutorialMap;

	netHit = false;
	heartScale = 5.f;
	heartMove = 0.f;
	stop = false;
	netScale = 32.f;
    playerPosition = Vector3((int)(player->Get_cPosition().x / m_TileMap->GetTileSize()), (int)(player->Get_cPosition().y / m_TileMap->GetTileSize()));
}

//Update functions
void TutorialScene::Update(double dt)
{
	//fps = 1 / dt;
	//cout << fps << endl;
    UpdateBullets(dt);
    Weapon->Update(dt);
	Scenebase::UpdateSpritesAnimastion(dt);
    UpdatePlayerInputUpdates(dt);
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
}	

void TutorialScene::UpdateBullets(double dt)
{
    vector<CBulletInfo*> temp = Weapon->GetBulletList();
	for (auto bulletIt : temp)
	{
		if (bulletIt->GetStatus())
		{
			Vector3 updatedPos = bulletIt->GetPosition() + (bulletIt->GetDirection() * bulletIt->GetSpeed()) * dt;
			//updatedPos.x += m_TileMap->GetTileSize() * 0.5;
			//updatedPos.y += m_TileMap->GetTileSize() * 0.5;

			int currentTile = 237;

			int tilePosX = updatedPos.x / m_TileMap->GetTileSize();
			int tilePosY = updatedPos.y / m_TileMap->GetTileSize();

			int test = (m_TileMap->GetTileType(tilePosX, tilePosY));

			if (test != currentTile)
			{
				//cout << bulletIt->GetPosition().x - GlobalData.world_X_offset << endl;

				if (bulletIt->GetBulletType() == BT_NET)
				{
					bulletIt->SetBulletType(BT_NETSPREAD);
					bulletIt->SetSpeed(0);
					bulletIt->SetScale(Vector3(32, 32, 0));
					bulletIt->SetLifetime(3);
				}
				else if (bulletIt->GetBulletType() != BT_NETSPREAD)
				{
					bulletIt->SetStatus(false);
				}
			}

			if (test == 244 && bulletIt->GetBulletType() == BT_FIRE)
			{
				m_TileMap->SetTile(237, tilePosX, tilePosY);
			}

			if (test == 86 && bulletIt->GetBulletType() == BT_AIR)
			{
				m_TileMap->SetTile(237, tilePosX, tilePosY);
			}
			/*if (test == 244 && bulletIt->GetBulletType() == BT_WATER)
			{
				m_TileMap->SetTile(237, tilePosX, tilePosY);
			}*/
		}
	}
		
}



void TutorialScene::UpdatePlayerInputUpdates(double dt)
{
	
    player->Update(dt);
	Weapon->Update(dt);
}

//Render functions
void TutorialScene::Render()
{

	Scenebase::Render();
	Scenebase::RenderHUD();
	if (m_TileMap != nullptr)
	{
		RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
	}
	RenderHUD();
	RenderMainCharacter();
	RenderBullets();
	Scenebase::RenderSprites();
	//renderthesprite->RenderSprites();

}

void TutorialScene::RenderBullets()
{
    vector<CBulletInfo*> temp = Weapon->GetBulletList();

    for (auto bulletIt : temp)
    {
        if (bulletIt->GetStatus())
        {
			if (bulletIt->GetBulletType() == BT_FIRE)
				Render2DMesh(meshList[GEO_FIRE], false, 16.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_AIR)
				Render2DMesh(meshList[GEO_AIR], false, 16.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_WATER)
				Render2DMesh(meshList[GEO_WATER], false, 16.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_NET)
				Render2DMesh(meshList[GEO_SMALLNET], false, 8.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);
			
			if (bulletIt->GetBulletType() == BT_NETSPREAD)
				Render2DMesh(meshList[GEO_BIGNET], false, bulletIt->GetScale().x, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);
		}	
	}

	//Enemy Bullets
	vector<CBulletInfo*> tempEnemy = Weapon->GetEnemyBulletList();

	for (auto enemyBulletIt : tempEnemy)
	{
		if (enemyBulletIt->GetStatus())
			Render2DMesh(meshList[GEO_FIRE], false, 32.0f, enemyBulletIt->GetPosition().x - GlobalData.world_X_offset, enemyBulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);
	}
}

void TutorialScene::RenderMainCharacter()
{
	
}

void TutorialScene::Exit()
{
}

//Other Functions
void TutorialScene::Reset()
{
    m_TileMap = &tutorialMap;
    netHit = false;
    stop = false;
    netScale = 32.f;
    playerPosition = Vector3((int)(player->Get_cPosition().x / m_TileMap->GetTileSize()), (int)(player->Get_cPosition().y / m_TileMap->GetTileSize()));
}