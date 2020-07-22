#pragma once
#include "gameNode.h"
#include "enemyBoy.h"

class enemyManager : public gameNode
{
	typedef vector<enemy*> getVEnemy;
	typedef vector<enemy*>::iterator getVIEnemy;
private:
	enemyBoy* _boy;

public:
	enemyManager() {}
	~enemyManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
	vector<enemyBoy*> getVBoy() { return _boy; }
};

