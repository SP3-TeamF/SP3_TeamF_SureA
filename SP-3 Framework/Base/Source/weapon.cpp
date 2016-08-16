#include "weapon.h"

weapon::weapon()
{
    maxClipSize = 10;
    currentHeldAmmo = 1;
    maxAmmoCapacity = 5;
    currentLoadedAmmo = 1;
    timeBetweenEachBullet = 1.f;
    currentTime = 0;
	reloadTimer = 0;
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
	reloadTimer = 0;

}

void weapon::fireWeapon(Vector3 view, Vector3 position)
{
	if (view != 0 && canFireBullet()){
		view.Normalized();
		CBulletInfo* bullet = FetchGO();
		bullet->SetStatus(true);
		bullet->Init(position, view, 500, 3, 10);
		currentLoadedAmmo--;
		currentTime = 0;
		reloadTimer = 0;
		isReloading = true;
	}

}

void weapon::waterWeapon(Vector3 view, Vector3 position){
	if (view != 0 && canFireBullet()){
		view.Normalized();
		CBulletInfo* bullet = FetchGO();
		bullet->SetStatus(true);
		bullet->Init(position, view, 150, 6, 20);
		currentLoadedAmmo--;
		currentTime = 0;
		reloadTimer = 0;
		isReloading = true;
	}
}

void weapon::airWeapon(Vector3 view, Vector3 position){
	if (view != 0 && canFireBullet()){
		view.Normalized();
		CBulletInfo* bullet = FetchGO();
		bullet->SetStatus(true);
		bullet->Init(position, view, 1000, 6, 20);
		currentLoadedAmmo--;
		currentTime = 0;
		reloadTimer = 0;
		isReloading = true;
	}
}

void weapon::fireNet(Vector3 view, Vector3 position)
{
	if (view != 0 && canFireBullet()){

		view.Normalized();
		CBulletInfo* bullet = FetchGO();
		bullet->SetStatus(true);
		bullet->Init(position, view, 100, 3, 10);
		currentLoadedAmmo--;
		currentTime = 0;
		reloadTimer = 0;
		isReloading = true;
	}
}

void weapon::Update(double dt)
{
	cout << isReloading << std::endl;

	if (isReloading == true && reloadTimer <=1){
		reloadTimer += dt;
		currentLoadedAmmo = 1;
	}
	else{
		reloadTimer = 0;
		isReloading = false;
	}
	
	for (auto bulletIt : m_goList)
	{
		currentTime += dt;
		
		
			if (bulletIt->GetSpeed())
			{
				bulletIt->Update(dt);
			}
		
	}
}

bool weapon::canFireBullet()
{
    if (currentTime > timeBetweenEachBullet && currentLoadedAmmo > 0 && isReloading == false)
    {
        return true;
    }

    return false;
}

void weapon::reloadWeapon()
{
	if (currentHeldAmmo > 0 && currentLoadedAmmo < maxClipSize)
	{
		currentLoadedAmmo = 1;
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

