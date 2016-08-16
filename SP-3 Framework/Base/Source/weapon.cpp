#include "weapon.h"

weapon::weapon()
{
    maxClipSize = 10;
    currentHeldAmmo = 10;
    maxAmmoCapacity = 5;
    currentLoadedAmmo = 5;
    timeBetweenEachBullet = 1.f;
    currentTime = 0;
    isReloading = false;
    weaponReloadTime = 0;
	weaponDamage = 0;
	CBulletInfo* bullet = FetchGO();


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
	bullet->SetStatus(false);


}

void weapon::fireWeapon(Vector3 view, Vector3 position)
{
	if (view != 0){
		
		view.Normalized();
		CBulletInfo* bullet = FetchGO();
		bullet->SetStatus(true);
		bullet->Init(position, view, 1000, 3, 10);
	}
	//::cout << bullet->GetPosition() << std::endl;

}

void weapon::fireNet(Vector3 view, Vector3 position)
{

}

void weapon::Update(double dt)
{
	currentTime += dt;
	for (auto bulletIt : m_goList)
	{
		if (canFireBullet()){
			if (bulletIt->GetSpeed())
			{
				bulletIt->Update(dt);
			}
		}
	}
	//std::cout << bullet->GetDirection() << "       " << bullet->GetSpeed() << std::endl;
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



CBulletInfo* weapon::FetchGO()
{
	for (std::vector<CBulletInfo *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		CBulletInfo *bullet = (CBulletInfo *)*it;
		if (bullet->GetStatus() == false)
		{
			bullet->SetStatus(true);
			return bullet;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		bullet = new CBulletInfo();
		m_goList.push_back(bullet);
	}
	CBulletInfo* bullet = m_goList.back();
	return bullet;
}

vector<CBulletInfo*> weapon::GetBulletList()
{
	return m_goList;
}

