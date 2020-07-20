#pragma once
#include "gameNode.h"
class object : public gameNode
{
private:


public:
	object() {}
	~object() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
};

