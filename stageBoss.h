#pragma once
#include "gameNode.h"
#include "boss.h"
class stageBoss : public gameNode
{
private:
	boss* _boss;
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

