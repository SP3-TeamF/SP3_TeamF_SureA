#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "BulletInfo.h"
#include "Vector3.h"
#include <vector>
using std::vector;

class CBulletFactory{
public:
	CBulletFactory();
	~CBulletFactory();

	void Update(double dt);
	CBulletInfo* FetchGO();

	vector<CBulletInfo*> GetBulletList();

protected:
	std::vector<CBulletInfo*> m_goList;

private:

};



#endif BULLET_FACTORY_H