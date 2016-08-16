#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Vector3.h"

class Character
{
public:
	Character();

	virtual ~Character();
	virtual void Update(double dt) = 0;

	//Getters
	int Get_cHealth();
	bool Get_cActive();
	float Get_cMoveSpeed();
	Vector3 Get_cPosition();
	Vector3 Get_cMovement();

	//Setters
	void Set_cHealth(int health);
	void Set_cActive(bool active);
	void Set_cMoveSpeed(float movespeed);
	void Set_cPosition(Vector3 position);
	void Set_cMovement(Vector3 movement);

	//Adders
	void Add_cHealth(int health);
	void Add_cMoveSpeed(float movespeed);
	void Add_cPosition(Vector3 position);
	void Add_cMovement(Vector3 movement);

protected:
	int c_Health;
	bool c_Active;
	float c_MoveSpeed;
	Vector3 c_Position;
	Vector3 c_Movement;
};

#endif CHARACTER_H_