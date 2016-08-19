#ifndef WEAPON_H_
#define WEAPON_H_

#include "BulletInfo.h"
#include "Vector3.h"
#include <vector>
#include "GlobalDatas.h"
#include "Player.h"
#include "controls.h"
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
    void reloadWeapon();
    void updateBullets(double dt);
    void resetWeaponAmmo();
    void fireWeapon(Vector3 view, Vector3 position);
	void renderGO();
	Vector3 getBulletPosition();
    
    bool canFireBullet();

	CBulletInfo* FetchGO();

	double getWeaponReloadTime();
    int getCurrentHeldAmmo();
    int getCurrentLoadedBullet();
    int getMaxClipSize();
    int getMaxAmmoCapacity();
	int weaponDamage;

	AABB test;
	bool isFire;
	bool isWater;
	bool isAir;

	vector<CBulletInfo*> GetBulletList();

	void bulletCollision(double dt);

protected:
	std::vector<CBulletInfo *> m_goList;

private:
	int maxClipSize;
	int currentHeldAmmo;
	int maxAmmoCapacity;
	int currentLoadedAmmo;

	bool isReloading;

	double reloadTimer;
    double currentTime;
    double weaponReloadTime;
    double timeBetweenEachBullet;
	CBulletInfo* bullet;

	WEAPON_TYPE WeaponType;

};


#endif WEAPON_H_