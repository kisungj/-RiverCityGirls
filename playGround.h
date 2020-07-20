#pragma once
#include "gameNode.h"
#include "stageManager.h"
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class playGround : public gameNode
{
private:
	stageManager* _stageManager;

public:
	playGround();
	~playGround();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
};

