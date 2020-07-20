#pragma once
#include "gameNode.h"
#include "enemy.h"

class testEnemyScene : public gameNode
{
private:
	enemy* _enemy;

public:
	testEnemyScene() {}
	~testEnemyScene() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
};

