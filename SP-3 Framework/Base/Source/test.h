#ifndef TEST_H
#define TEST_H

#include "SceneMapEditor.h"

class test : public Scenebase
{

public:
	test();
	~test();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
};

#endif