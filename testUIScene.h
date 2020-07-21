#pragma once
#include "gameNode.h"
#include "ui.h"

class testUIScene : public gameNode
{
private:
	ui* _ui;

public:
	testUIScene() {}
	~testUIScene() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
};

