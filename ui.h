#pragma once
#include "gameNode.h"
class ui : public gameNode
{
private:


public:
	ui() {}
	~ui() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
};

