#include "weapon.h"

weapon::weapon()
{
    maxClipSize = 10;
    currentHeldAmmo = 10;
    maxAmmoCapacity = 5;
    currentLoadedAmmo = 5;
    timeBetweenEachBullet = 0.1;
    currentTime = 0;
    isReloading = false;
    weaponReloadTime = 0;
}

weapon::~weapon()
{
}

weapon::weapon(float timeBetweenEachBullet, int maxClipSize, int maxAmmoCapacity, double reloadTime, int weaponDamage)
{
    this->maxClipSize = maxClipSize;
    this->maxAmmoCapacity = maxAmmoCapacity;
    this->timeBetweenEachBullet = timeBetweenEachBullet;
    this->currentLoadedAmmo = maxClipSize;
    this->currentHeldAmmo = maxAmmoCapacity;
    this->currentTime = 0;
    this->isReloading = false;
    this->weaponReloadTime = reloadTime;
	this->weaponDamage = weaponDamage;
}

void weapon::fireWeapon(Vector3 view, Vector3 position)
{
}

void weapon::Update(double dt)
{
	currentTime += dt;
}

bool weapon::canFireBullet()
{
    if (currentTime > timeBetweenEachBullet && currentLoadedAmmo > 0)
    {
        return true;
    }

    return false;
}

void weapon::reloadWeapon()
{
    if (currentHeldAmmo > 0 && currentLoadedAmmo < maxClipSize)
    {
        if (currentHeldAmmo > maxClipSize - currentLoadedAmmo)
        {
            if (currentLoadedAmmo > 0)
            {
                currentHeldAmmo -= maxClipSize - currentLoadedAmmo;
                currentLoadedAmmo = maxClipSize;
            }
            else
            {
                currentHeldAmmo -= maxClipSize;
                currentLoadedAmmo = maxClipSize;
            }
        }
        else
        {
            currentLoadedAmmo = currentHeldAmmo;
            currentHeldAmmo = 0;
        }
    }
}

double weapon::getWeaponReloadTime()
{
	return weaponReloadTime;
}

int weapon::getCurrentHeldAmmo()
{
    return currentHeldAmmo;
}

int weapon::getCurrentLoadedBullet()
{
    return currentLoadedAmmo;
}

int weapon::getMaxClipSize()
{
    return maxClipSize;
}

int weapon::getMaxAmmoCapacity()
{
    return maxAmmoCapacity;
}

void weapon::resetWeaponAmmo()
{
    this->currentLoadedAmmo = maxClipSize;
    this->currentHeldAmmo = maxAmmoCapacity;
}