#pragma once
#include "gameNode.h"
class stage1 : public gameNode
{
private:


public:
	stage1() {}
	~stage1() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

