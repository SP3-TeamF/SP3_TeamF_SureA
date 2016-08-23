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
	CBulletInfo* enemyBullet = FetchEnemyBullet();

	for (std::vector<CBulletInfo *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		CBulletInfo *bullet = (CBulletInfo *)*it;
		bullet->SetDirection(Vector3(1, 0, 0));
		bullet->SetPosition(Vector3(300, 200, 0));
		bullet->SetSpeed(5.f);
	}

	for (std::vector<CBulletInfo *>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
	{
		CBulletInfo *enemyBullet = (CBulletInfo *)*it2;
		enemyBullet->SetDirection(Vector3(1, 0, 0));
		enemyBullet->SetPosition(Vector3(300, 200, 0));
		enemyBullet->SetSpeed(3.f);
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
	enemyBullet->SetStatus(false);
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
						   bullet->Init(position, view, 100, 5, 1);
						   bullet->SetBulletType(BT_NET);
						   bullet->SetScale(Vector3(3,3,0));
						   bullet->SetLifetime(5);
						   break;
			}
			case WT_FIRE:
			{
							bullet->Init(position, view, 150, 6, 20);
							bullet->SetBulletType(BT_FIRE);
							bullet->SetScale(Vector3(1,1,0));
							break;
			}
			case WT_WATER:
			{
							 bullet->Init(position, view, 1000, 6, 20);
							 bullet->SetBulletType(BT_WATER);
							 bullet->SetScale(Vector3(1, 1, 0));
							 break;
			}
			case WT_AIR:
			{
						   bullet->Init(position, view, 500, 3, 10);
						   bullet->SetBulletType(BT_AIR);
						   bullet->SetScale(Vector3(1, 1, 0));
						   break;
			}
		}
	}
}

void weapon::fireEnemyWeapon(Vector3 view, Vector3 position){
	CBulletInfo* enemyBullet = FetchEnemyBullet();
	enemyBullet->SetStatus(true);
	enemyBullet->Init(position, view, 200, 10, 1);
	enemyBullet->SetBulletType(BT_ENEMY);
	enemyBullet->SetScale(Vector3(1, 1, 0));


	
}


void weapon::Update(double dt)
{
	if (GlobalData.isControllerConnected)
	{
		if ((controls.GetIsControllerTriggerPressed(CONTROLLER_1, R_TRIGGER)))
		{
			fireEnemyWeapon((controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK)), player->Get_cPosition()+Vector3(GlobalData.world_X_offset,GlobalData.world_Y_offset,0));
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
	
	for (auto bulletIt : m_goList)
	{
		currentTime += dt;
		if (bulletIt->GetStatus())
		{
			bulletIt->Update(dt);
		}
	}
	for (auto enemyBulletIt : enemyList)
	{
		currentTime += dt;
		if (enemyBulletIt->GetStatus())
		{
			enemyBulletIt->Update(dt);
		}
	}
	bulletCollision(dt);
}

void weapon::bulletCollision(double dt)
{
	Vector3 updatedPos = bullet->GetPosition() + (bullet->GetDirection() * bullet->GetSpeed()) * dt;
	updatedPos.x += m_TileMap->GetTileSize() * 0.5;
	updatedPos.y += m_TileMap->GetTileSize() * 0.5;

	int currentTile = 237;

	int tilePosX = updatedPos.x / m_TileMap->GetTileSize();
	int tilePosY = updatedPos.y / m_TileMap->GetTileSize();

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

CBulletInfo* weapon::FetchEnemyBullet(){

	for (std::vector<CBulletInfo *>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
	{
		CBulletInfo *enemyBullet = (CBulletInfo *)*it2;
		if (enemyBullet->GetStatus() == false)
		{
			enemyBullet->SetStatus(true);
			return enemyBullet;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		enemyBullet = new CBulletInfo();
		enemyList.push_back(enemyBullet);
	}

	CBulletInfo* enemyBullet = enemyList.back();
	return enemyBullet;
}

vector<CBulletInfo*> weapon::GetEnemyBulletList()
{
	return enemyList;
}
