#ifndef WEAPON_H_
#define WEAPON_H_

#include "BulletInfo.h"
#include "Vector3.h"
#include <vector>
#include "GlobalDatas.h"
#include "Player.h"
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
	void fireNet(Vector3 view, Vector3 position);
    void fireWeapon(Vector3 view, Vector3 position);
	void waterWeapon(Vector3 view, Vector3 position);
	void airWeapon(Vector3 view, Vector3 position);
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

	vector<CBulletInfo*> GetBulletList();
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

};


#endif WEAPON_H_