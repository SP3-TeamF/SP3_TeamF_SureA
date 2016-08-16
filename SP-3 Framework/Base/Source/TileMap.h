#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class TileMap
{
public:
	TileMap(void);
	~TileMap(void);

    void Init(const int screenWidth, const int screenHeight,
              const int world_Width, const int world_Height,
			  const int theTileSize = 25
              );

	bool LoadMap(const string mapName);
	bool SaveMap(const string mapName);
	bool WriteMap(const string mapName, vector<vector<int>> mapVariables, int mapHeight, int mapWidth);

	//getter
    int GetTileSize(void);

	//World get functions
	int GetWorldWidth(void);
	int GetWorldHeight(void);
	int GetNumWorldTile_Width(void);
	int GetNumWorldTile_Height(void);

	//Screen get functions
	int GetScreenWidth(void);
	int GetScreenHeight(void);
	int GetNumScreenTile_Width(void);
	int GetNumScreenTile_Height(void);
	int GetTileType(float xPosition, float yPosition);

	//Setter
	void SetTile(int typeNo, int xPos, int yPos);

    vector<vector<int> > world_Tile_Map;

private:
	//Screen Variables
	int screen_Width;
	int screen_Height;

	int numTile_Screen_Width;
	int numTile_Screen_Height;

    //World Variables
    int world_Width;
    int world_Height;

    int numTile_World_Width;
    int numTile_World_Height;

	int tileSize;

	bool LoadFile(const string mapName);
};

#endif TILEMAP_H_