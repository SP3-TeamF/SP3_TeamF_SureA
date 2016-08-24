#include "weapon.h"
#include "player.h"
#include "BulletFactory.h"
#include "GlobalDatas.h"

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
	WeaponType = WT_NET;

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
	reloadTimer = 0;

}

void weapon::fireWeapon(Vector3 view, Vector3 position)
{
	if (view != 0 && canFireBullet()){
		view.Normalized();
		CBulletInfo* bullet = GlobalData.bulletFactory->FetchGO();
		bullet->SetStatus(true);
		currentLoadedAmmo--;
		currentTime = 0;
		reloadTimer = 0;
		isReloading = true;
		switch (WeaponType)
		{
		case WT_NET:
		{
			if (Inventory.netbullet > 0)
			{
				bullet->Init(position, view, 100, 5, 1);
				bullet->SetBulletType(BT_NET);
				bullet->SetScale(Vector3(3, 3, 0));
				bullet->SetLifetime(5);
				Inventory.netbullet--;
				break;
			}
		}
		case WT_FIRE:
		{
			if (Inventory.firebullet > 0)
			{
				bullet->Init(position, view, 150, 6, 10);
				bullet->SetBulletType(BT_FIRE);
				bullet->SetScale(Vector3(1, 1, 0));
				Inventory.firebullet--;
				break;
			}
			else break;
		}
		case WT_WATER:
		{
			if (Inventory.waterbullet > 0)
			{
				bullet->Init(position, view, 75, 6, 20);
				bullet->SetBulletType(BT_WATER);
				bullet->SetScale(Vector3(1, 1, 0));
				Inventory.waterbullet--;
				break;
			}
			else break;
		}
		case WT_AIR:
		{
			if (Inventory.airbullet > 0)
			{
				bullet->Init(position, view, 350, 2, 5);
				bullet->SetBulletType(BT_AIR);
				bullet->SetScale(Vector3(1, 1, 0));
				Inventory.airbullet--;
				break;
			}
			else break;
		}
		}
	}
}

void weapon::Update(double dt)
{
	if (GlobalData.isControllerConnected)
	{
		if ((controls.GetIsControllerTriggerPressed(CONTROLLER_1, R_TRIGGER)))
		{
			fireWeapon((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition()+Vector3(GlobalData.world_X_offset,GlobalData.world_Y_offset,0));
		}
		if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_UP))){
			WeaponType = WT_NET;
		}
		if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_DOWN))){
			WeaponType = WT_WATER;
		}
		if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_RIGHT))){
			WeaponType = WT_AIR;
		}
		if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_LEFT))){
			WeaponType = WT_FIRE;
		}
	}
	else
	{
		if ( controls.isKeyboardButtonPressed(KEYBOARD_1)){
			WeaponType = WT_NET;
		}
		if (controls.isKeyboardButtonPressed(KEYBOARD_2)){
			WeaponType = WT_WATER;
		}
		if (controls.isKeyboardButtonPressed(KEYBOARD_3)){
			WeaponType = WT_AIR;
		}
		if (controls.isKeyboardButtonPressed(KEYBOARD_4)){
			WeaponType = WT_FIRE;
		}
		if (controls.isKeyboardButtonPressed(KEYBOARD_SPACE))
		{
			fireWeapon(Vector3(1, 0, 0), player->Get_cPosition());
		}
	}

	if (isReloading == true && reloadTimer <=1){
		reloadTimer += dt;
		currentLoadedAmmo = 1;
	}
	else{
		reloadTimer = 0;
		isReloading = false;
	}
	
	currentTime += dt;
	BulletFactory->Update(dt);
	//for (auto bulletIt : m_goList)
	//{
	//	currentTime += dt;
	//	if (bulletIt->GetStatus())
	//	{
	//		bulletIt->Update(dt);
	//	}
	//}
	//for (auto enemyBulletIt : enemyList)
	//{
	//	if (enemyBulletIt->GetStatus())
	//	{
	//		enemyBulletIt->Update(dt);
	//	}
	//}
	
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

