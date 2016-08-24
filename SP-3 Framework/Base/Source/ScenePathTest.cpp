#include "ScenePathTest.h"
#include "Player.h"
#include "GlobalDatas.h"


ScenePathTest::ScenePathTest()
{
    testEnemy.SetScanRadius(1000);
    testEnemy.Set_cMoveSpeed(100);
    testEnemy.SetAttackRadius(20);
    testEnemy.Set_cPosition(Vector3(380, 600, 0));
}

ScenePathTest::~ScenePathTest()
{
}

void ScenePathTest::Init()
{
    Scenebase::Init();

    //Player Variables 
    player->SetPlayerBorder(0, 1024, 0, 800);
    player->Set_cMoveSpeed(100);
    player->Set_cPosition(Vector3(320, 320, 0));

    GlobalData.world_X_offset = 0;
    GlobalData.world_Y_offset = 0;

    pathTestMap.Init(1024, 800, 1024, 800, 32);
    pathTestMap.LoadMap("Image//CSV//PathTest.csv");

    m_TileMap = &pathTestMap;

	heartScale = 5.f;
	heartMove = 0.f;

}

//Update functions
void ScenePathTest::Update(double dt)
{
	//float fps = 1 / dt;
	//cout << fps << endl;

    testEnemy.Update(dt);
	player->Update(dt);
	Scenebase::UpdateSpritesAnimation(dt);
}

//Render functions
void ScenePathTest::Render()
{
    Scenebase::Render();
    if (m_TileMap != nullptr)
    {
        RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
    }
	Scenebase::RenderBullet();
    Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    Render2DMesh(meshList[GEO_FIRE], false, 32, testEnemy.Get_cPosition().x , testEnemy.Get_cPosition().y, 0);// removed +16 
}

//Other Functions
void ScenePathTest::Exit()
{
}

void ScenePathTest::Reset()
{
    m_TileMap = &pathTestMap;

    GlobalData.world_X_offset = 0;
    GlobalData.world_Y_offset = 0;

    player->SetPlayerBorder(0, 1024, 0, 800);
    player->Set_cMoveSpeed(100);
    player->Set_cPosition(Vector3(320, 320, 0));

    pathTestMap.Init(1024, 800, 1024, 800, 32);
    pathTestMap.LoadMap("Image//CSV//PathTest.csv");

    testEnemy.SetScanRadius(1000);
    testEnemy.Set_cMoveSpeed(100);
    testEnemy.SetAttackRadius(20);
    testEnemy.Set_cPosition(Vector3(380, 600, 0));
}