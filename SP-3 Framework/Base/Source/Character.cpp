#include "Character.h"

Character::Character()
{
	c_Health = 0;
	c_Active = false;
	c_MoveSpeed = 1.f;
	c_Position = Vector3(0, 0, 0);
	c_Movement = Vector3(0, 0, 0);
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

Vector3 Character::Get_cPosition()
{
	return c_Position;
}

Vector3 Character::Get_cMovement()
{
	return c_Movement;
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

void Character::Set_cPosition(Vector3 position)
{
	this->c_Position = position;
}
void Character::Set_cMovement(Vector3 movement)
{
	this->c_Movement = movement;
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

void Character::Add_cPosition(Vector3 position)
{
	this->c_Position += position;
}

void Character::Add_cMovement(Vector3 movement)
{
	this->c_Movement += movement;
}
