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
	player->SetPlayerBorder(64, 800, 64, 736);
	
	m_TileMap = new TileMap();
	m_TileMap->Init(1024, 800, 2048, 1600, 32);
	m_TileMap->LoadMap("Image//CSV//ok.csv");
	player->Set_cMoveSpeed(100);
	player->Set_cPosition(Vector3(300, 200, 0));

	Weapon = new weapon();
}

void TutorialScene::Update(double dt)
{
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

	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_LSTICKER) || controls.isKeyboardButtonHeld(KEYBOARD_L_SHIFT)))
	{
		player->Set_cMoveSpeed(300.f);
	}
	else{
		player->Set_cMoveSpeed(100.f);
	}
	
	player->Update(dt);
	
	if ((controls.GetIsControllerTriggerPressed(CONTROLLER_1, R_TRIGGER)) || (controls.isKeyboardButtonPressed(KEYBOARD_SPACE))){

		if (WeaponType == WT_FIRE){
			Weapon->fireWeapon((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition());
		}
		if (WeaponType == WT_WATER){
			Weapon->waterWeapon((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition());
		}
		if (WeaponType == WT_AIR){
			Weapon->airWeapon((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition());
		}
		if (WeaponType == WT_NET){
			Weapon->fireNet((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition());
		}
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_UP) || controls.isKeyboardButtonPressed(KEYBOARD_1))){
		WeaponType = WT_NET;
		std::cout << "Net" << std::endl;
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_DOWN) || controls.isKeyboardButtonPressed(KEYBOARD_2))){
		WeaponType = WT_WATER;
		std::cout << "Water" << std::endl;
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_RIGHT) || controls.isKeyboardButtonPressed(KEYBOARD_3))){
		WeaponType = WT_AIR;
		std::cout << "Air" << std::endl;
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_LEFT) || controls.isKeyboardButtonPressed(KEYBOARD_4))){
		WeaponType = WT_FIRE;
		std::cout << "Fire" << std::endl;
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
	Weapon->Update(dt);

}	

void TutorialScene::Render()
{
	Scenebase::Render();
	if (m_TileMap != nullptr)
	{
		RenderTileMap(m_TileMap, GlobalData.world_X_offset, GlobalData.world_Y_offset);
	}
	Render2DMesh(meshList[GEO_TEST], false, 1.0f, player->Get_cPosition().x, player->Get_cPosition().y, 0);

	vector<CBulletInfo*> temp = Weapon->GetBulletList();
	for (auto bulletIt : temp)
	{
		if (bulletIt->GetStatus())
		{
			Render2DMesh(meshList[GEO_TEST], false, 1.0f, bulletIt->GetPosition().x, bulletIt->GetPosition().y, 0);
		}
	}
	
}

void TutorialScene::Exit()
{}