#pragma once
#include "gameNode.h"
class testUIScene : public gameNode
{
public:
	testUIScene() {}
	~testUIScene() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
};

