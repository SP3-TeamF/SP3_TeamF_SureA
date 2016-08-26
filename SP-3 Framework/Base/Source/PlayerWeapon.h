#ifndef PLAYER_WEAPON_H_
#define PLAYER_WEAPON_H_

#include "weapon.h"
using std::vector;

class PlayerWeapon : public weapon
{

public:
	PlayerWeapon();
	~PlayerWeapon();

	void Update(double dt);
	virtual void fireWeapon(Vector3 view, Vector3 position);
private:
};


#endif PLAYER_WEAPON_H_