#pragma once

#include "vector3.h"
#include "AABB.h"
#include "GlobalDatas.h"

enum BULLET_TYPE{
	BT_NET = 0,
	BT_FIRE,
	BT_WATER,
	BT_AIR,
	BT_NETSPREAD,
	BT_ENEMY
};

class CBulletInfo
{
public:
	CBulletInfo(void);
	virtual ~CBulletInfo(void);
protected:
	// Indicate the status of this bullet
	bool m_bStatus;
	// The position of the bullet
	Vector3 position;
	// The direction of the bullet
	Vector3 direction;
	// The speed of the bullet
	float speed;
	// The lifetime of the bullet
	float lifetime;
	// The Damage of the bullet
	float damage;

	// The scale of the bullet
	Vector3 scale;
	BULLET_TYPE BulletType;

    Vector3 nextPosition;
public:
	// Initialise the CBulletInfo instance
	void Init(const Vector3 position, const Vector3 direction, const float speed, const float lifetime, int bulletDamage, BULLET_TYPE bullType = BT_NET);
	
	//Set current Bullet type
	void SetBulletType(BULLET_TYPE bulletType);

	//Get current bullet type;
	BULLET_TYPE GetBulletType();

	// Set the status of this CBulletInfo instance
	void SetStatus(const bool bStatus);
	// Get the status of this CBulletInfo instance
	bool GetStatus(void);

	//Set the scale of the CBulletInfo instance
	void SetScale(const Vector3 scale);

	//Get the scale of the CBulletInfo instance
	Vector3 GetScale(void);
	
	// Set the position of this CBulletInfo instance
	void SetPosition(const Vector3 position);
	// Get the position of this CBulletInfo instance
	Vector3 GetPosition(void);
	
	// Set the direction of this CBulletInfo instance
	void SetDirection(const Vector3 direction);
	// Get the direction of this CBulletInfo instance
	Vector3 GetDirection(void);
	
	// Set the speed of this CBulletInfo instance
	void SetSpeed(const float speed);
	// Get the speed of this CBulletInfo instance
	float GetSpeed(void);

	// Set the speed of this CBulletInfo instance
	void SetDamage(const float damage);
	// Get the speed of this CBulletInfo instance
	float GetDamage(void);
	
	// Set the lifetime of this CBulletInfo instance
	void SetLifetime(const float lifetime);
	// Get the lifetime of this CBulletInfo instance
	float GetLifetime(void);

	// Update this CBulletInfo instance
	void Update(const double dt);

    bool bulletHitboxCheck(AABB* hitbox);

};

