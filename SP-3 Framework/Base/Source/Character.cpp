#include "Character.h"

Character::Character()
{
    c_Health = 0;
    c_Active = false;
    c_MoveSpeed = 1.f;
    c_MoveVel = Vector3(0, 0, 0);
    c_JumpVel = Vector3(0, 0, 0);
    c_Position = Vector3(0, 0, 0);
};

Character::~Character()
{

}

//Getters
int Character::Get_cHealth()
{
    return c_Health;
}

bool Character::Get_cActive()
{
    return c_Active;
}

float Character::Get_cMoveSpeed()
{
    return c_MoveSpeed;
}

Vector3 Character::Get_cMoveVel()
{
    return c_MoveSpeed;
}

Vector3 Character::Get_cJumpVel()
{
    return c_JumpVel;
}

Vector3 Character::Get_cPosition()
{
    return c_Position;
}

//Setters
void Character::Set_cHealth(int health)
{
    this->c_Health = health;
}

void Character::Set_cActive(bool active)
{
    this->c_Active = active;
}

void Character::Set_cMoveSpeed(float movespeed)
{
    this->c_MoveSpeed = movespeed;
}

void Character::Set_cMoveVel(Vector3 moveVel)
{
    this->c_MoveVel = moveVel;
}

void Character::Set_cJumpVel(Vector3 jumpVel)
{
    this->c_JumpVel = jumpVel;
}

void Character::Set_cPosition(Vector3 position)
{
    this->c_Position = position;
}

//Adders
void Character::Add_cHealth(int health)
{
    this->c_Health += health;
}

void Character::Add_cMoveSpeed(float movespeed)
{
    this->c_MoveSpeed += movespeed;
}

void Character::Add_cMoveVel(Vector3 moveVel)
{
    this->c_MoveVel += moveVel;
}

void Character::Add_cJumpVel(Vector3 jumpVel)
{
    this->c_JumpVel += jumpVel;
}

void Character::Add_cPosition(Vector3 position)
{
    this->c_Position += position; 
}
