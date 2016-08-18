#include "Player.h"
#include "GlobalDatas.h"

static Player* player_Instance = 0;

Player::Player()
{
	inAir = false;
	canJump = true;
	c_Health = 0;
	c_Active = false;
	c_Position = Vector3(0, 0, 0);
	upBorder = 0;
	downBorder = 0;
	leftBorder = 0;
	rightBorder = 0;
	current_Player_State = P_STATE_IDLE;
}

Player::~Player()
{

}

void Player::Update(double dt)
{
	if (m_TileMap != nullptr)
	{
		ConstrainPlayer();
		UpdateMovement(dt);
	}
}

Player* Player::GetInstance()
{
	if (player_Instance == 0)
	{
		player_Instance = new Player();
	}
	return player_Instance;
}

void Player::DropInstance()
{
	if (player_Instance != 0)
	{
		delete player_Instance;
		player_Instance = 0;
	}
}

void Player::SetPlayerBorder(int leftBorder, int rightBorder, int downBorder, int upBorder)
{
	this->leftBorder = leftBorder;
	this->rightBorder = rightBorder;
	this->upBorder = upBorder;
	this->downBorder = downBorder;
}

void Player::ConstrainPlayer()
{

	float shift_X = 0;
	float shift_Y = 0;

	if (c_Position.x < leftBorder)
	{
		shift_X = c_Position.x - leftBorder;
		c_Position.x = leftBorder;
	}
	else if (c_Position.x > rightBorder)
	{
		shift_X = c_Position.x - rightBorder;

		
		c_Position.x = rightBorder;
		if (GlobalData.world_X_offset>(m_TileMap->GetWorldWidth() - m_TileMap->GetScreenWidth()))
			GlobalData.world_X_offset = (m_TileMap->GetWorldWidth() - m_TileMap->GetScreenWidth());
	}

	if (c_Position.y < downBorder)
	{
		shift_Y = c_Position.y - downBorder;
		c_Position.y = downBorder;

	}
	else if (c_Position.y > upBorder)
	{
		shift_Y = c_Position.y - upBorder;
		c_Position.y = upBorder;
		if (GlobalData.world_Y_offset>(m_TileMap->GetWorldHeight() - m_TileMap->GetScreenHeight()))
			GlobalData.world_Y_offset = (m_TileMap->GetWorldHeight() - m_TileMap->GetScreenHeight());
	}

	shift_X += GlobalData.world_X_offset;
	shift_Y += GlobalData.world_Y_offset;

	float tileShifted = (m_TileMap->GetNumScreenTile_Width() * m_TileMap->GetTileSize());

	if (shift_X >= 0 && m_TileMap->GetWorldWidth() > tileShifted)
	{
		GlobalData.world_X_offset = shift_X;
	}

	if (shift_Y >= 0 && m_TileMap->GetWorldHeight () > tileShifted)
	{
		GlobalData.world_Y_offset = shift_Y;
	}
}

