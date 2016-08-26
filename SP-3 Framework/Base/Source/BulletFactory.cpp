#include "BulletFactory.h"

CBulletFactory::CBulletFactory()
{
}

CBulletFactory::~CBulletFactory(){

}

CBulletInfo* CBulletFactory::FetchGO()
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
		CBulletInfo * bullet = new CBulletInfo();
		m_goList.push_back(bullet);
	}

	CBulletInfo* bullet = m_goList.back();
	return bullet;
}

vector<CBulletInfo*> CBulletFactory::GetBulletList()
{
	return m_goList;
}

void CBulletFactory::Update(double dt){
	for (auto bulletIt : m_goList)
	{
		//currentTime += dt;
		if (bulletIt->GetStatus())
		{
			bulletIt->Update(dt);
		}
	}
}