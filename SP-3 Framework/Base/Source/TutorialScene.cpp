#include "TutorialScene.h"
#include "Application.h"


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
    tutorialMap.LoadMap("Image//CSV//fireLevel.csv");

    m_TileMap = &tutorialMap;

	netHit = false;
	heartScale = 5.f;
	heartMove = 0.f;
	stop = false;
	netScale = 32.f;

}

//Update functions
void TutorialScene::Update(double dt)
{
	//fps = 1 / dt;
	//cout << fps << endl;
    Scenebase::UpdateSpritesAnimation(dt);
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

void TutorialScene::UpdatePlayerInputUpdates(double dt)
{
    player->Update(dt);
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
	Scenebase::RenderBullet();
	Scenebase::RenderSprites();
	//renderthesprite->RenderSprites();

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
    GlobalData.world_X_offset = 0;
    GlobalData.world_Y_offset = 0;

    player->SetPlayerBorder(128, 864, 128, 480);
    player->Set_cMoveSpeed(100);
    player->Set_cPosition(Vector3(800, 400, 0));

    tutorialMap.Init(1024, 800, 2048, 1600, 32);
    tutorialMap.LoadMap("Image//CSV//Zentut.csv");

    m_TileMap = &tutorialMap;

    netHit = false;
    heartScale = 5.f;
    heartMove = 0.f;
    stop = false;
    netScale = 32.f;

}