void Player::UpdateMovement(double dt)
{


		Vector3 updatedPos = c_Position + (c_Movement * c_MoveSpeed) * dt;
	updatedPos.x += m_TileMap->GetTileSize() * 0.5  + GlobalData.world_X_offset;
	updatedPos.y += m_TileMap->GetTileSize() * 0.5 + GlobalData.world_Y_offset;

	int currentTile = 237;

	int tilePosX = updatedPos.x / m_TileMap->GetTileSize() + GlobalData.world_X_offset;
	int tilePosY = updatedPos.y / m_TileMap->GetTileSize() + GlobalData.world_Y_offset;

	float armOffsetX = m_TileMap->GetTileSize() * 0.3;
	float legOffsetX = m_TileMap->GetTileSize() * 0.3;

	float limbOffsetY = m_TileMap->GetTileSize() * 0.35;
	float limbOffsetY_H = m_TileMap->GetTileSize() * 0.2;

	float extraOffsetY_t = m_TileMap->GetTileSize() * 0.25;
	float extraOffseyY_b = m_TileMap->GetTileSize() * 0.4;

	float rightOffsetX = m_TileMap->GetTileSize() * 0.2;
	//int c_tile = m_TileMap->GetTileType(tilePosX, tilePosY);

	int rightHand = m_TileMap->GetTileType(( updatedPos.x + armOffsetX) / m_TileMap->GetTileSize()  , (updatedPos.y + limbOffsetY_H) / m_TileMap->GetTileSize());
	int rightLeg = m_TileMap->GetTileType(( updatedPos.x + legOffsetX) / m_TileMap->GetTileSize() , (updatedPos.y - limbOffsetY) / m_TileMap->GetTileSize());

	int leftHand = m_TileMap->GetTileType(( updatedPos.x - armOffsetX) / m_TileMap->GetTileSize() , (updatedPos.y + limbOffsetY_H) / m_TileMap->GetTileSize());
	int leftLeg = m_TileMap->GetTileType(( updatedPos.x - legOffsetX) / m_TileMap->GetTileSize() , (updatedPos.y - limbOffsetY) / m_TileMap->GetTileSize());

	int extraCheckTopLeft = m_TileMap->GetTileType(( updatedPos.x - rightOffsetX) / m_TileMap->GetTileSize()  ,  (updatedPos.y + extraOffsetY_t) / m_TileMap->GetTileSize());
	int extraCheckTopRight = m_TileMap->GetTileType(( updatedPos.x + rightOffsetX) / m_TileMap->GetTileSize() ,  (updatedPos.y + extraOffsetY_t) / m_TileMap->GetTileSize());

	int extraCheckBottomLeft = m_TileMap->GetTileType(( updatedPos.x - rightOffsetX) / m_TileMap->GetTileSize() ,  (updatedPos.y - extraOffseyY_b) / m_TileMap->GetTileSize());
	int extraCheckBottomRight = m_TileMap->GetTileType(( updatedPos.x + rightOffsetX) / m_TileMap->GetTileSize() , (updatedPos.y - extraOffseyY_b) / m_TileMap->GetTileSize());

	if (c_Movement.y > 0)
	{
		if (extraCheckTopLeft != currentTile || extraCheckTopRight != currentTile)
		{
			c_Movement.y = 0;
		}
		if (leftHand != currentTile || rightHand != currentTile)
		{
			c_Movement.x = 0;
		}
	}
	if (c_Movement.y < 0)
	{
		if (extraCheckBottomLeft != currentTile || extraCheckBottomRight != currentTile)
		{
			c_Movement.y = 0;
		}
		if (leftLeg != currentTile || rightLeg != currentTile)
		{
			c_Movement.x = 0;
		}
	}
	if (c_Movement.x > 0)
	{
		if (extraCheckTopRight != currentTile || extraCheckBottomRight != currentTile)
		{
			c_Movement.y = 0;
		}

		if (rightHand != currentTile || rightLeg != currentTile)
		{
			c_Movement.x = 0;
		}
	}
	if (c_Movement.x <0)
	{
		if (extraCheckTopLeft != currentTile || extraCheckBottomLeft != currentTile)
		{
			c_Movement.y = 0;
		}
		if (leftHand != currentTile || leftLeg != currentTile)
		{
			c_Movement.x = 0;
		}
	}

	this->c_Position = c_Position + (c_Movement * c_MoveSpeed) * dt;
	//cout << GlobalData.world_X_offset << " " << rightLeg << "   here" <<(m_TileMap->GetWorldWidth() - m_TileMap->GetNumScreenTile_Width())<< endl;
	//cout << m_TileMap->GetWorldWidth() << " ere" << m_TileMap->GetScreenWidth() << endl;
	//To Let Player stay exactly on ground
	c_Movement.SetZero();
}

bool Player::GetInAir()
{
	return inAir;
}

PLAYER_STATE Player::Get_Player_State()
{
	return current_Player_State;
}

void Player::SetPlayerState(PLAYER_STATE newPlayerState)
{
	this->current_Player_State = newPlayerState;
}

int Player::GetStandingTile()
{
	if (m_TileMap != nullptr)
	{
		int posX = c_Position.x + GlobalData.world_X_offset;
		int posY = c_Position.y + GlobalData.world_Y_offset - m_TileMap->GetTileSize();
		return m_TileMap->GetTileType(posX, posY);
	}
	return -1;
}

int Player::GetCurrentTile()
{
	if (m_TileMap != nullptr)
	{
		int posX = c_Position.x + GlobalData.world_X_offset;
		int posY = c_Position.y + GlobalData.world_Y_offset - m_TileMap->GetTileSize() * 0.5;
		return m_TileMap->GetTileType(posX, posY);
	}
	return -1;
}