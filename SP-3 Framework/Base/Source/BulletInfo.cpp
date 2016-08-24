#include "BulletInfo.h"
#include "Player.h"

CBulletInfo::CBulletInfo(void)
: m_bStatus(false)
, speed(10)
, lifetime(5)
, nextPosition(0)
, damage(1)

{
}


CBulletInfo::~CBulletInfo(void)
{
}


// Initialise the CBulletInfo instance
void CBulletInfo::Init(const Vector3 position,
    const Vector3 direction,
    const float speed,
    const float lifetime,
	int bulletDamage,
	BULLET_TYPE bulletType
	)
{
    this->position = position;
    this->direction = direction;
    this->speed = speed;
    this->lifetime = lifetime;
    SetStatus(true);
	this->damage = bulletDamage;
	this->BulletType = bulletType;
}

//Set current Bullet type
void CBulletInfo::SetBulletType(BULLET_TYPE bulletType)
{
	this->BulletType = bulletType;
}

//Get current bullet type;
BULLET_TYPE CBulletInfo::GetBulletType()
{
	return this->BulletType;
}

// Set the status of this CBulletInfo instance
void CBulletInfo::SetStatus(const bool bStatus)
{
    this->m_bStatus = bStatus;
}


// Get the status of this CBulletInfo instance
bool CBulletInfo::GetStatus(void)
{
    return m_bStatus;
}

// Set the position of this CBulletInfo instance
void CBulletInfo::SetPosition(const Vector3 position)
{
	this->position = position;
}

// Get the position of this CBulletInfo instance
Vector3 CBulletInfo::GetPosition(void)
{
    return position;
}

// Set the direction of this CBulletInfo instance
void CBulletInfo::SetDirection(const Vector3 direction)
{
	this->direction = direction;
	if (this->direction.LengthSquared() > 0)
	{
		this->direction.Normalize();
	}
}

// Get the direction of this CBulletInfo instance
Vector3 CBulletInfo::GetDirection(void)
{
    return direction;
}

// Set the scale of this CBulletInfo instance
void CBulletInfo::SetScale(const Vector3 scale)
{
	this->scale = scale;
}

// Get the scale of this CBulletInfo instance
Vector3 CBulletInfo::GetScale(void)
{
	return scale;
}

// Set the speed of this CBulletInfo instance
void CBulletInfo::SetSpeed(const float speed)
{
    this->speed = speed;
}

// Get the speed of this CBulletInfo instance
float CBulletInfo::GetSpeed(void)
{
    return speed;
}

// Set the damage of this CBulletInfo instance
void CBulletInfo::SetDamage(const float damage)
{
	this->damage = damage;
}

// Get the damage of this CBulletInfo instance
float CBulletInfo::GetDamage(void)
{
	return damage;
}

// Set the lifetime of this CBulletInfo instance
void CBulletInfo::SetLifetime(const float lifetime)
{
    this->lifetime = lifetime;
}

// Get the lifetime of this CBulletInfo instance
float CBulletInfo::GetLifetime(void)
{
    return lifetime;
}

// Update this CBulletInfo instance
void CBulletInfo::Update(const double dt)
{
    // Check if the bullet is active
    if (GetStatus() == true)
    {
		
		float mapoffsetx= (m_TileMap->GetWorldWidth() + GlobalData.world_X_offset);
		float mapoffsety = (m_TileMap->GetWorldHeight() + GlobalData.world_Y_offset);

        SetPosition(GetPosition() + GetDirection() * GetSpeed() * dt);
        SetLifetime(GetLifetime() - dt);

        // Check if the lifetime is gone
        if (GetLifetime() <= 0)
        {
            SetStatus(false);
        }
    }
}

//bool CBulletInfo::bulletHitboxCheck(AABB* hitbox)
//{
//    Vector3 currentPos = GetPosition();
//    int offsetDivisor = GetSpeed() / 10;
//    Vector3 offset = (nextPosition - currentPos) * (1 / offsetDivisor);
//    for (int i = 0; i < offsetDivisor; ++i)
//    {
//        if (hitbox->PointToAABB(currentPos))
//        {
//            return true;
//            break;
//        }
//        currentPos += offset;
//    }
//    return false;
//}

