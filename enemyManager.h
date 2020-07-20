#pragma once
#include "gameNode.h"
class enemyManager : public gameNode
{
private:


public:
	enemyManager() {}
	~enemyManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

