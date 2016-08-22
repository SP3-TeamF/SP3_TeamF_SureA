#include "TileMap.h"
#include <iostream>
using std::cout;
using std::endl;

TileMap::TileMap(void)
    : screen_Width(0)
    , screen_Height(0)
    , numTile_Screen_Width(0)
    , numTile_Screen_Height(0)
    , world_Width(0)
    , world_Height(0)
    , numTile_World_Width(0)
    , numTile_World_Height(0)
    , tileSize(0)
{
    world_Tile_Map.clear();
}

TileMap::~TileMap(void)
{
     world_Tile_Map.clear();
}

void TileMap::Init(const int screenWidth, const int screenHeight,
                   const int worldWidth, const int worldHeight,
                   const int theTileSize
                   )
{
    this->screen_Width = screenWidth;
    this->screen_Height = screenHeight;
    
    this->numTile_Screen_Width = (int)screenWidth / theTileSize;
    this->numTile_Screen_Height = (int)screenHeight / theTileSize;
    
    this->world_Width = worldWidth;
    this->world_Height = worldHeight;
    
    this->tileSize = theTileSize;

    numTile_World_Width = (int)(world_Width / theTileSize);
    numTile_World_Height = (int)(world_Height / theTileSize);

    world_Tile_Map.resize(numTile_World_Height);

    for (int i = 0; i < numTile_World_Height; ++i)
    {
        world_Tile_Map[i].resize(numTile_World_Width);
    }
}

bool TileMap::LoadMap(const string mapName)
{
	if (LoadFile(mapName) == true)
	{
		printf("Map (%s) has been successfully loaded!\n", mapName.c_str());
		return true;
	}

	return false;
}

bool TileMap::LoadFile(const string mapName)
{
	int currentLine = 0;
	int maxNumColumns = 0;

	ifstream file(mapName.c_str());

    if (file.is_open())
    {
        while (file.good())
        {
            string currentText = "";
            getline(file, currentText);

            if (currentLine > numTile_World_Height)
            { 
                break;
            }

            if (currentLine == 0)
            {
                // This is the first line of the map data file
                string token;
                istringstream iss(currentText);
                while (getline(iss, token, ','))
                {
                    // Count the number of columns
                    ++maxNumColumns;
                }
                if (maxNumColumns != numTile_World_Width)
                {
                    cout << "Fail to load: " << mapName << endl;
                    return false;
                }

                ++currentLine;
            }

            int currentColum = 0;

            string token;
            istringstream iss(currentText);
            while (getline(iss, token, ',') && (currentColum < numTile_World_Width))
            {
                world_Tile_Map[numTile_World_Height - currentLine][currentColum++] = atoi(token.c_str());
            }

            currentLine++;
        }
        return true;
    }
	else
	{
        WriteMap(mapName, world_Tile_Map, numTile_World_Width, numTile_World_Height);
	}


	return true;
}

//Screen Getters
int TileMap::GetNumScreenTile_Width(void)
{
    return numTile_Screen_Width;
}

int TileMap::GetNumScreenTile_Height(void)
{
    return numTile_Screen_Height;
}

int TileMap::GetScreenWidth(void)
{
	return screen_Width;
}

int TileMap::GetScreenHeight(void)
{
	return screen_Height;
}

//World Getters
int TileMap::GetNumWorldTile_Width(void)
{
    return numTile_World_Width;
}

int TileMap::GetNumWorldTile_Height(void)
{
    return numTile_World_Height;
}

int TileMap::GetWorldWidth(void)
{
	return this->world_Width;
}

int TileMap::GetWorldHeight(void)
{
	return this->world_Height;
}

//Others
int TileMap::GetTileSize(void)
{
    if (this)
    {
        return tileSize;
    }
}

int TileMap::GetTileType(float xPosition, float yPosition)
{
    if (this)
    {
        if (xPosition >= 0 &&
            xPosition < GetNumWorldTile_Width() &&
            yPosition >= 0 &&
            yPosition < GetNumWorldTile_Height()
            )
        {
            return world_Tile_Map[yPosition][xPosition];
        }
    }
	return -1;
}

bool TileMap::WriteMap(const string mapName, vector<vector<int>> mapVariables, int mapWidth, int mapHeight)
{
	ofstream newFile;
	newFile.open(mapName);

	for (int y = 0; y < mapHeight; ++y)
	{
		for (int x = 0; x < mapWidth; ++x)
		{
			newFile << 0 << ",";
			if (x == mapWidth - 1)
			{
				newFile << endl;
			}
		}
	}

	newFile.close();

	return true;
}

bool TileMap::SaveMap(const string mapName)
{
    ofstream newFile;
    newFile.open(mapName);

    for (int y = numTile_World_Height - 1; y >=0 ; --y)
    {
        for (int x = 0; x < numTile_World_Width; ++x)
        {
            newFile << GetTileType(x, y) << ",";

            if (x == numTile_World_Width - 1)
            {
                newFile << endl;
            }
        }
    }

    newFile.close();

	cout << "Map " << mapName << " has been successfully EXPLODED!\n" ;
	return true;
}

void TileMap::SetTile(int typeNo, int xPos, int yPos)
{
	if (xPos >= 0 &&
		xPos < GetNumWorldTile_Width() &&
		yPos >= 0 &&
		yPos < GetNumWorldTile_Height()
		)
	{
		world_Tile_Map[yPos][xPos] = typeNo;
	}
}