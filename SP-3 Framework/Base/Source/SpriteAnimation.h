#ifndef	SPRITEANIMATION_H_

#define SPRITEANIMATION_H_
#include "Mesh.h"
#include <vector>
#include "Vertex.h"


struct Animation
{
	//Functions
	Animation() {
	
	}
	void Set(int startFrame, int endFrame, int repeat, float time, bool active)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeatCount = repeat;
		this->animTime = time;
		this->animActive = active;
	}


	//Variables
	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
	bool animActive;

};

class SpriteAnimation : public Mesh
{

public:

	//Functions 
	SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();
	void Update(double dt);
	virtual void Render();
	

	//Variables
	int m_row;
	int m_col;
	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
};

#endif SPRITEANIMATION_H_
