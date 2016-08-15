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

    if (c_Position.x < leftBorder)
    {
        shift_X = c_Position.x - leftBorder;
        c_Position.x = leftBorder;
    }
    else if (c_Position.x > rightBorder)
    {
        shift_X = c_Position.x - rightBorder;
        c_Position.x = rightBorder;
    }

    if (c_Position.y < downBorder)
    {
        c_Position.y = downBorder;
        c_JumpVel.SetZero();
    }
    else if (c_Position.y > upBorder)
    {
        c_Position.y = upBorder;
    }

    shift_X += GlobalData.world_X_offset;

    float tileShifted = (m_TileMap->GetNumScreenTile_Width() * m_TileMap->GetTileSize());

    if (shift_X >= 0 && m_TileMap->GetWorldWidth() > tileShifted)
    {
        GlobalData.world_X_offset = shift_X;
    }
}

void Player::UpdateMovement(double dt)
{
    Vector3 updatedPos = c_Position + (c_JumpVel + (c_MoveVel * c_MoveSpeed)) * dt;
    updatedPos.x += GlobalData.world_X_offset;
    updatedPos.y += m_TileMap->GetTileSize() * 0.5;

    float armOffsetX = m_TileMap->GetTileSize() * 0.35;
    float legOffsetX = m_TileMap->GetTileSize() * 0.1;

    float limbOffsetY = m_TileMap->GetTileSize();
    float extraOffsetY = m_TileMap->GetTileSize() * 0.9;

    int playerHead = m_TileMap->GetTileType(updatedPos.x, updatedPos.y);

    int leftHand = m_TileMap->GetTileType(updatedPos.x - armOffsetX, updatedPos.y);
	int rightHand = m_TileMap->GetTileType(updatedPos.x + armOffsetX, updatedPos.y);

    int extraCheckTopLeft = m_TileMap->GetTileType(updatedPos.x - armOffsetX, updatedPos.y);
    int extraCheckTopRight = m_TileMap->GetTileType(updatedPos.x + armOffsetX, updatedPos.y);
    
    int extraCheckBottomLeft = m_TileMap->GetTileType(updatedPos.x - armOffsetX, updatedPos.y - extraOffsetY);
    int extraCheckBottomRight = m_TileMap->GetTileType(updatedPos.x + armOffsetX, updatedPos.y - extraOffsetY);

	int leftLeg = m_TileMap->GetTileType(updatedPos.x - legOffsetX, updatedPos.y - limbOffsetY);
	int rightLeg = m_TileMap->GetTileType(updatedPos.x + legOffsetX, updatedPos.y - limbOffsetY);

    if (playerHead != 0)
    {
        c_JumpVel.SetZero();
    }

    if (leftLeg != 0 || rightLeg != 0)
    {
        inAir = false;
        canJump = true;
        c_JumpVel.SetZero();
        if (c_MoveVel.x == 0)
        {
            current_Player_State = P_STATE_IDLE;
        }
    }
    else
    {
        inAir = true;
    }

    if (c_MoveVel.x < 0)
    {
        if (
            leftHand != 0 ||
            extraCheckTopLeft != 0 ||
            extraCheckBottomLeft != 0 
            )
        {
            c_MoveVel.SetZero();
        }
    }
    else
    {
        if (
            rightHand != 0 ||
            extraCheckTopRight != 0 ||
            extraCheckBottomRight != 0
            )
        {
            c_MoveVel.SetZero();
        }
    }
    

    this->c_Position = c_Position + (c_JumpVel + (c_MoveVel * c_MoveSpeed)) * dt;
    
    //To Let Player stay exactly on ground
    c_MoveVel.SetZero();
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