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
    Vector3 Get_cMoveVel();
    Vector3 Get_cJumpVel(); 
    Vector3 Get_cPosition();

    //Setters
    void Set_cHealth(int health);
    void Set_cActive(bool active);
    void Set_cMoveSpeed(float movespeed);
    void Set_cMoveVel(Vector3 moveVel);
    void Set_cJumpVel(Vector3 jumpVel);
    void Set_cPosition(Vector3 position);

    //Adders
    void Add_cHealth(int health);
    void Add_cMoveSpeed(float movespeed);
    void Add_cMoveVel(Vector3 moveVel);
    void Add_cJumpVel(Vector3 jumpVel);
    void Add_cPosition(Vector3 position);

protected:
    int c_Health;
    bool c_Active;
    float c_MoveSpeed;
    Vector3 c_MoveVel;
    Vector3 c_JumpVel;
    Vector3 c_Position;
};

#endif CHARACTER_H_