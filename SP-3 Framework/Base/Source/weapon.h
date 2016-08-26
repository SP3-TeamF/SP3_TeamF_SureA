#ifndef WEAPON_H_
#define WEAPON_H_

#include "BulletInfo.h"
#include "Vector3.h"
#include <vector>
#include "controls.h"
#include "Invent.h"
#include "BulletFactory.h"
using std::vector;


enum WEAPON_TYPE{
	WT_NET,
	WT_FIRE,
	WT_WATER,
	WT_AIR
};
class weapon
{
	
public:
	weapon();
    weapon(float timeBetweenEachBullet, int maxClipSize, int maxAmmoCapacity, double reloadTime, int weaponDamage);
	~weapon();

    void Update(double dt);
    void updateBullets(double dt);
    void resetWeaponAmmo();
    virtual void fireWeapon(Vector3 view, Vector3 position);


	//Getters
	int getCurrentHeldAmmo();
	int getCurrentLoadedBullet();
	int getMaxClipSize();
	Vector3 getBulletPosition();
	double getWeaponReloadTime();


    bool canFireBullet();

	int weaponDamage;

	WEAPON_TYPE WeaponType;

protected:
	int maxClipSize;
	int currentHeldAmmo;
	int maxAmmoCapacity;
	int currentLoadedAmmo;

	bool isReloading;

	double reloadTimer;
	double currentTime;
	double weaponReloadTime;
	double timeBetweenEachBullet;

};


#endif WEAPON_H_