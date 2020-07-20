#pragma once
#include "gameNode.h"
class stage2 : public gameNode
{
private:


public:
	stage2() {}
	~stage2() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

