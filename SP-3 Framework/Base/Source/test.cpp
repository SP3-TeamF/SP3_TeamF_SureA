#include "test.h"
#include "weapon.h"

test::test()
{
}

test::~test()
{
}

void test::Init()
{
	Scenebase::Init();
	player->SetPlayerBorder(64, 960, 64, 736);
	m_TileMap = new TileMap();
    m_TileMap->Init(1024, 800, 2048, 1600, 32);
	m_TileMap->LoadMap("Image//CSV//potato.csv");
	player->Set_cMoveSpeed(100);
}

void test::Update(double dt)
{
	if (controls.isKeyboardButtonHeld(KEYBOARD_W))
	{
		player->Add_cJumpVel(Vector3(0,1,0));
	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_S))
	{
		player->Add_cJumpVel(Vector3(0, -1, 0));
	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_D))
	{
		player->Add_cMoveVel(Vector3(1, 0, 0));
	}
	if (controls.isKeyboardButtonHeld(KEYBOARD_A))
	{
		player->Add_cMoveVel(Vector3(-1, 0, 0));
	}

	player->Add_cJumpVel(controls.GetControllerDirection(CONTROLLER_1, L_JOYSTICK));

	if (controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_LSTICKER))
	{
		player->Set_cMoveSpeed(300.f);
	}
	else{
		player->Set_cMoveSpeed(100.f);
	}
	
	player->Update(dt);	
}

void test::Render()
{
	Scenebase::Render();
	Render2DMesh(meshList[GEO_TEST], false, 2.0f, player->Get_cPosition().x, player->Get_cPosition().y, 0);
}

void test::Exit()
{}