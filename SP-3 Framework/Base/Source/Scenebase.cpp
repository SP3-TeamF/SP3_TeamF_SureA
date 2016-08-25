#include "Scenebase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

static const float SKYBOXSIZE = 1000.f;

Scenebase::Scenebase():m_cMinimap(NULL)
{
}

Scenebase::~Scenebase()
{
	if (m_cMinimap)
	{
		delete m_cMinimap;
		m_cMinimap = NULL;
	}
    Exit();
}

//Init Functions
void Scenebase::Init()
{
	// Blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Enable depth test
	//	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//	glDepthFunc(GL_LESS); 

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");


	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}


	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Harrington.tga");

	meshList[GEO_TEXT1] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT1]->textureID = LoadTGA("Image//Harrington1.tga");

    meshList[GEO_BACKGROUND] = MeshBuilder::Generate2DMesh("GEO_BACKGROUND", Color(1, 1, 1), 0.0f, 0.0f, 800.0f, 600.0f);
    meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Night_Sky.tga");
	
	meshList[GEO_TILESHEET] = MeshBuilder::GenerateTileMesh("TileSheet", 21, 23);
	meshList[GEO_TILESHEET]->textureID = LoadTGA("Image//TileSheet1.tga");

	meshList[GEO_SCROLL] = MeshBuilder::Generate2DMesh("GEO_SCROLL", Color(1, 1, 1), 0.0f, 0.0f, 800.0f, 600.0f);
	meshList[GEO_SCROLL]->textureID = LoadTGA("Image//tutScroll.tga");

    WispImagesInit();
    HUD_ImagesInit();
    EnemyImagesInit();
    PlayerImagesInit();
    BulletImagesInit();
	
	m_cMinimap = new CMinimap();
	m_cMinimap->SetBackground(MeshBuilder::GenerateSquareMinimap("MINIMAP", Color(1, 1, 1), 1.f));
	m_cMinimap->GetBackground()->textureID = LoadTGA("Image//Map1.tga");

	m_cMinimap->SetBorder(MeshBuilder::GenerateQuad("MINIMAPBORDER", Color(1, 1, 0), 1.f));
	m_cMinimap->SetAvatar(MeshBuilder::GenerateMinimapAvatar("MINIMAPAVATAR", Color(1, 0, 0), 0.5f));

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;

    glDisable(GL_CULL_FACE);
}

void Scenebase::EnemyImagesInit()
{
    meshList[GEO_AIRMONDOWN] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_AIRMONDOWN]->textureID = LoadTGA("Image//airmonDOWN.tga");
    SpriteAnimation *sa15 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONDOWN]);
    if (sa15)
    {
        sa15->m_anim = new Animation();
        sa15->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
    meshList[GEO_AIRMONUP] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_AIRMONUP]->textureID = LoadTGA("Image//airmonUP.tga");
    SpriteAnimation *sa16 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONUP]);
    if (sa16)
    {
        sa16->m_anim = new Animation();
        sa16->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_AIRMONLEFT] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_AIRMONLEFT]->textureID = LoadTGA("Image//airmonLEFT.tga");
    SpriteAnimation *sa17 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONLEFT]);
    if (sa17)
    {
        sa17->m_anim = new Animation();
        sa17->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
    meshList[GEO_AIRMONRIGHT] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_AIRMONRIGHT]->textureID = LoadTGA("Image//airmonRIGHT.tga");
    SpriteAnimation *sa18 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONRIGHT]);
    if (sa18)
    {
        sa18->m_anim = new Animation();
        sa18->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_FIREMONDOWN] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_FIREMONDOWN]->textureID = LoadTGA("Image//firemonDOWN.tga");
    SpriteAnimation *sa19 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONDOWN]);
    if (sa19)
    {
        sa19->m_anim = new Animation();
        sa19->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
    meshList[GEO_FIREMONUP] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_FIREMONUP]->textureID = LoadTGA("Image//firemonUP.tga");
    SpriteAnimation *sa20 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONUP]);
    if (sa20)
    {
        sa20->m_anim = new Animation();
        sa20->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_FIREMONLEFT] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_FIREMONLEFT]->textureID = LoadTGA("Image//firemonLEFT.tga");
    SpriteAnimation *sa21 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONLEFT]);
    if (sa21)
    {
        sa21->m_anim = new Animation();
        sa21->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
    meshList[GEO_FIREMONRIGHT] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_FIREMONRIGHT]->textureID = LoadTGA("Image//firemonRIGHT.tga");
    SpriteAnimation *sa22 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONRIGHT]);
    if (sa22)
    {
        sa22->m_anim = new Animation();
        sa22->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }


    meshList[GEO_WATERMONDOWN] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_WATERMONDOWN]->textureID = LoadTGA("Image//firemonDOWN.tga");
    SpriteAnimation *sa23 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONDOWN]);
    if (sa23)
    {
        sa23->m_anim = new Animation();
        sa23->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
    meshList[GEO_WATERMONUP] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_WATERMONUP]->textureID = LoadTGA("Image//firemonUP.tga");
    SpriteAnimation *sa24 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONUP]);
    if (sa24)
    {
        sa24->m_anim = new Animation();
        sa24->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_WATERMONLEFT] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_WATERMONLEFT]->textureID = LoadTGA("Image//firemonLEFT.tga");
    SpriteAnimation *sa25 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONLEFT]);
    if (sa25)
    {
        sa25->m_anim = new Animation();
        sa25->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
    meshList[GEO_WATERMONRIGHT] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_WATERMONRIGHT]->textureID = LoadTGA("Image//firemonRIGHT.tga");
    SpriteAnimation *sa26 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONRIGHT]);
    if (sa26)
    {
        sa26->m_anim = new Animation();
        sa26->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

}

