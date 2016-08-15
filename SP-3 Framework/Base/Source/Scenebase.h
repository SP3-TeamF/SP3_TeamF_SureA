#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"
#include "Vector2.h"
#include "Player.h"
#include "GlobalDatas.h"
#include "Controls.h"
#include "SpriteAnimation.h"

class Scenebase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
    Scenebase();
    ~Scenebase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

    //Init functions

	//Update Functions
	
	//Render Function
	void RenderMesh(Mesh *mesh, bool enableLight);
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderTextOnScreen2(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void Render2DMesh(Mesh *mesh, bool enableLight, float size = 1.0f, float x = 0.0f, float y = 0.0f, float rotateAngle = 0);
    void RenderTileMap(TileMap* currentMap, float x_offSet = 0, float y_Offset = 0, float z_Offset = 0, float scrollSpeed = 1);
    void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size = 1.0f, float x = 0.0f, float y = 0.0f, float rotateAngle = 0);
    void RenderTile(Mesh *mesh, int tileID, const float size = 1.0f, const float x = 0.0f, const float y = 0.0f, const float z = 0);
  
protected:
    enum GEOMETRY_TYPE
    {
        GEO_TEXT,
        GEO_BACKGROUND,
        GEO_TILESHEET,
		GEO_TEST,
        NUM_GEOMETRY,
    };

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];

    float fps;
	bool bLightEnabled;
};

#endif SCENEBASE_H