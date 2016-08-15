#ifndef WEAPON_H_
#define WEAPON_H_

#include "BulletInfo.h"
#include "Vector3.h"
#include <vector>
#include "GlobalDatas.h"
using std::vector;

class weapon
{
public:
	weapon();
    weapon(float timeBetweenEachBullet, int maxClipSize, int maxAmmoCapacity, double reloadTime, int weaponDamage);
	~weapon();

    void Update(double dt);
    void reloadWeapon();
    void updateBullets(double dt);
    void resetWeaponAmmo();
    void fireWeapon(Vector3 view, Vector3 position);
    
    bool canFireBullet();

	double getWeaponReloadTime();
    int getCurrentHeldAmmo();
    int getCurrentLoadedBullet();
    int getMaxClipSize();
    int getMaxAmmoCapacity();
	int weaponDamage;
private:
	int maxClipSize;
	int currentHeldAmmo;
	int maxAmmoCapacity;
	int currentLoadedAmmo;

	bool isReloading;

    double currentTime;
    double weaponReloadTime;
    double timeBetweenEachBullet;

};


#endif WEAPON_H_