void Scenebase::PlayerImagesInit()
{
    meshList[GEO_MCDOWN] = MeshBuilder::GenerateSpriteAnimation("down", 1, 3);
    meshList[GEO_MCDOWN]->textureID = LoadTGA("Image//PLAYER IMAGES//MCdown.tga");
    SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWN]);
    if (sa1)
    {
        sa1->m_anim = new Animation();
        sa1->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCUP] = MeshBuilder::GenerateSpriteAnimation("up", 1, 3);
    meshList[GEO_MCUP]->textureID = LoadTGA("Image//PLAYER IMAGES//MCup.tga");
    SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCUP]);
    if (sa2)
    {
        sa2->m_anim = new Animation();
        sa2->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCLEFT] = MeshBuilder::GenerateSpriteAnimation("left", 1, 3);
    meshList[GEO_MCLEFT]->textureID = LoadTGA("Image//PLAYER IMAGES//MCleft.tga");
    SpriteAnimation *sa3 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCLEFT]);
    if (sa3)
    {
        sa3->m_anim = new Animation();
        sa3->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCRIGHT] = MeshBuilder::GenerateSpriteAnimation("right", 1, 3);
    meshList[GEO_MCRIGHT]->textureID = LoadTGA("Image//PLAYER IMAGES//MCright.tga");
    SpriteAnimation *sa4 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCRIGHT]);
    if (sa4)
    {
        sa4->m_anim = new Animation();
        sa4->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCTOPLEFT] = MeshBuilder::GenerateSpriteAnimation("topleft", 1, 3);
    meshList[GEO_MCTOPLEFT]->textureID = LoadTGA("Image//PLAYER IMAGES//MCupleft.tga");
    SpriteAnimation *sa5 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCTOPLEFT]);
    if (sa5)
    {
        sa5->m_anim = new Animation();
        sa5->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCDOWNLEFT] = MeshBuilder::GenerateSpriteAnimation("downleft", 1, 3);
    meshList[GEO_MCDOWNLEFT]->textureID = LoadTGA("Image//PLAYER IMAGES//MCdownleft.tga");
    SpriteAnimation *sa6 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWNLEFT]);
    if (sa6)
    {
        sa6->m_anim = new Animation();
        sa6->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCDOWNRIGHT] = MeshBuilder::GenerateSpriteAnimation("downright", 1, 3);
    meshList[GEO_MCDOWNRIGHT]->textureID = LoadTGA("Image//PLAYER IMAGES//MCdownright.tga");
    SpriteAnimation *sa7 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWNRIGHT]);
    if (sa7)
    {
        sa7->m_anim = new Animation();
        sa7->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_MCTOPRIGHT] = MeshBuilder::GenerateSpriteAnimation("topright", 1, 3);
    meshList[GEO_MCTOPRIGHT]->textureID = LoadTGA("Image//PLAYER IMAGES//MCupright.tga");
    SpriteAnimation *sa8 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCTOPRIGHT]);
    if (sa8)
    {
        sa8->m_anim = new Animation();
        sa8->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
}

