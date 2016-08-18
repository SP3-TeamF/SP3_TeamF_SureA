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

	for (std::vector<CBulletInfo *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		CBulletInfo *bullet = (CBulletInfo *)*it;
		bullet->SetDirection(Vector3(1, 0, 0));
		bullet->SetPosition(Vector3(300, 200, 0));
		bullet->SetSpeed(5.f);
	}

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
	bullet->SetStatus(false);
	reloadTimer = 0;

}

void weapon::fireWeapon(Vector3 view, Vector3 position)
{
	if (view != 0 && canFireBullet()){
		view.Normalized();
		CBulletInfo* bullet = FetchGO();
		bullet->SetStatus(true);
		currentLoadedAmmo--;
		currentTime = 0;
		reloadTimer = 0;
		isReloading = true;
		switch (WeaponType)
		{
			case WT_NET:
			{
						   bullet->Init(position, view, 500, 3, 10);
						   bullet->SetBulletType(BT_NET);
						   break;
			}
			case WT_FIRE:
			{
							bullet->Init(position, view, 150, 6, 20);
							bullet->SetBulletType(BT_FIRE);
							break;
			}
			case WT_WATER:
			{
							 bullet->Init(position, view, 1000, 6, 20);
							 bullet->SetBulletType(BT_WATER);
							 break;
			}
			case WT_AIR:
			{
						   bullet->Init(position, view, 100, 3, 10);
						   bullet->SetBulletType(BT_AIR);
						   break;
			}
		}
	}
}


void weapon::Update(double dt)
{
	if ((controls.GetIsControllerTriggerPressed(CONTROLLER_1, R_TRIGGER)) || (controls.isKeyboardButtonPressed(KEYBOARD_SPACE))){
			fireWeapon((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition());
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_UP) || controls.isKeyboardButtonPressed(KEYBOARD_1))){
		WeaponType = WT_NET;
		std::cout << "Net" << std::endl;
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_DOWN) || controls.isKeyboardButtonPressed(KEYBOARD_2))){
		WeaponType = WT_WATER;
		std::cout << "Water" << std::endl;
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_RIGHT) || controls.isKeyboardButtonPressed(KEYBOARD_3))){
		WeaponType = WT_AIR;
		std::cout << "Air" << std::endl;
	}
	if ((controls.isControllerButtonPressed(CONTROLLER_1, CONTROLLER_DPAD_LEFT) || controls.isKeyboardButtonPressed(KEYBOARD_4))){
		WeaponType = WT_FIRE;
		std::cout << "Fire" << std::endl;
	}
	if (controls.isKeyboardButtonPressed(KEYBOARD_SPACE))
	{
		fireWeapon(Vector3(1, 0, 0), player->Get_cPosition());
	}
	//cout << isReloading << std::endl;

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
	bulletCollision(dt);

}

void weapon::bulletCollision(double dt)
{
	Vector3 updatedPos = bullet->GetPosition() + (bullet->GetDirection() * bullet->GetSpeed()) * dt;
	updatedPos.x += m_TileMap->GetTileSize() * 0.5 + GlobalData.world_X_offset;
	updatedPos.y += m_TileMap->GetTileSize() * 0.5 + GlobalData.world_Y_offset;

	int currentTile = 237;

	int tilePosX = updatedPos.x / m_TileMap->GetTileSize();
	int tilePosY = updatedPos.y / m_TileMap->GetTileSize();

	//for (std::vector<CBulletInfo *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	//{
	//	CBulletInfo *bullet = (CBulletInfo *)*it;
	//	if (bullet->GetStatus() == true)
	//	{
	//		if (m_TileMap->GetTileType(tilePosX, tilePosY) != 237)
	//		{
	//			//bullet->bulletHitboxCheck();
	//		}
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
		//test.SetCircle(Vector3(bullet->GetPosition().x, bullet->GetPosition().y, 0), 5);

		m_goList.push_back(bullet);
	}
	
	CBulletInfo* bullet = m_goList.back();
	return bullet;
}

vector<CBulletInfo*> weapon::GetBulletList()
{
	return m_goList;
}

