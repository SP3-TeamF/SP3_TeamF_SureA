#include "test.h"

test::test()
{}

test::~test()
{}

void test::Init()
{
	Scenebase::Init();
	player->SetPlayerBorder(64, 1024, 64, 736);
	m_TileMap = new TileMap();
	m_TileMap->Init(1024, 800, 25, 64, 800, 2048, 32);
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

	cout << player->Get_cPosition() << endl;
	player->Update(dt);


}

void test::Render()
{
	Scenebase::Render();
	Render2DMesh(meshList[GEO_TEST], false, 2.0f, player->Get_cPosition().x, player->Get_cPosition().y, 0);
}

void test::Exit()
{}