void Scenebase::BulletImagesInit()
{
    meshList[GEO_FIRE] = MeshBuilder::GenerateSpriteAnimation("topright", 1, 7);
    meshList[GEO_FIRE]->textureID = LoadTGA("Image//BULLET IMAGES//fire.tga");
    SpriteAnimation *sa9 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
    if (sa9)
    {
        sa9->m_anim = new Animation();
        sa9->m_anim->Set(0, 6, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_WATER] = MeshBuilder::GenerateSpriteAnimation("topright", 1, 6);
    meshList[GEO_WATER]->textureID = LoadTGA("Image//BULLET IMAGES//water.tga");
    SpriteAnimation *sa10 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATER]);
    if (sa10)
    {
        sa10->m_anim = new Animation();
        sa10->m_anim->Set(0, 4, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_AIR] = MeshBuilder::GenerateSpriteAnimation("topright", 1, 4);
    meshList[GEO_AIR]->textureID = LoadTGA("Image//BULLET IMAGES//air.tga");
    SpriteAnimation *sa11 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIR]);
    if (sa11)
    {
        sa11->m_anim = new Animation();
        sa11->m_anim->Set(0, 3, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_BIGNET] = MeshBuilder::GenerateQuad("bigweb", Color(1, 1, 1), 1);
    meshList[GEO_BIGNET]->textureID = LoadTGA("Image//BULLET IMAGES//bigNet.tga");

    meshList[GEO_SMALLNET] = MeshBuilder::GenerateQuad("bigweb", Color(1, 1, 1), 1);
    meshList[GEO_SMALLNET]->textureID = LoadTGA("Image//BULLET IMAGES//volleyball.tga");
}

void Scenebase::WispImagesInit()
{
    meshList[GEO_AIRWISP] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_AIRWISP]->textureID = LoadTGA("Image//windwisp.tga");
    SpriteAnimation *sa12 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRWISP]);
    if (sa12)
    {
        sa12->m_anim = new Animation();
        sa12->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_FIREWISP] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_FIREWISP]->textureID = LoadTGA("Image//firewisp.tga");
    SpriteAnimation *sa13 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREWISP]);
    if (sa13)
    {
        sa13->m_anim = new Animation();
        sa13->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }

    meshList[GEO_WATERWISP] = MeshBuilder::GenerateSpriteAnimation("windwisp", 1, 3);
    meshList[GEO_WATERWISP]->textureID = LoadTGA("Image//waterwisp.tga");
    SpriteAnimation *sa14 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERWISP]);
    if (sa14)
    {
        sa14->m_anim = new Animation();
        sa14->m_anim->Set(0, 2, 0, 1.f, true); //startframe, endframe, repeat, time, enable
    }
}

void Scenebase::HUD_ImagesInit()
{
    //HUD stuff
    meshList[GEO_HUD] = MeshBuilder::Generate2DMesh("GEO_HUD", Color(1, 1, 1), 0.0f, 0.0f, 1024, 800.0f);
    meshList[GEO_HUD]->textureID = LoadTGA("Image//HUD IMAGES//HUD.tga");

    meshList[GEO_HEART] = MeshBuilder::Generate2DMesh("GEO_HEART", Color(1, 1, 1), 0.0f, 0.0f, 32.f, 32.f);
    meshList[GEO_HEART]->textureID = LoadTGA("Image//HUD IMAGES//Heart.tga");

    meshList[GEO_HPTEX] = MeshBuilder::Generate2DMesh("GEO_HPTEXTURE", Color(1, 1, 1), 0.0f, 0.0f, 32.f, 32.f);
    meshList[GEO_HPTEX]->textureID = LoadTGA("Image//HUD IMAGES//hpTexture.tga");

    meshList[GEO_HUDNET] = MeshBuilder::Generate2DMesh("GEO_HUDNet", Color(1, 1, 1), 0.0f, 0.0f, 32.f, 32.f);
    meshList[GEO_HUDNET]->textureID = LoadTGA("Image//HUD IMAGES//HUDNet.tga");

    meshList[GEO_HUDFIRE] = MeshBuilder::Generate2DMesh("GEO_HUDFIRE", Color(1, 1, 1), 0.0f, 0.0f, 32.f, 32.f);
    meshList[GEO_HUDFIRE]->textureID = LoadTGA("Image//HUD IMAGES//HUDFire.tga");

    meshList[GEO_HUDWATER] = MeshBuilder::Generate2DMesh("GEO_HUDWATER", Color(1, 1, 1), 0.0f, 0.0f, 32.f, 32.f);
    meshList[GEO_HUDWATER]->textureID = LoadTGA("Image//HUD IMAGES//HUDWater.tga");

    meshList[GEO_HUDAIR] = MeshBuilder::Generate2DMesh("GEO_HUDAIR", Color(1, 1, 1), 0.0f, 0.0f, 32.f, 32.f);
    meshList[GEO_HUDAIR]->textureID = LoadTGA("Image//HUD IMAGES//HUDAir.tga");
}

