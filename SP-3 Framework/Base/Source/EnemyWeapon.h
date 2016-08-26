#ifndef ENEMY_WEAPON_H_
#define ENEMY_WEAPON_H_

#include "weapon.h"
using std::vector;

enum ENEMY_WEAPON{
	EW_FIRE,
	EW_AIR,
	EW_WATER
};

class EnemyWeapon : public weapon
{

public:
	EnemyWeapon();
	~EnemyWeapon();
	
	void Update(double dt);

private:
	ENEMY_WEAPON EWeapon;
};


#endif WEAPON_H_