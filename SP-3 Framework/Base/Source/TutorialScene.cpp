#include "TutorialScene.h"
#include "weapon.h"

TutorialScene::TutorialScene()
{
	Weapon = new weapon();
}

TutorialScene::~TutorialScene()
{}

void TutorialScene::Init()
{
    Scenebase::Init();

    GlobalData.world_X_offset = 0;
    GlobalData.world_Y_offset = 0;
    player->SetPlayerBorder(128, 864, 128, 576);

    m_TileMap = new TileMap();
    m_TileMap->Init(1024, 800, 2048, 1600, 32);
    m_TileMap->LoadMap("Image//CSV//ok.csv");
    player->Set_cMoveSpeed(100);
    player->Set_cPosition(Vector3(300, 200, 0));
    controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK) = Vector3(0, 0, 0);
    Weapon = new weapon();

    playerPosition = Vector3((int)(player->Get_cPosition().x / m_TileMap->GetTileSize()), (int)(player->Get_cPosition().y / m_TileMap->GetTileSize()));
}

//Update functions
void TutorialScene::Update(double dt)
{
    UpdateBullets(dt);
    Weapon->Update(dt);
    UpdateSpriteAnimations(dt);
    UpdatePlayerInputUpdates(dt);
}	

void TutorialScene::UpdateBullets(double dt)
{
    vector<CBulletInfo*> temp = Weapon->GetBulletList();
    for (auto bulletIt : temp)
    {
        Vector3 updatedPos = bulletIt->GetPosition() + (bulletIt->GetDirection() * bulletIt->GetSpeed()) * dt;
        updatedPos.x += m_TileMap->GetTileSize() * 0.5 + GlobalData.world_X_offset;
        updatedPos.y += m_TileMap->GetTileSize() * 0.5 + GlobalData.world_Y_offset;

        int currentTile = 237;

        int tilePosX = updatedPos.x / m_TileMap->GetTileSize();
        int tilePosY = updatedPos.y / m_TileMap->GetTileSize();
        int test = (m_TileMap->GetTileType(tilePosX, tilePosY));

        if (test != currentTile)
        {
            bulletIt->SetStatus(false);
            bulletIt->SetPosition(Vector3(player->Get_cPosition().x, player->Get_cPosition().y, 0));
        }
    }
}

void TutorialScene::UpdateSpriteAnimations(double dt)
{
    SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWN]);
    if (sa1)
    {
        sa1->Update(dt);
        sa1->m_anim->animActive = true;
    }
    SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCUP]);
    if (sa2)
    {
        sa2->Update(dt);
        sa2->m_anim->animActive = true;
    }
    SpriteAnimation *sa3 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCLEFT]);
    if (sa3)
    {
        sa3->Update(dt);
        sa3->m_anim->animActive = true;
    }
    SpriteAnimation *sa4 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCRIGHT]);
    if (sa4)
    {
        sa4->Update(dt);
        sa4->m_anim->animActive = true;
    }
    SpriteAnimation *sa5 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCTOPLEFT]);
    if (sa5)
    {
        sa5->Update(dt);
        sa5->m_anim->animActive = true;
    }
    SpriteAnimation *sa6 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWNLEFT]);
    if (sa6)
    {
        sa6->Update(dt);
        sa6->m_anim->animActive = true;
    }
    SpriteAnimation *sa7 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWNRIGHT]);
    if (sa7)
    {
        sa7->Update(dt);
        sa7->m_anim->animActive = true;
    }
    SpriteAnimation *sa8 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCTOPRIGHT]);
    if (sa8)
    {
        sa8->Update(dt);
        sa8->m_anim->animActive = true;
    }

    SpriteAnimation *sa9 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
    if (sa9)
    {
        sa9->Update(dt);
        sa9->m_anim->animActive = true;
    }

    SpriteAnimation *sa10 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATER]);
    if (sa10)
    {
        sa10->Update(dt);
        sa10->m_anim->animActive = true;
    }

    SpriteAnimation *sa11 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIR]);
    if (sa11)
    {
        sa11->Update(dt);
        sa11->m_anim->animActive = true;
    }
}

void TutorialScene::UpdatePlayerInputUpdates(double dt)
{
    player->Add_cMovement(controls.GetControllerDirection(CONTROLLER_1, L_JOYSTICK));

    if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_LSTICKER) || controls.isKeyboardButtonHeld(KEYBOARD_L_SHIFT)))
    {
        player->Set_cMoveSpeed(300.f);
    }
    else{
        player->Set_cMoveSpeed(100.f);
    }

    player->Update(dt);

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

//Render functions
void TutorialScene::Render()
{
	Scenebase::Render();
	
    RenderMainCharacter();
    RenderBullets();

}

void TutorialScene::RenderBullets()
{
    vector<CBulletInfo*> temp = Weapon->GetBulletList();

    for (auto bulletIt : temp)
    {
        if (bulletIt->GetStatus())
        {

            if (bulletIt->GetBulletType() == BT_FIRE)
                Render2DMesh(meshList[GEO_FIRE], false, 32.0f, bulletIt->GetPosition().x, bulletIt->GetPosition().y, 0);

            if (bulletIt->GetBulletType() == BT_AIR)
                Render2DMesh(meshList[GEO_AIR], false, 32.0f, bulletIt->GetPosition().x, bulletIt->GetPosition().y, 0);

            if (bulletIt->GetBulletType() == BT_WATER)
                Render2DMesh(meshList[GEO_WATER], false, 32.0f, bulletIt->GetPosition().x, bulletIt->GetPosition().y, 0);

            /*	if (WeaponType == WT_NET)
            Render2DMesh(meshList[GEO_NET], false, 32.0f, bulletIt->GetPosition().x, bulletIt->GetPosition().y, 0);
            */

        }
    }
}

void TutorialScene::RenderMainCharacter()
{
    if (m_TileMap != nullptr)
    {
        RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
    }
    //	player->Add_cMovement(controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK));
    if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y > 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x>0)
    {
        //render top right
        Render2DMesh(meshList[GEO_MCTOPRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y > 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x < 0)
    {
        //render top left
        Render2DMesh(meshList[GEO_MCTOPLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y < 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x < 0)
    {
        //renderbot left
        Render2DMesh(meshList[GEO_MCDOWNLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y <0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x > 0)
    {
        //render bot right
        Render2DMesh(meshList[GEO_MCDOWNRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == 1 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == 0)
    {
        //render up
        Render2DMesh(meshList[GEO_MCUP], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);

    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == -1 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == 0)
    {
        //render down
        Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == 1)
    {
        //render right
        Render2DMesh(meshList[GEO_MCRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == -1)
    {
        //render left
        Render2DMesh(meshList[GEO_MCLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    }
    else
        Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
}

void TutorialScene::Exit()
{}