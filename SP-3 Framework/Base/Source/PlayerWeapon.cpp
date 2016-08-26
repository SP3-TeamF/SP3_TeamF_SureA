#include "PlayerWeapon.h"
#include "GlobalDatas.h"

PlayerWeapon::PlayerWeapon(){

}

PlayerWeapon::~PlayerWeapon(){

}

void PlayerWeapon::Update(double dt){

}

void PlayerWeapon::fireWeapon(Vector3 view, Vector3 position)
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