void Scenebase::UpdateSpritesAnimation(double dt)
{
	SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWN]);
	if (sa1)
	{
		sa1->Update(dt);
		sa1->m_anim->animActive = true;
	}
	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCUP]);
	if (sa2)
	{
		sa2->Update(dt);
		sa2->m_anim->animActive = true;
	}
	SpriteAnimation *sa3 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCLEFT]);
	if (sa3)
	{
		sa3->Update(dt);
		sa3->m_anim->animActive = true;
	}
	SpriteAnimation *sa4 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCRIGHT]);
	if (sa4)
	{
		sa4->Update(dt);
		sa4->m_anim->animActive = true;
	}
	SpriteAnimation *sa5 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCTOPLEFT]);
	if (sa5)
	{
		sa5->Update(dt);
		sa5->m_anim->animActive = true;
	}
	SpriteAnimation *sa6 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWNLEFT]);
	if (sa6)
	{
		sa6->Update(dt);
		sa6->m_anim->animActive = true;
	}
	SpriteAnimation *sa7 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCDOWNRIGHT]);
	if (sa7)
	{
		sa7->Update(dt);
		sa7->m_anim->animActive = true;
	}
	SpriteAnimation *sa8 = dynamic_cast<SpriteAnimation*>(meshList[GEO_MCTOPRIGHT]);
	if (sa8)
	{
		sa8->Update(dt);
		sa8->m_anim->animActive = true;
	}

	SpriteAnimation *sa9 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
	if (sa9)
	{
		sa9->Update(dt);
		sa9->m_anim->animActive = true;
	}

	SpriteAnimation *sa10 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATER]);
	if (sa10)
	{
		sa10->Update(dt);
		sa10->m_anim->animActive = true;
	}

	SpriteAnimation *sa11 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIR]);
	if (sa11)
	{
		sa11->Update(dt);
		sa11->m_anim->animActive = true;
	}


	SpriteAnimation *sa12 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRWISP]);
	if (sa12)
	{
		sa12->Update(dt);
		sa12->m_anim->animActive = true;
	}


	SpriteAnimation *sa13 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREWISP]);
	if (sa13)
	{
		sa13->Update(dt);
		sa13->m_anim->animActive = true;
	}


	SpriteAnimation *sa14 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERWISP]);
	if (sa14)
	{
		sa14->Update(dt);
		sa14->m_anim->animActive = true;
	}


	SpriteAnimation *sa15 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONDOWN]);
	if (sa15)
	{
		sa15->Update(dt);
		sa15->m_anim->animActive = true;
	}

	SpriteAnimation *sa16 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONUP]);
	if (sa16)
	{
		sa16->Update(dt);
		sa16->m_anim->animActive = true;
	}

	SpriteAnimation *sa17 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONLEFT]);
	if (sa17)
	{
		sa17->Update(dt);
		sa17->m_anim->animActive = true;
	}

	SpriteAnimation *sa18 = dynamic_cast<SpriteAnimation*>(meshList[GEO_AIRMONRIGHT]);
	if (sa18)
	{
		sa18->Update(dt);
		sa18->m_anim->animActive = true;
	}


	SpriteAnimation *sa19 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONDOWN]);
	if (sa19)
	{
		sa19->Update(dt);
		sa19->m_anim->animActive = true;
	}

	SpriteAnimation *sa20 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONUP]);
	if (sa20)
	{
		sa20->Update(dt);
		sa20->m_anim->animActive = true;
	}


	SpriteAnimation *sa21 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONLEFT]);
	if (sa21)
	{
		sa21->Update(dt);
		sa21->m_anim->animActive = true;
	}

	SpriteAnimation *sa22 = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIREMONRIGHT]);
	if (sa22)
	{
		sa22->Update(dt);
		sa22->m_anim->animActive = true;
	}


	SpriteAnimation *sa23 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONDOWN]);
	if (sa23)
	{
		sa23->Update(dt);
		sa23->m_anim->animActive = true;
	}

	SpriteAnimation *sa24 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONUP]);
	if (sa24)
	{
		sa24->Update(dt);
		sa24->m_anim->animActive = true;
	}


	SpriteAnimation *sa25 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONLEFT]);
	if (sa25)
	{
		sa25->Update(dt);
		sa25->m_anim->animActive = true;
	}

	SpriteAnimation *sa26 = dynamic_cast<SpriteAnimation*>(meshList[GEO_WATERMONRIGHT]);
	if (sa26)
	{
		sa26->Update(dt);
		sa26->m_anim->animActive = true;
	}

}

