#include "Vector3.h"
#include "Character.h"
#include "AABB.h"
#include "weapon.h"

#ifndef PLAYER_H_
#define PLAYER_H_

enum PLAYER_STATE
{
    P_STATE_IDLE,
    P_STATE_MOVING_LEFT,
    P_STATE_MOVING_RIGHT,
    P_STATE_JUMP,
    P_STATE_FALL,

    NUM_STATES,
};


#define player Player::GetInstance()

class Player : public Character
{
public:
    static Player* GetInstance();
    static void DropInstance();

    //Updates
    void InAirUpdate(double dt);
    virtual void Update(double dt);
    void UpdateMovement(double dt);
	void fireWeapon(Vector3 view, Vector3 position);

    //Getters
    bool GetInAir();
    int GetCurrentTile();
    int GetStandingTile();
    PLAYER_STATE Get_Player_State();

    //Setters
    void SetPlayerBorder(int leftBorder, int rightBorder, int downBorder, int upBorder);
    void SetPlayerState(PLAYER_STATE newPlayerState);

    //Others
    void ConstrainPlayer();

    bool canJump;
  
	AABB playerHitbox;

	weapon *playerweapon;

protected:
    Player();
    ~Player();


private:
    bool inAir;
    int upBorder;
    int downBorder;
    int leftBorder;
    int rightBorder;

    PLAYER_STATE current_Player_State;
};

#endif PLAYER_H_