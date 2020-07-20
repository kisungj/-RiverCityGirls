#pragma once
#include "gameNode.h"
class stageBoss : public gameNode
{
private:


public:
	stageBoss() {}
	~stageBoss() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

