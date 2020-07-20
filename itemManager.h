#pragma once
#include "gameNode.h"
class itemManager :	public gameNode
{
private:


public:
	itemManager() {}
	~itemManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