//void Scenebase::renderHitbox(bool ShowHitbox)
//{
//	if (ShowHitbox)
//	{
//		modelStack.PushMatrix();
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		modelStack.Translate(obj->Hitbox.pos.x, obj->Hitbox.pos.y + 100, obj->Hitbox.pos.z);
//		modelStack.Scale(obj->Hitbox.size.x, obj->Hitbox.size.y, obj->Hitbox.size.z);
//		RenderMesh(meshList[GEO_HITBOX], false);
//		if (!mode)
//		{
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		}
//		modelStack.PopMatrix();
//}
void Scenebase::Reset()
{

}

//Update Functions
void Scenebase::Update(double dt)
{
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    fps = (float)(1.f / dt);


	camera.Update(dt);
}

//Render Functions
void Scenebase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	
}

void Scenebase::RenderHUD(){
	Render2DMesh(meshList[GEO_HUD], false, 1.0f);

	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().GetWindowWidth() * 0.78f + heartMove, Application::GetInstance().GetWindowHeight() * 0.79f + heartMove, 0);
	modelStack.Scale(heartScale, heartScale, heartScale);
	RenderMeshIn2D(meshList[GEO_HPTEX], false);
	modelStack.PopMatrix();

	Render2DMesh(meshList[GEO_HEART], false, 5, Application::GetInstance().GetWindowWidth() * 0.78f, Application::GetInstance().GetWindowHeight() * 0.79f);
	Render2DMesh(meshList[GEO_HUDNET], false, 1, Application::GetInstance().GetWindowWidth() * 0.28f, Application::GetInstance().GetWindowHeight() * 0.91f);
	Render2DMesh(meshList[GEO_HUDFIRE], false, 1, Application::GetInstance().GetWindowWidth() * 0.28f, Application::GetInstance().GetWindowHeight() * 0.87f);
	Render2DMesh(meshList[GEO_HUDWATER], false, 1, Application::GetInstance().GetWindowWidth() * 0.28f, Application::GetInstance().GetWindowHeight() * 0.83f);
	
	Render2DMesh(meshList[GEO_HUDAIR], false, 0.8, Application::GetInstance().GetWindowWidth() * 0.283f, Application::GetInstance().GetWindowHeight() * 0.795f);
	
	//if (bullet->GetBulletType()==BT_AIR)
	//Render2DMesh(meshList[GEO_AIR], false, 75, Application::GetInstance().GetWindowWidth() * 0.283f + 325, Application::GetInstance().GetWindowHeight() * 0.795f + 40);
	//if (bullet->GetBulletType() == BT_WATER)
	//Render2DMesh(meshList[GEO_WATER], false, 75, Application::GetInstance().GetWindowWidth() * 0.283f + 325, Application::GetInstance().GetWindowHeight() * 0.795f + 40);
	//if(bullet->GetBulletType() == BT_FIRE)
	//Render2DMesh(meshList[GEO_FIRE], false, 75, Application::GetInstance().GetWindowWidth() * 0.283f + 325, Application::GetInstance().GetWindowHeight() * 0.795f + 40);
	//if(bullet->GetBulletType() == BT_NET)
	//Render2DMesh(meshList[GEO_BIGNET], false, 75, Application::GetInstance().GetWindowWidth() * 0.283f + 325, Application::GetInstance().GetWindowHeight() * 0.795f + 38);


	std::ostringstream s;
	s.precision(5);
	s << "x   " << Inventory.netbullet;
	RenderTextOnScreen(meshList[GEO_TEXT1], s.str(), Color(1, 1, 1), 20, 280, 555);

	std::ostringstream ss;
	ss.precision(5);
	ss << "x   " << Inventory.firebullet;
	RenderTextOnScreen(meshList[GEO_TEXT1], ss.str(), Color(1, 1, 1), 20, 280, 530);

	std::ostringstream sss;
	ss.precision(5);
	sss << "x   " << Inventory.waterbullet;
	RenderTextOnScreen(meshList[GEO_TEXT1], sss.str(), Color(1, 1, 1), 20, 280, 505);

	std::ostringstream ssss;
	ssss.precision(5);
	ssss << "x   " << Inventory.airbullet;
	RenderTextOnScreen(meshList[GEO_TEXT1], ssss.str(), Color(1, 1, 1), 20, 280, 480);

	//RenderMeshIn2D(m_cMinimap->GetBorder(), false, 100, Application::GetInstance().GetWindowWidth() * 0.28f, Application::GetInstance().GetWindowHeight() * 0.83f);
	RenderMeshIn2D(m_cMinimap->GetBackground(), false, 150, Application::GetInstance().GetWindowWidth() * 0.28f-150, Application::GetInstance().GetWindowHeight() * 0.83f+40);
	//RenderMeshIn2D(m_cMinimap->GetAvatar(), false, 150, Application::GetInstance().GetWindowWidth() * 0.28f - 150, Application::GetInstance().GetWindowHeight() * 0.83f + 40);

}

