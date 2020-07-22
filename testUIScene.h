#pragma once
#include "gameNode.h"
#include "ui.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class testUIScene : public gameNode
{
private:
	ui* _ui;
	string _test;

	char _indexStr[255];

	int _index;
	float _chatCount;

public:
	testUIScene() {}
	~testUIScene() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
};

