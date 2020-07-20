#pragma once
#include "gameNode.h"
class item : public gameNode
{
private:


public:
	item() {}
	~item() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

