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
}

//Update functions
void ScenePathTest::Update(double dt)
{
    testEnemy.Update(dt);

    if (GlobalData.isControllerConnected)
    {
        if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_LSTICKER)))
        {
            player->Set_cMoveSpeed(300.f);
        }
        else{
            player->Set_cMoveSpeed(100.f);
        }
        player->Add_cMovement(controls.GetControllerDirection(CONTROLLER_1, L_JOYSTICK));
    }
    else
    {
        if (controls.isKeyboardButtonHeld(KEYBOARD_L_SHIFT))
        {
            player->Set_cMoveSpeed(300.f);
        }
        else{
            player->Set_cMoveSpeed(100.f);
        }

        if (controls.isKeyboardButtonPressed(KEYBOARD_LEFT) || controls.isKeyboardButtonHeld(KEYBOARD_LEFT))
        {
            GlobalData.world_X_offset -= m_TileMap->GetTileSize();
            if (GlobalData.world_X_offset < 0)
            {
                GlobalData.world_X_offset = 0;
            }
        }

        if (controls.isKeyboardButtonPressed(KEYBOARD_RIGHT) || controls.isKeyboardButtonHeld(KEYBOARD_RIGHT))
        {
            GlobalData.world_X_offset += m_TileMap->GetTileSize();
            if (GlobalData.world_X_offset > m_TileMap->GetWorldWidth() - m_TileMap->GetScreenWidth())
            {
                GlobalData.world_X_offset = m_TileMap->GetWorldWidth() - m_TileMap->GetScreenWidth();
            }
        }

        if (controls.isKeyboardButtonPressed(KEYBOARD_DOWN) || controls.isKeyboardButtonHeld(KEYBOARD_DOWN))
        {
            GlobalData.world_Y_offset -= m_TileMap->GetTileSize();
            if (GlobalData.world_Y_offset < 0)
            {
                GlobalData.world_Y_offset = 0;
            }
        }

        if (controls.isKeyboardButtonPressed(KEYBOARD_UP) || controls.isKeyboardButtonHeld(KEYBOARD_UP))
        {
            GlobalData.world_Y_offset += m_TileMap->GetTileSize();
            if (GlobalData.world_Y_offset > m_TileMap->GetWorldHeight() - m_TileMap->GetScreenHeight())
            {
                GlobalData.world_Y_offset = m_TileMap->GetWorldHeight() - m_TileMap->GetScreenHeight();
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
    }
    player->Update(dt);

}

//Render functions
void ScenePathTest::Render()
{
    Scenebase::Render();
    if (m_TileMap != nullptr)
    {
        RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
    }

    Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    Render2DMesh(meshList[GEO_FIRE], false, 32, testEnemy.Get_cPosition().x + 16, testEnemy.Get_cPosition().y + 16, 0);
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