void Scenebase::RenderSprites()
{
    if (GlobalData.isControllerConnected)
    {
        if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y > 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x > 0)
        {
            //render top right
            Render2DMesh(meshList[GEO_MCTOPRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y > 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x < 0)
        {
            //render top left
            Render2DMesh(meshList[GEO_MCTOPLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y < 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x < 0)
        {
            //renderbot left
            Render2DMesh(meshList[GEO_MCDOWNLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y < 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x > 0)
        {
            //render bot right
            Render2DMesh(meshList[GEO_MCDOWNRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == 1 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == 0)
        {
            //render up
            Render2DMesh(meshList[GEO_MCUP], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);

        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == -1 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == 0)
        {
            //render down
            Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == 1)
        {
            //render right
            Render2DMesh(meshList[GEO_MCRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else if (controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).y == 0 && controls.GetControllerDirection(CONTROLLER_1, R_JOYSTICK).x == -1)
        {
            //render left
            Render2DMesh(meshList[GEO_MCLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
        else
        {
            Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
        }
    }
    else
    {
        RenderSprites_keyboard();
    }
}

void Scenebase::RenderSprites_keyboard()
{
    if (controls.isKeyboardButtonHeld(KEYBOARD_W) && (controls.isKeyboardButtonHeld(KEYBOARD_D)))
        Render2DMesh(meshList[GEO_MCTOPRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_W) && (controls.isKeyboardButtonHeld(KEYBOARD_A)))
        Render2DMesh(meshList[GEO_MCTOPLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_S) && (controls.isKeyboardButtonHeld(KEYBOARD_A)))
        Render2DMesh(meshList[GEO_MCDOWNLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_S) && (controls.isKeyboardButtonHeld(KEYBOARD_D)))
        Render2DMesh(meshList[GEO_MCDOWNRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_W))
        Render2DMesh(meshList[GEO_MCUP], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_S))
        Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_A))
        Render2DMesh(meshList[GEO_MCLEFT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else if (controls.isKeyboardButtonHeld(KEYBOARD_D))
        Render2DMesh(meshList[GEO_MCRIGHT], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
    else
        Render2DMesh(meshList[GEO_MCDOWN], false, 32, player->Get_cPosition().x, player->Get_cPosition().y, 0);
}

void Scenebase::RenderMesh(Mesh *mesh, bool enableLight)
{
    Mtx44 MVP, modelView, modelView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    if (enableLight && bLightEnabled)
    {
        glUniform1i(m_parameters[U_LIGHTENABLED], 1);
        modelView = viewStack.Top() * modelStack.Top();
        glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
        modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
        glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

        //load material
        glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
        glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
        glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
        glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
    }
    else
    {
        glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    }
    if (mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }
    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }
    mesh->Render();
    if (mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Scenebase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	//	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.3f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
}

void Scenebase::Render2DMesh(Mesh *mesh, bool enableLight, float size, float x, float y, float rotateAngle)
{
    Mtx44 ortho;
    ortho.SetToOrtho(0, Application::GetWindowWidth(), 0, Application::GetWindowHeight(), -10, 10);
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity();
    modelStack.PushMatrix();
    modelStack.LoadIdentity();
    modelStack.Translate(x, y, 0);
    modelStack.Rotate(rotateAngle, 0, 1, 0);
    modelStack.Scale(size, size, size);


    Mtx44 MVP, modelView, modelView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    if (mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }
    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }
    mesh->Render();
    if (mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    modelStack.PopMatrix();
    viewStack.PopMatrix();
    projectionStack.PopMatrix();
}

void Scenebase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	//	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f
			, 0.3f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	//	glEnable(GL_DEPTH_TEST);
}
 
void Scenebase::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y, float rotateAngle)
{
	Mtx44 ortho;
    ortho.SetToOrtho(0, Application::GetWindowWidth(), 0, Application::GetWindowHeight(), -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.Translate(x, y, 0);
    modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Scale(size, size, size);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

void Scenebase::RenderTile(Mesh *mesh, int tileID, const float size, const float x, const float y, const float z)
{
	Mtx44 ortho;
    ortho.SetToOrtho(0, Application::GetWindowWidth(), 0, Application::GetWindowHeight(), -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
    modelStack.Translate(x, y, z);
	modelStack.Scale(size, size, size);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(tileID * 6, 6);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

void Scenebase::RenderTileMap(TileMap* currentMap, float x_Offset, float y_Offset, float z_Offset, float scrollSpeed)
{
	int tileOffSetX = x_Offset / currentMap->GetTileSize();
    int tileOffSetY = y_Offset / currentMap->GetTileSize();

    for (int y = tileOffSetY; y < tileOffSetY + currentMap->GetNumScreenTile_Height() + 1; ++y)
	{
        if (y >= currentMap->GetNumWorldTile_Height())
            break;

        for (int x = tileOffSetX; x < tileOffSetX + currentMap->GetNumScreenTile_Width()+1; ++x)
		{
			if (x >= currentMap->GetNumWorldTile_Width())
				break;
		
			if (currentMap->world_Tile_Map[y][x] == 0)
				continue;

            RenderTile(
                meshList[GEO_TILESHEET]
                , currentMap->world_Tile_Map[y][x]
                , currentMap->GetTileSize()
                , x * currentMap->GetTileSize() - x_Offset * scrollSpeed
                , y * currentMap->GetTileSize() - y_Offset * scrollSpeed
                , z_Offset
                );
		}
	}
}

void Scenebase::RenderBullet()
{
	vector<CBulletInfo*> temp = BulletFactory->GetBulletList();

	for (auto bulletIt : temp)
	{
		if (bulletIt->GetStatus())
		{
			if (bulletIt->GetBulletType() == BT_FIRE)
				Render2DMesh(meshList[GEO_FIRE], false, 16.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_AIR)
				Render2DMesh(meshList[GEO_AIR], false, 16.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_WATER)
				Render2DMesh(meshList[GEO_WATER], false, 16.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_NET)
				Render2DMesh(meshList[GEO_SMALLNET], false, 8.0f, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);

			if (bulletIt->GetBulletType() == BT_NETSPREAD)
				Render2DMesh(meshList[GEO_BIGNET], false, bulletIt->GetScale().x, bulletIt->GetPosition().x - GlobalData.world_X_offset, bulletIt->GetPosition().y - GlobalData.world_Y_offset, 0);
		}
	}
}

//Other Functions
void Scenebase::Exit()
{
}
