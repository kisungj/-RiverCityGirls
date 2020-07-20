#pragma once
#include "gameNode.h"
#include "boss.h"
class testBossScene : public gameNode
{
private:
	boss* _boss;
public:
	testBossScene() {}
	~testBossScene() {}
public:
	virtual HRESULT init();
	virtual void    render();
	virtual void    update();
	virtual void    release();
};

