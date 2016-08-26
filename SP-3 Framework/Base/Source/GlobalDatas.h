#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H
#include "BulletInfo.h"
#include "BulletFactory.h"
#include "TileMap.h"
#include <vector>
#include <irrKlang.h>
using namespace irrklang;
using std::vector;

#define m_TileMap GlobalDatas::GetInstance().tileMap
#define GlobalData GlobalDatas::GetInstance()
#define BulletFactory GlobalDatas::GetInstance().bulletFactory

class GlobalDatas
{
public:

	GlobalDatas(){};
	~GlobalDatas(){
        if (theSoundEngine)
        {
            theSoundEngine->drop();
        }
        if (tileMap)
        {
            delete tileMap;
        }
        bulletFactory;
    };
   
	static GlobalDatas& GetInstance()
	{
		static GlobalDatas globalV;
		return globalV;
	}

    //irrKlang stuff
    ISoundEngine* theSoundEngine = createIrrKlangDevice();

    //Tile Maping functions
    TileMap* tileMap = new TileMap();
	CBulletFactory* bulletFactory = new CBulletFactory();


	//World Offsets
	float world_X_offset = 0.f;
	float world_Y_offset = 0.f;

	bool isControllerConnected = false;

	bool quitGame = false;
};

#endif GLOBAL_VARIABLE_H