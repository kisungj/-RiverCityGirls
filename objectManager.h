#pragma once
#include "gameNode.h"
class objectManager : public gameNode
{
private:


public:
	objectManager() {}
	~objectManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
};

